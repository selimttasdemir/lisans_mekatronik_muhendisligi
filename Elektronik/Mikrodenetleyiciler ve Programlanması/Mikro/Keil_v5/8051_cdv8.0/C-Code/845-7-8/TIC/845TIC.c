//********************************************************************
//
// Author        : ADI - Apps            www.analog.com/MicroConverter
//
// Date          : November 2003
//
// File          : 845TIC.c
//
// Hardware      : ADuC845, ADuC847, ADuC848
//
// Description   :To configure TIC as a 20 second interval counter
//********************************************************************

#include <stdio.h>
#include <ADuC845.h>  //To use the ADuC847 or ADuC848 simply change this header file to
					  //<ADuC847.h> or <ADuC848.h>

sbit LED = 0x0B4;

void delay(int length)
{
while (length >=0)
    length--;
}

void TIC_int () interrupt 10
{
      	LED ^=1;                 			//Blink LED twice.
       	delay(5000);
       	LED ^=1;
       	delay(5000);
       	LED ^=1;
       	delay(5000);
       	LED ^=1;

}

void main (void)
{

//Configure Time Interval Counter
        IEIP2 = 0x04;   		// enable TIC interrupt
   	EA = 1;				// enable interrupts

	TIMECON = 0xD0;                 //Count in seconds, clear TCEN
        INTVAL = 0x14;                  //Value to count to. This is dependent on the count type
        				//selected in TIMECON. Since seconds were selected, then INTVAL
        				//should count seconds (not hundreths of seconds or minutes or hours)
        				//In this example, the preloaded time is not used and the
        				//required count time is 20 seconds (INTVAL = 14h)

	//SEC = 0x10;                     //Timer preloaded to 1 minutes, 10 seconds....NOT USED
	//MIN = 0x01;
	//hour = 0x02
        delay(10000);                	//Delay to allow TIC registers be written to. TIC registers are clocked
        				//from the 32kHz clock and so reading from or trying to use TIC registers
        				//too quickly can have unforeseen results.
       	TIMECON	= 0xD3;                 //Start counting, enable INTVAL counter & TIC counter

	while (1);   			//Wait here for TIC interrupt.

}
