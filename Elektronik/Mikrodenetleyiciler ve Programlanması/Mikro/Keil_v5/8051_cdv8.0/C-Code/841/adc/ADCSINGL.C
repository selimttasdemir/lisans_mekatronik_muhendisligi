/*********************************************************************

 Author        : ADI - Apps            www.analog.com/MicroConverter

 Date          : October 2003

 File          : ADCsingl.c

 Hardware      : ADuC841

 Description   : Performs repeated single ADC conversions and moves
                 results to UART. 

		
*********************************************************************/

#include<stdio.h>
#include<aduc841.h>

sbit LED = 0x0B4;                //P3.4 drives red LED on eval board

void adc_int() interrupt 6{
	LED=1;
	printf("\n%02BX%02BX\n",ADCDATAH,ADCDATAL);
	return;
			  }
void DELAY(int);			// Function prototype
void main(void)
{
int  CHAN=0;

/* Set up UART */
T3CON = 0x086;
T3FD = 0x08;
SCON   = 0x052;

/* PRECONFIGURE...*/

ADCCON1 = 0x08C;      // power up ADC /32 + 4 acq clock
ADCCON2 = CHAN;				// select channel to convert
EA	= 1;				// enable interrupts
EADC	= 1;				// enable ADC interrupt

/* PERFORM REPEATED SINGLE CONVERSIONS...*/

for(;;)
{
SCONV = 1;				// Perform single conversion
while (LED==0){}
LED=0;
}

}




