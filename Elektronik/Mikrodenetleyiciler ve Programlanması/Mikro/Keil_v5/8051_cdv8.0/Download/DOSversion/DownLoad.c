/********************************************************************

ADuC Downloader Version 2.07                            13 Oct 1999
----------------------------                            Ciaran King
                                                        Accutron Ltd.
This program serially downloads program files           Limerick,
to Analog Devices MicroConverter products.              Ireland.

Program files must be of INTEL standard HEX format.

This code was compiled using Borland C++ version 5.0 for DOS.

The clock() function is used to determine communication timeouts.
[the tick resolution is assumed to be 1/18th of a second.  It may be
different on other compilers or in memory models other than LARGE]

This program will work with two versions of on-chip firmware:
  - version 1 firmware is on ADuC812 chips of date code <9933**
  - version 2 firmware is on ADuC812 chips of date code >9932**
                             and other MicroConverter products

                      **ENGINEERING LOT EXCEPTION:
                        parts branded with lot nmbr & date code of
                        F104366.1 & 9925 contain version 2 firmware

For a detailed description of both serial download protocols, refer
to Analog Devices' tech note "uC004 - Understanding the Serial
Download Protocol" available at http://www.analog.com/MicroConverter.

********************************************************************/

#include <stdio.h>   //for reading hex file
#include <string.h>  //for copying parameter strings
#include <stdlib.h>  //for exit() function
#include <time.h>    //for clock() and clock_t (timeouts)
#include <conio.h>   //for reading/writing the UART hardware ports
#include <ctype.h>   //for toupper() function

/*******************************************************************/

#define DEFAULTTIMEOUT 5  //about a quarter of a second
#define ERASETIMEOUT 80   //about 4 seconds

#define VER " 2.07 "
#define DATE "18th Oct, 1999  "

const int retrys = 3;

/*function prototypes*/

int  reset(int *major, int *minor);
int  download(int rev, char *program);
int  run(int rev, long address);

void showTitle(void);
void showInstructions(void);

int  decodeCommandLine(int argc, char *argv[],
                       int *comport, double *crystal,
                       char *filename,
                       int *dontEraseData,
                       int *autoRun,
                       long *startAddress);

int  validateParameters(int comport, double *crystal,
                        char *filename, long startAddress);

int  openComms(int comport, long baudrate);
int  initcommshardware(int comport, unsigned long int baudrate);
int  dataavail(void);
void charin(unsigned char *ch);
int  clearxmit(void);
void charout(unsigned char ch);

int  readRecordFromFile(FILE *FptrIn, unsigned char *Record);
int  readBlockFromFile(FILE *FptrIn, unsigned long *addr,
                       int *len, unsigned char *data);

int  sendPacket(unsigned char *message, int length);
int  sendLoaderPacket(int len, char *data);
int  waitForAck(int timeout);

int  waitForRev1Signature(char *sig);
int  downloadRev1(char *program);
int  runRev1(long address);

int  waitForRev2Signature(char *sig, int *major, int *minor);
int  enableRev2(int revision, int dontEraseData);
int  downloadRev2(char *program);
int  runRev2(long address);


/*******************************************************************/
/*                    BEGINNING OF MAIN PROGRAM                    */
/*******************************************************************/

void main(int argc, char *argv[])
{
  int comport=1;               //comport to connect through
  long baudrate=9600;          //communications baud rate
  long cmdStartAddress=-1;
  long startAddress=0x0000;    //downloaded program start address
  char filename[256]="";       //name&location of program to download
  double crystal=11.059200;    //crystal frequency of the target
  int rMajor, rMinor;          //rev number of the target firmware
  int dontEraseData = 0;       //default to erasing all target memory
  int autoRun=0;               //don't automatically run target prog

  showTitle();

  decodeCommandLine(argc,argv,
                    &comport,&crystal,
                    filename,
                    &dontEraseData,
                    &autoRun,
                    &cmdStartAddress);

  if(!validateParameters(comport,&crystal,filename,startAddress))
    exit(1);

  /*work out actual baud rate*/
  baudrate=crystal/1152.0;

  openComms(comport,baudrate);

  /*reset the target device (hopefully into loader mode)*/
  if(reset(&rMajor,&rMinor))
  {
    printf("Target firmware revision %d.%02d\n",rMajor,rMinor);

    if(cmdStartAddress!=-1)  //user specified a different start address
      startAddress=cmdStartAddress;
    else if(rMajor==1)       //use the default rev 1 start address
      startAddress=0xFF00;
    else if(rMajor==2)       //use the default rev 2 start address
      startAddress=0x0000;

    if(enableRev2(rMajor,dontEraseData))
    {
      if(download(rMajor,filename))
      {
        if(autoRun)
        {
          run(rMajor,startAddress);
        }
      }
    }
  }
}

/*******************************************************************/
/*           END OF MAIN PROGRAM , BEGINNING OF FUNCTIONS          */
/*******************************************************************/

/*extract the filename etc. from the command line parameters*/
int  decodeCommandLine(int argc,char *argv[],
                       int *comport,double *crystal,
                       char *filename,
                       int *dontEraseData,
                       int *autoRun,
                       long *startAddress)

{
  int i;
  char option;
  for(i=1;i<argc;i++)         //loop thru all arguments on cmd line
                              //skip argv[0] as that's the appl. name
  {
    if(  (argv[i][0]=='-')    //see if this argument is a parameter
       ||(argv[i][0]=='\\')   //by checking first char in the string
       ||(argv[i][0]=='/'))
    {
      option=toupper(argv[i][1]);
      if(argv[i][2]==':')     //3rd char in param string must be ';'
      {
        switch(option)        //check the second char to see what
                              //parameter it is
        {
        case 'C':                                //comport parameter
          *comport=argv[i][3]-'0';
          break;
        case 'F':                                //crystal frequency
          sscanf(&argv[i][3],"%lf",crystal);
          break;
        case 'R':                                //start address
          *autoRun=1;
          sscanf(&argv[i][3],"%X",startAddress);
          break;
        }
      }
      else if ((option=='H')||(option=='?'))
        showInstructions();
      else if (option=='D')
        *dontEraseData=1;
      else if (option=='R')
        *autoRun=1;
    }
    else                             //assume argument is a filename
      strcpy(filename,argv[i]);
  }
  return 0;
}

/*check that the specified parameters are valid*/
int validateParameters(int comport,double *crystal,
                       char *filename,long startAddress)
{
  if(strlen(filename)==0)
  {
    printf("No Program file specified\n");
    return 0;                            /*false*/
  }
  if((comport<1) || (comport>8))
  {
    printf("invalid comport number\n");
    return 0;                            /*false*/
  }

  if(*crystal<70)
    *crystal*=1000000.0;  /*convert from MHz into Hz*/

  if((*crystal<2000000.0) || (*crystal>70000000.0))
  {
    printf("invalid target crystal frequency\n");
    return 0;                            /*false*/
  }
  if(startAddress>0xFFFF)
  {
    printf("invalid start address\n");
    return 0;                            /*false*/
  }
  return 1;                              /*true*/
}

void showTitle(void)
{
  printf("\nDOWNLOAD.EXE: ADuC program downloader ver "VER"\n");
  printf(DATE"C.King Accutron Ltd.\n");
}

void showInstructions(void)
{
  printf("Program options:\n");
  printf("  a filename must be specified on the command line\n");
  printf("  /C:n    select the com port (default is 1)\n");
  printf("  /F:n.n  select the target crystal freq in MHz (default 11.0592)\n");
  printf("  /D      do not erase Flash/EE data space (firmware rev 2.0 or greater)\n");
  printf("  /R      run the program from the beginning (0000 hex)\n");
  printf("  /R:xxxx run the program from the specified start address\n");
  printf("Example:\n");
  printf("  DOWNLOAD filename.hex /c:1 /f:16 /d /r\n");
}

/*******************************************************************/

/*set up the communications link to the target*/
int openComms(int comport,long baudrate)
{
  int rcvd;
  unsigned char ch;
  printf("Initialising Com%d at %ld baud:",
         comport,baudrate);
  if(!initcommshardware(comport,baudrate))
  {
    printf("Failed.\n");
    return 0;      /*failure*/
  }
  printf("OK!\n");

  if(dataavail()){
    /*need to purge the com channel*/
    rcvd=0;
    printf("Clearing receive buffer:");
    while(dataavail()){      //see if any data from the target
      charin(&ch);           //get the data
      printf(".");
      rcvd++;
      if(rcvd>100){
        printf("\nRecieve buffer overflow: terminating\n");
        return 0; /*failure*/
      }
    }
    printf("Cleared\n");
  }
  return 1;             /*success*/

}

/*attempt to perform a software reset on the target*/
int  reset(int *major,int *minor)
{
  unsigned char data[4];
  char sanatizedSig[100];
  *major=0;
  *minor=0;
  int i;
  for(i=0;i<retrys;i++)   //3 attempts to reset...
  {
    printf("Resetting the target device: ");
    /*Send the rev1 loader reset command*/
    charout('!');
    /*now see if the rev1 signature has appeared*/
    if(waitForRev1Signature(sanatizedSig))
    {
      printf("%s reset OK!\n",sanatizedSig);
      *major=1;
      return 1;           /*success*/
    }

    /*now send the rest of the reset packet*/
    /*the first byte, the '!' has already been sent*/
    data[0]='Z';      //command code
    data[1]='O';                  //set up the parameter and checksum
    data[2]=0-data[0]-data[1];
    if(sendPacket(data,3))
      if(waitForRev2Signature(sanatizedSig,major,minor))
      {
        printf("%s reset OK!\n",sanatizedSig);
        return 1;         /*success*/
      }
    printf("Failed\n");
  }
  return 0;             /*failure*/
}



/*download the program to the target device*/
int download(int rev,char *program)
{
  int result;
  printf("Downloading %s: ",program);
  switch(rev)
  {
  case 0:
    result=1;
    break;
  case 1:
    result=downloadRev1(program);
    break;
  case 2:
    result=downloadRev2(program);
    break;
  default:
    result=2;
    break;
  }
  switch(result)
  {
  case 0:
    printf(" Downloaded OK!\n");
    break;
  case 1:
    printf("Error: Target was not reset\n");
    break;
  case 2:
    printf("Error: This version of DOWNLOAD.EXE is not compatible with this target\n");
    break;
  case 3:
    printf("Error: Failed to download\n");
    break;
  case 4:
    printf("Error: File not found\n");
    break;
  }
  return (result==0);
}


/* send the target device a command to commence user code execution
   from a specified address */
int run(int rev,long address)
{
  int result;
  printf("Running program from address 0x%04lx: ",address);
  switch(rev)
  {
  case 0:
    result=1;
    break;
  case 1:
    result=runRev1(address);
    break;
  case 2:
    result=runRev2(address);
    break;
  default:
    result=2;
    break;
  }
  switch(result)
  {
  case 0:
    printf("Run OK!\n");
    break;
  case 1:
    printf("Not reset\n");
    break;
  case 2:
    printf("Error: This version of DOWNLOAD.EXE is not compatible with this target\n");
    break;
  case 3:
    printf("Failed to run\n");
    break;
  }
  return (result==0);
}

/*******************************************************************/
/*Revision 1 loader routines*/
int waitForRev1Signature(char *sig)
{
  int i=0;
  clock_t starttime;        //clock variable for determining timeouts
  unsigned char ch;
  char expected[]="ADuC812  krl";  //rev 1 firmware was only used on the '812
  strcpy(sig,"none");
  starttime=clock();          //get start clock value
  while(1)
  {                           //keep trying....
    if(dataavail())           //see if any data from the target
    {
      charin(&ch);            //get the data
      if(ch==expected[i])
      {
        sig[i]=ch;
        i++;
        sig[i]='\0';
        if(i==strlen(expected))
        {
          sig[7]='\0';        //hide the '  krl' part of the string*/
          return 1;           /*success*/
        }
      }
      else
        i=0;                  //back to the start
    }
    if(clock()>starttime+15)  //see if timeout has elapsed
      return 0;               /*timeout failure*/
  }
}

int downloadRev1(char *program)
{
  FILE *pFile;
  unsigned char buffer[128];
  int result=0; /*success*/
  /*try and open the file*/
  pFile=fopen(program,"r");
  /*check if it opened ok*/
  if(pFile!=NULL)
  {
    while(1)  //keep going until all downloaded
    {
      if(readRecordFromFile(pFile,buffer))
      {
        if(sendPacket(buffer,strlen((char*)buffer)))
        {
          if(!waitForAck(DEFAULTTIMEOUT))
          {
            result=3;
            break;
          }
          else
            printf(".");
        }
        else
        {
          result=3;
          break;
        }
      }
      else
        break;
    }
    /*close the intel hex file*/
    fclose(pFile);
  }
  else
    result=4;
  return result;
}

int runRev1(long address)
{
  unsigned char packet[30];
  sprintf((char*)packet,";%X",address);
  if(sendPacket(packet,strlen((char*)packet)))
    if(waitForAck(DEFAULTTIMEOUT))
      return 0;
  return 3;      /*failure*/
}

/*******************************************************************/
/*Revision 2 loader routines*/

int waitForRev2Signature(char *sig,int *major,int *minor)
{
  int i=0;
  int state=0;
  clock_t starttime;        //clock variable for determining timeouts
  unsigned char ch;
  unsigned char checksum=0;
  unsigned char data[30];
  strcpy(sig,"none");
  starttime=clock();        //get start clock value
  while(1)                  //keep trying....
  {
    if(dataavail())         //see if any data from the target
    {
      charin(&ch);          //get the data
      data[state]=ch;
      checksum+=ch;
      switch(state) //see what we are doing....
      {             //watch for fallthroughs in this switch statement
      case 0:       //waiting for start character ("A")
        if(ch=='A')
          state++;
        else
          checksum=0;
        break;
      case 1:
        if(ch=='D')         //waiting for second character ("D")
          state++;
        else
          state=0;
        break;
      case 2:               //waiting for third character ("I")
        if(ch=='I')
          state++;
        else
          state=0;
        break;
      case 3:               //waiting for device partname
        /*Since we scrap the "ADI" part code header,
          replace it with "ADuC"*/
        strcpy(sig,"ADuC");
        i=4;                //position of next character
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
        /*if the character in the device partname is a printable
          character, other than capital "X" or space " ", then
          add it to the signature string*/
        if((isprint(ch)) && (ch!='X') && (ch!=' '))
          sig[i++]=ch;
        sig[i]='\0';
        state++;
        break;
      case 10:
        if(ch=='V')
          state++;
        else
          state=0;
        break;
      case 11:
        if(isdigit(ch)){
          *major=ch-'0';
          state++;
        }
        else
          state=0;
        break;
      case 12:
        if(isdigit(ch)){
          *minor=(ch-'0')*10;
          state++;
        }
        else
          state=0;
        break;
      case 13:
        if(isdigit(ch)){
          *minor+=(ch-'0');
          state++;
        }
        else
          state=0;
        break;
      case 14:
        if(ch=='\r')
          state++;
        else
          state=0;
        break;
      case 15:
        if(ch=='\n')
          state++;
        else
          state=0;
        break;
      case 16:     //waiting for hardware id hi byte: ignore
      case 17:     //waiting for hardware id lo byte: ignore
      case 18:     //waiting for firmware id hi byte: ignore
      case 19:     //waiting for firmware id lo byte: ignore
      case 20:     //waiting for age hi byte:         ignore
      case 21:     //waiting for age lo byte:         ignore
      case 22:     //waiting for spare byte:          ignore
      case 23:     //waiting for spare byte:          ignore
        state++;
        break;
      case 24:     //waiting for checksum
        return (checksum==0);
      }
    }
    if(clock()>starttime+15)     //see if timeout has elapsed
      return 0;                  //timeout failure
  }
}

int enableRev2(int revision,int dontEraseData)
{
  int result=0;
  if(revision==1)
    result=1;
  if(revision==2)
  {
    int i;
    for(i=0;i<retrys;i++)
    {
      if(dontEraseData)
      {
        printf("Erasing code memory . . ");
        if(sendLoaderPacket(1,"C"))
          result=waitForAck(ERASETIMEOUT);
      }
      else{
        printf("Erasing code and data memory . . ");
        if(sendLoaderPacket(1,"A"))
          result=waitForAck(DEFAULTTIMEOUT);
      }
      if(result)
      {
        printf("OK\n");
        break;
      }
      else
        printf("Failed\n");
    }
  }
  return result;
}

int downloadRev2(char *program)
{
  FILE *pFile;
  unsigned char progData[128];   //block of data to download
  unsigned long progAddr;        //address to download to
  int blockLen;                  //number of bytes in the block
  int result=0;                  /*success*/
  /*try and open the file*/
  pFile=fopen(program,"r");
  /*check if it opened ok*/
  if(pFile!=NULL)
  {
    while(1)                     //keep going until all downloaded
    {
      /*read a block of data from the file, along with its destination addr*/
      if(readBlockFromFile(pFile,&progAddr,&blockLen,progData))
      {
        /*see if we got data ok*/
        if(blockLen>0)
        {
          result=3;              //assume the worst...
          /*build up the program packet*/
          char packet[128];
          int i;
          packet[0]='W';                 //write code memory command
          packet[1]=(progAddr>>16)%256;  //set up the 24bit address
          packet[2]=(progAddr>>8) %256;
          packet[3]= progAddr     %256;
          /*copy the program bytes into the packet*/
          for(i=0;i<blockLen;i++)
            packet[i+4]=progData[i];
          /*send the command as a 'loader' packet*/
          if(sendLoaderPacket(blockLen+4,packet))
          {
            /*check to see if the target ack's the command*/
            if(waitForAck(DEFAULTTIMEOUT))
            {
              /*print a 'progress dot'*/
              printf(".");
              result=0;
            }
            else
              break;  //break out of the loop
          }
          else
            break;    //break out of the loop
        }
      }
      else
        break;        //break out of the loop
    }
    /*close the intel hex file*/
    fclose(pFile);
  }
  else
    result=4;
  return result;
}

int runRev2(long address)
{
  char data[4];
  /*build the 'run' command packet*/
  data[0]='U';                 //run from user space command
  data[1]=(address>>16)%256;   //24 bit address
  data[2]=(address>>8)%256;
  data[3]= address%256;
  /*send the command as a 'loader' packet*/
  if(sendLoaderPacket(4,data))
  {
    /*check to see if the target ack's the command*/
    if(waitForAck(DEFAULTTIMEOUT))
      return 0;                /*success*/
  }
  return 3;                    /*failure*/
}

/*******************************************************************/

/*sends a data packet to the target*/
int sendPacket(unsigned char *message,int length)
{
  int i;
  clock_t starttime;        //clock variable for determining timeouts
  starttime=clock();        //get start clock value
  i=0;
  while(i<length)
  {
    if(clearxmit())         //is uart ready to transmit next byte?
    {
      charout(message[i++]);   //send the byte
      starttime=clock();       //'reset' the timeout
    }
    else                       //uart is not ready
      if(clock()>starttime+2)  //see if timeout has elapsed
        return 0;              /*timeout failure*/
  }
  return 1;
}

/*sends a correctly formated loader command packet to the target*/
int sendLoaderPacket(int len, char *data)
{
  unsigned char packet[128];  //the loader packet
  unsigned char xsum;         //temp var to calculate the checksum
  int i;
  /*set up the 070E header*/
  packet[0]=0x07;
  packet[1]=0x0E;
  /*set up the number of data bytes in the loader packet*/
  packet[2]=len;
  /*copy the data into the packet*/
  for(i=0;i<len;i++)
    packet[3+i]=data[i];
  /*now calculate the checksum of the packet*/
  /*ignore the header, but include the length byte*/
  xsum=len;
  for(i=0;i<len;i++)
    xsum+=packet[i+3];
  packet[len+3]=0-xsum;
  /*send the packet to the target device*/
  return sendPacket(packet,len+4);
}

/*wait for acknowledge from the target device*/
int waitForAck(int timeout)
{
  unsigned char ch;
  clock_t starttime;  //clock variable for determining the timeouts
  starttime=clock();  //get start clock value
  while(1)            //keep trying....
    if(dataavail())   //see if any data from the target
    {
      charin(&ch);    //get the data
      if(ch==0x06)    //see if it is an ACK
        return 1;     /*success*/
    }
    else
      if(clock()>starttime+timeout)    //see if timeout has elapsed
        return 0;                      /*failed (due to timeout)*/
}

int readRecordFromFile(FILE *FptrIn,unsigned char *Record)
{
// read a record from file
  int Index=0;
  unsigned char InChar;
  InChar=fgetc(FptrIn);
  while((InChar!='\n') && ((char)InChar!=EOF))
  {
    Record[Index++]=InChar;
    InChar=fgetc(FptrIn);
  }
  Record[Index] = '\0';
  if (Index==0) return 0;        /*nothing read*/
  if (Record[0]!=':') return 0;  /*not a intel hex record*/
  return 1;
}


int readBlockFromFile (FILE *FptrIn,unsigned long *addr,
                       int *len, unsigned char *data)
{
  char Record[128];
  int bytecount;
  unsigned char xsum=0;
  int rectype;
  int packetxsum;
  int i;
  if(readRecordFromFile(FptrIn,(unsigned char*)Record))
  {
    /*get the number of data bytes in the record*/
    if(sscanf(Record+1,"%2X",&bytecount)!=1) return 0;
    xsum+=bytecount;
    /*get the block start address*/
    if(sscanf(Record+3,"%4lX",addr)!=1) return 0;
    xsum+=(*addr)/256;
    xsum+=(*addr)%256;
    /*get the record type*/
    if(sscanf(Record+7,"%2X",&rectype)!=1) return 0;
    xsum+=rectype;
    /*get the data from the record*/
    for(i=0;i<bytecount;i++)
    {
      if(sscanf(Record+9+i*2,"%2X",data+i)!=1) return 0;
      xsum+=data[i];
    }
    /*get the checksum from the record*/
    if(sscanf(Record+9+bytecount*2,"%2X",&packetxsum)!=1) return 0;
    xsum+=packetxsum;
    /*validate the checksum*/
    if(xsum!=0)
      return 0;
    /*make sure it's a type of records that we can handle*/
    if(rectype==0)         //only return type 0 records
      *len=bytecount;
    else if(rectype==1)    //ignore type 1 records
      *len=0;
    else
      return 0;            //fail on any other type of records
    return 1;
  }
  return 0;
}

/*******************************************************************/
/*low-level uart communications routines*/

/*type of error*/
typedef enum {COMMS_NOERR,       //no error encountered
              COMMS_OVERRUN,     //serial comunications overrun
              COMMS_PARITY,      //serial communications parity error
              COMMS_FRAME,       //serial communications frame error
              COMMS_BREAK,       //serial communications break
              COMMS_SENDTIMEOUT, //communications timeout on xmit
              COMMS_WAITTIMEOUT, //communications timeout on recieve
              COMMS_RECVTIMEOUT  //communications timeout on recieve
              } commerrors;


/*line control register bit definitions*/

#define LCRWORDLSB 1
#define LCRWORDMSB 2
#define LCRSTOP    4
#define LCRPAR     8
#define LCRPARSEL 16
#define LCRPARONE 32
#define LCRBREAK  64
#define LCRDIV   128

/*modem control register bit definitions*/
#define MCRDTR   1
#define MCRRTS   2
#define MCROUT1  4
#define MCROUT2  8
#define MCRLOOP 16

/*interupt enable register bit definitions*/
#define INTRECV  1
#define INTXMIT  2
#define INTLSTAT 4
#define INTMSTAT 8

/*line status register bit definitions*/
#define DATAREADY  1
#define OVERRUN    2
#define PARITY     4
#define FRAME      8
#define BREAK     16
#define XMITREADY 32
#define TSRE      64

/*modem status register bit definitions*/
#define DELTACTS   1
#define DELTADSR   2
#define TERI       4
#define DELTARLSD  8
#define CTS       16
#define DSR       32
#define RI        64
#define RLSD     128

/*interupt identifiation register definitions*/
#define INT_NONE  1
#define INT_MSTAT 0
#define INT_THRE  2
#define INT_RDA   4
#define INT_LSTAT 6

/*uart register offsets from base address*/
#define LCONT (combase+3)
#define TXREG (combase)
#define RXREG (combase)
#define MCONT (combase+4)
#define LSTAT (combase+5)
#define MSTAT (combase+6)

/*record of the previous error*/
commerrors lastcommerr=COMMS_NOERR;

/*hardware IO port base address of the uart*/
unsigned int combase;

/*set up the uart*/
int initcommshardware(int comport,unsigned long int baudrate)
{
  unsigned long divisor;
  unsigned char lsb,msb;
  /*calculate the uart hardware base address*/
  if(comport==1)
    combase=0x3F8;
  else if(comport==2)
    combase=0x2F8;
  else
    combase=comport;
  /*calculate the baud rate divisor values*/
  divisor=(115200L / baudrate);
  msb=divisor/256;
  lsb=divisor & 0x00ff;
  printf(".");               //display a progress dot
  /*set up the uart to access the baud rate divisor registers*/
  outp(LCONT,LCRDIV);
  printf(".");               //display a progress dot
  /*write the baud rate divisor values*/
  outp(combase,  lsb);
  printf(".");               //display a progress dot
  outp(combase+1,msb);
  printf(".");               //display a progress dot
  /*set up the line parameters*/
  outp(LCONT,0x03);          //no parity, 1 stop, 8 data
  printf(".");               //display a progress dot
  return 1;
}

/*checks to see if the uart line status is ok*/
unsigned char check_status(int *status)
{
  lastcommerr=COMMS_NOERR;        //assume no error
  *status=inp(LSTAT);             //get the uart line status
  if (*status & OVERRUN)          //check for overrun error
    lastcommerr=COMMS_OVERRUN;
  if (*status & PARITY)           //check for parity error
    lastcommerr=COMMS_PARITY;
  if (*status & FRAME)            //check for frame error
    lastcommerr=COMMS_FRAME;
  if (*status & BREAK)            //check for break error
    lastcommerr=COMMS_BREAK;
  /*return TRUE if there was no error*/
  return(lastcommerr==COMMS_NOERR);
}


int clearxmit(void)
{
  int status;
  /*see if the uart status is ok*/
  if(check_status(&status))
    /*see if the transmit ready bit is set*/
    if (status & XMITREADY)
      return 1;
  return 0;
}

int dataavail(void)
{
  int status;
  /*see if the uart status is ok*/
  if(check_status(&status))
    /*see if the dataready bit is set*/
    if (status & DATAREADY)
      return 1;
  return 0;
}

/*read the byte from the recieve register of the uart*/
void charin(unsigned char *ch)
{
  *ch=inp(RXREG);
}

/*send the byte to the transmision register of the uart*/
void charout(unsigned char ch)
{
  outp(TXREG,ch);
}
