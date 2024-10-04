/* Author        : ADI - Apps            www.analog.com/MicroConverter

 Date          : April 2002

 File          : ADCcont.c

 Hardware      : ADuC832

 Description   : Performs ADC conversions in continuous mode at a
                 rate of 30.840KSPS (assuming an 2.097152 Mclk).
                 Outputs ADC results via UART.  Continuously
                 flashes LED.
                 All rate calculations assume an 2.097152MHz Mclk. */

#include<stdio.h>
#include<aduc832.h>

sbit LED = 0x0B4;

void adc_int() interrupt 6{
	printf("%02BX%02BX\n",ADCDATAH,ADCDATAL);
	return;
			  }

void DELAY(int length);
			  

void main(void)

{
int CHAN = 0;

T3CON=0x082;
T3FD= 0x02D;
SCON   = 0x052;



/* PRECONFIGURE... */

ADCCON1 = 0x0B0;      // power up ADC /32 + 1 acq clock
ADCCON2 = CHAN ;      // select channel to convert

/*LAUNCH CONTINUOUS CONVERSIONS...*/

EA = 1;               // enable interrupts
EADC = 1;             // enable ADC interrupt
CCONV = 1;            // begin continuous conversions

/* CONTINUE WITH OTHER CODE... */
	
for (;;)
	{
	DELAY(2);
	LED ^= 1;             // blink (complement) the LED
        }

// the micro is free to continue with other tasks (flashing the LED in
// this case) while the ADC is continuously converting, and results
// are being handled by the ADC interrupt service routine.

}

void DELAY(int length)
{
while (length >=0)
    length--;
}
