/*********************************************************************

 Author        : ADI - Apps            www.analog.com/MicroConverter

 Date          : May 2002

 File          : ADCsingl.c

 Hardware      : ADuC831

 Description   : Performs repeated single ADC conversions and moves
                 results to UART. Sets the red LED on the eval
                 board upon completion of each conversion.  A new
                 conversion is innitiated every 200ms.

		
*********************************************************************/

#include<stdio.h>
#include<aduc831.h>

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
T3CON = 0x085;
T3FD = 0x08;
SCON   = 0x052;

/* PRECONFIGURE...*/

ADCCON1 = 0x80;                        // power up ADC
ADCCON2 = CHAN;				// select channel to convert
EA	= 1;				// enable interrupts
EADC	= 1;				// enable ADC interrupt

/* PERFORM REPEATED SINGLE CONVERSIONS...*/

for(;;)
{
DELAY(7000);
LED  ^= 1;				// Complement LED
SCONV = 1;				// Perform single conversion
}

}

void DELAY(int length)
{
while (length >=0)
    length--;
}


