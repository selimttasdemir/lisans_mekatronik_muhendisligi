/*********************************************************************

 Author        : ADI - Apps            www.analog.com/MicroConverter

 Date          : October 2003

 File          : ADCsingl.c

 Hardware      : ADuC842

 Description   : Performs repeated single ADC conversions and moves
                 results to UART. Sets the red LED on the eval
                 board upon completion of each conversion.                 
                 All rate calculations assume an 2.097152MHz Mclk.
		
*********************************************************************/

#include<stdio.h>
#include<aduc842.h>

sbit LED = 0x0B4;                //P3.4 drives red LED on eval board

void adc_int() interrupt 6{
	printf("\n%02BX%02BX\n",ADCDATAH,ADCDATAL);
	return;
			  }
void DELAY(int);			// Function prototype
void main(void)
{
int  CHAN=0;

/* Set up UART */
T3CON = 0x083;
T3FD = 0x02D;
SCON   = 0x052;

/* PRECONFIGURE...*/

ADCCON1 = 0x0AC;                        // power up ADC
ADCCON2 = CHAN;				// select channel to convert
EA	= 1;				// enable interrupts
EADC	= 1;				// enable ADC interrupt

/* PERFORM REPEATED SINGLE CONVERSIONS...*/

for(;;)
{
DELAY(17000);
LED  ^= 1;				// Complement LED
SCONV = 1;				// Perform single conversion
while (ADCI == 0)
	{
	}				// wait for interupt
}

}

void DELAY(int length)
{
while (length >=0)
    length--;
}


