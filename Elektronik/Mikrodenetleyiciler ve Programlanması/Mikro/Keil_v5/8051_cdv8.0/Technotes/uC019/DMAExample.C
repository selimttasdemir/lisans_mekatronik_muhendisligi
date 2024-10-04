/********************************************************************

 Author        : ADI - Apps            www.analog.com/MicroConverter

 Date          : APRIL 2002

 File          : DMAEXAPLE.C

 Hardware      : ADuC832

 Description	: DMA MENU DRIVEN EXAMPLE CODE	
 
********************************************************************/

#pragma DEBUG OBJECTEXTEND CODE // pragma lines can contain state C51
#include <stdio.h>              // declarations for I/O functions
#include <ctype.h>
#include <ADuC832.h>            // 8052 & ADuC832 predefined symbols
int i=0,flag=0;

void adc_int() interrupt 6{ 
	ADCCON1=0x00;
	flag  = 1;
        return;
			}

void init832(void)				// Initialize internal peripherals
 {
  PLLCON=0x00;
  flag = 0;
  
  SCON = 0x52 ;     		  	// 8bit, noparity, 1stopbit
  T3CON = 0x85;
  T3FD = 0x02D;
 }

void memDump(unsigned int sadr, unsigned int eadr)
 {
  unsigned char xdata *xramPtr;

  printf("       +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F\n");
  
  sadr&= 0xff00;
  for(xramPtr=(char xdata *)sadr; xramPtr <= (char xdata *)eadr; xramPtr+= 16)
   {
    printf( "%04P %02BX %02BX %02BX %02BX ",xramPtr,*(xramPtr+0),*(xramPtr+1),*(xramPtr+2),*(xramPtr+3));
    printf(      "%02BX %02BX %02BX %02BX "        ,*(xramPtr+4),*(xramPtr+5),*(xramPtr+6),*(xramPtr+7));
    printf(      "%02BX %02BX %02BX %02BX "        ,*(xramPtr+8),*(xramPtr+9),*(xramPtr+10),*(xramPtr+11));
    printf(      "%02BX %02BX %02BX %02BX\n"       ,*(xramPtr+12),*(xramPtr+13),*(xramPtr+14),*(xramPtr+15));
    if (RI)
     if (getchar()==0x03) break;
   }
  printf("\n");
 }
  


void prepareDma(void)
 {
  unsigned int xdata *xdatPtr;
  
  for(xdatPtr=0; xdatPtr<=0x7ffd; xdatPtr++)
   {*xdatPtr= 0x0000;}
  xdatPtr=0x7ffe; *xdatPtr=0xf000;
 }
 


void DmaSingle(void) 			// Single DMA Loop
 {
    
    ADCCON1=0x00; 				// Make sure ADC is in Power Down mode
    DMAL=0;
    DMAH=0;
    DMAP=0;
    prepareDma();
    ADCCON2=0x40; 				// Enable the DMA
    ADCCON1=0xA4; 				//  
    EA = 1;
    EADC = 1;
  
								// LAUNCH DMA conversion...  when finished, ADC interrupt will clear C
    CCONV = 1;   
    while (flag == 0)
	{printf("loop\n");}	
	
 } 



void DmaTimer2(void) 			// Timer 2 DMA Loop
 {
    DMAL=0;
    DMAH=0;
    DMAP=0;
    prepareDma();
  
    RCAP2L=0x0F6;				// sample period = 2 * T2 reload prd
    RCAP2H=0x0FF;  				//   = 2*(10000h-FFF6h)*5.722us
    TL2=0x0F6;					//   = 2*9*5.722us
    TH2=0x0FF;					//   = 102.99us
    
	ADCCON2=0x40; 				// Enable the DMA
    ADCCON1=0xA6;
    EA = 1;
    EADC = 1;

    TR2 = 1;       				//Start DMA
	 while (flag == 0)
	{printf("loop\n");}	
}



void DmaExternal(void)			// DMA on an external trigger
 {
   ADCCON1=0x00;				// Make sure ADC is in Power Down mode
    DMAL=0;
    DMAH=0;
    DMAP=0;
    prepareDma();
    ADCCON2=0x40;				// Enable the DMA
    ADCCON1=0xA4;				//  
    EA = 1;
    EADC = 1;
  
    ADCCON1 ^= 0x01;			// enable hardware CONVST pin
    while (flag == 0)
	{printf("loop\n");}	
 } 


void dispHelp(void)
 {
  printf("Dump XRAM ssss - eeee	D 0xssss 0xeeee:\n");
  printf("DMA operation Continuous Conversions DMA LOOP	M\n");
  printf("TIMER2 DMA Operation	N\n");
  printf("External Trigger Operation 0\n");
  printf("\n");
 }                                                                              

 /********************************************************************
MAIN function
********************************************************************/
void main(void)
 {
  unsigned char command;
  unsigned int sadr;
  unsigned int eadr;

  init832();

  printf("   \n\n"); //Sync
  printf("Check Program - Type ? for help\n");

  while(1)
   {
   flag=0; 
   printf("Cmd>"); scanf("%c",&command); command=toupper(command);
     if(command != 'D') printf("\n");

    switch (command)
     {
      case 'D': scanf("%x %x",&sadr,&eadr);
                memDump(sadr,eadr);
                break;
      case '?': dispHelp(); break;
      case 'M': DmaSingle(); break;
      case 'N': DmaTimer2(); break;
      case 'O': DmaExternal(); break;
      
      default:  if(command!=0x0d) printf("Unknown command 0x%02BX- Hit ? for help\n\n",command);
     }  
   }
 }

