/*********************************************************************

 Author        : ADI - Apps            www.analog.com/MicroConverter

 Date          : October 2003

 File          : ADCtimer.c

 Hardware      : ADuC841

 Description   : Performs ADC conversions at 10KSPS in Timer2 mode.
                 P3.3 indicates convesion complete. Continuously
                 flashes LED (independently of ADC routine) at
                 approximately 10Hz.
                 All rate calculations assume an 11.0592MHz crystal
		
********************************************************************/

#include<stdio.h>
#include<aduc841.h>

sbit    adcled = 0x0B3  ;
sbit	LED = 0x0B4;		//P3.4 drives red LED on eval board 

void adc_int() interrupt 6{
  	        adcled ^= 1;
		return;
			  }                                           
void DELAY(int);
void main(void)
{

int CHAN=0;
/*PRECONFIGURE...*/
ADCCON1 = 0x09E;		// power up ADC & enable Timer2 mode
ADCCON2 = CHAN ; 		// select channel to convert
RCAP2L  = 0x0D2; 		//sample period = 2 * T2 reload prd
RCAP2H  = 0x0FF; 		
TL2	= 0x0D2; 		
TH2	= 0x0FF;		

/*LAUNCH Timer2 DRIVEN CONVERSIONS...*/
EA	= 1;		        // enable interrupts
EADC	= 1;			// enable ADC interrupt
TR2	= 1;			// run Timer2

/*CONTINUE WITH OTHER CODE...*/
for (;;)
{
LED ^= 1;
DELAY(3200);
}

/*; the micro is free to continue with other tasks (flashing the LED in
 this case) while the ADC operation is being controlled by Timer2
 and the ADC interrupt service routine.*/

}

void DELAY(int length)
{
while (length >=0)
    {length--;}
}

