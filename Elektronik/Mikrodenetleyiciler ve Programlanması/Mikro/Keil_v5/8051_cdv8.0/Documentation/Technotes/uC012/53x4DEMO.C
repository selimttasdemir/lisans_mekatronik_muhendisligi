/********************************************************************

 Author        : ADI - Apps            www.analog.com/MicroConverter

 Date          : 

 File          : 53x4DEMO.c

 Hardware      : ADuC814

 Description:	
 
********************************************************************/

#pragma DEBUG OBJECTEXTEND CODE // pragma lines can contain state C51
#include <stdio.h>              // declarations for I/O functions
#include <ctype.h>
#include <ADuC814.h>            // 8052 & ADuC814 predefined symbols


float vref;
sbit ad53x4cs = P3^4;	// Chip select for ad53x4 (PORT3.4)



/*******************************************************
Initialize the ADuC814 resouces being used
in this sample
*******************************************************/

void init814(void)	// Initialize internal peripherals
 {
  /* Configure UART for 9362bps */
  RCAP2H = 0xff;
  RCAP2L = -7;
  TH2 = 0xff;
  TL2 = -7;
  SCON = 0x52;
  T2CON = 0x34;

  /* Initialize SPI to talk to AD53x4 */
  CFG814 = 0x01;       // Serial interface enable for P3.5..P3.7 pins
  SPICON = 0x38;	// Enable SPI I/F as master, SCLOCK idle H,
  			// advance MSB output, sclock=fcore/2=1.05Mhz
 }
                                               


/********************************************************************
Low level interface functions from here
********************************************************************/



/*******************************************************
This function transmittes a byte data 
on the SPI interface
*******************************************************/

void spiTx(unsigned char txDat)	// Transmit a byte data over the SPI
 {
  ISPI = 0;     // Clear ISPI bit
  SPIDAT = txDat;
  while(!ISPI); // Wait until tx complete
 }



/*******************************************************
This function transfers a 16-bit input shift register
contents to the AD53x4 over the spi interface
*******************************************************/

void ad53x4out(unsigned char adrs, // A1,A0 bit of the contents
               bit pdN, // /PD bit of the contents
               bit ldacN, // /LDAC bit of the contents
               unsigned short dat) // 12-bit output data 
 {
  unsigned char txDat;
   
  ad53x4cs = 0;

  txDat = ((unsigned char) (dat>>8)) & 0x0f;
  txDat |= ldacN ? 0x10 : 0x00;
  txDat |= pdN ? 0x20 : 0x00;
  txDat |= (adrs<<6);
  spiTx(txDat);	// Tx the upper byte

  txDat = (unsigned char) dat;
  spiTx(txDat);	// Tx the lower byte

  ad53x4cs = 1;
 }



/*******************************************************
This function simultanously updates all the output
channels specified in the parameter list
*******************************************************/

void ad53x4out4(unsigned short dat0, unsigned short dat1, //datn is a data output to channel n. upper 4 bits ignored
                unsigned short dat2, unsigned short dat3)
 {
  ad53x4out(0,1,1,dat0);
  ad53x4out(1,1,1,dat1);
  ad53x4out(2,1,1,dat2);
  ad53x4out(3,1,0,dat3);
 }



/********************************************************************
Application specific functions from here
********************************************************************/


/*******************************************************
This function displayes Main Menu on terminal and
returns a selection
*******************************************************/

short MainMenu(void)
 {
  unsigned char n;
  do
   {
    putchar(12);
    printf("Main Menu\n\n");
    printf("VREF= %.3f\n\n", vref);
    printf("1 Enter Power Down Mode\n");
    printf("2 Set 0 to all channels\n");
    printf("3 Set Voltage\n");
    printf("4 Specify VREF\n\n");

    printf(">"); n=getchar();
   } while(!( '1' <= n & n <= '4' ) );

  return(toint(n));
 }

 

/*******************************************************
This function puts the external DAC into power down
mode
*******************************************************/

void powerDown(void)
 {
  putchar(12);
  ad53x4out(0,0,0,0);
  printf("Power down mode set\n\nAny key to return to Main Menu"); getchar(); 
 }



/*******************************************************
This function sets 0 volt to all the output channel of
the external DAC
*******************************************************/

void setZero(void)
 {
  putchar(12);
  ad53x4out4(0,0,0,0);
  printf("All outputs set to 0V\n\nAny key to return to Main Menu"); getchar();
 }



/*******************************************************
This function displayes Set Voltage sub menu
and returns a selection
*******************************************************/

unsigned char setVMenu(void)
 {
  unsigned char n;

  do
   {
    putchar(12);
    printf("Select Channel or ^C to exit\n\n");
    printf("0 Channel A\n");
    printf("1 Channel B\n");
    printf("2 Channel C\n");
    printf("3 Channel D\n\n");
    
    printf(">"); n=getchar(); printf("\n");
   } while(!('0'<=n & n<='3' | n==3));

  return(n);
 }    


 
/*******************************************************
This function sets voltage to a channel
*******************************************************/

void setVoltage(void)
 {
  unsigned char ch;
  unsigned char c;
  int u;
  float voltage;
  unsigned int outcode;

  if (vref==0)
   {
    putchar(12);
    printf("Specify VREF from the Main Menu first\n\nAny key to return to Main Menu");
    getchar();
   }
  else
   {

    do
     {
      ch = setVMenu();
      if (ch==3) break; else ch=toint(ch);

      do
       {
        printf("Channel %c output voltage [V] (^C to exit) = ",toascii('A'+ch));
        u=scanf("%f",&voltage); c=getchar(); printf("\n");
        if (u!=0)
         {
          if (voltage < vref*4095.5/4096) 
           ad53x4out(ch,1,0,outcode=4096*voltage/vref+0.5);
          else
           printf("Out of range\n");
         }
        else
         if (c==3) break; else printf("?\n");
       } while(1);

     } while(1);

   }

 }



/*******************************************************
This function get a reference voltage specified by
a user
*******************************************************/

void spcVref(void)
 {
  putchar(12);
  printf("VREF Voltage [V] = "); scanf("%f",&vref); getchar();
 }



/********************************************************************
MAIN function
********************************************************************/

void main(void)
 {
  init814();

  while(1)
   {
    switch( MainMenu() )
     {
      case 1: powerDown();
              break;
      case 2: setZero();
              break;
      case 3: setVoltage();
              break;
      case 4: spcVref();
              break;
     }
   }

 }
