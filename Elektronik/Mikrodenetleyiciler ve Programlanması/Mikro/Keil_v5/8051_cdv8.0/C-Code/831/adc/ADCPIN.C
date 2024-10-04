/*;********************************************************************
;
; Author        : ADI - Apps            www.analog.com/MicroConverter
;
; Date          : May 2002
;
; File          : ADCpin.asm
;
; Hardware      : ADuC831
;
; Description   : Performs hardware pin driven ADC conversions and
;                 outputs results on UART.  Continuously flashes
;                 LED (independently of ADC routine) at approximately
;                 5Hz.
;		
;*********************************************************************/

#include<stdio.h>
#include<aduc831.h>
void DELAY(long int);		// function prototype

void adc_int() interrupt 6{
	printf("%02BX%02BX\n",ADCDATAH,ADCDATAL);
	return;
			  }


sbit LED = 0x0B4;               // P3.4

void main(void)
{
int CHAN = 0;

/*set up UART */
T3CON = 0x085;
T3FD = 0x08;
SCON   = 0x052;

/*PRECONFIGURE...*/

ADCCON1 = 0x080;		// power up ADC
ADCCON2 = CHAN;			// select channel to convert

/*LAUNCH CONTINUOUS CONVERSIONS...*/

EA = 1;              		// enable interrupts
EADC = 1;		        // enable ADC interrupt
ADCCON1 |= 0x01;		// enable hardware CONVST pin

/*CONTINUE WITH OTHER CODE...*/

for(;;)
{
LED ^= 1;
DELAY(3400);
}

/*
 the micro is free to continue with other tasks (flashing the LED in
 this case) while the ADC is converting, synchronously to the
 external CONVST pin.  results are being handled by the ADC
 interrupt service routine.*/
}

void DELAY(long int length)
{
while (length >=0)
    length--;
}

