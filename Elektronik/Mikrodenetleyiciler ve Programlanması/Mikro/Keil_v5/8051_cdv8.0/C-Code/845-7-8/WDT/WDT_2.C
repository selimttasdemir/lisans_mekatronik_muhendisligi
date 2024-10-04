/*

  Author:		MicroConverter apps

  Date:		April 2004

  Hardware:	ADuC845, ADuC847, ADuC848

  Description:	To show the operation of a Watch Dog Timer refresh operation.
		The LED on P3.4 lights for a short time following the program start.
		The WDT is configured to generate an reset interrupt after 1 second (WDCON = 0x62;).
		The program then enters the while loop and turns off the LED (LED=1;). The FOR loop
		is set up to be slightly longer than the WDT time out (i<32768), which means that
		the WDT generates the reset before the refresh operation can occur causing the
		program to start again.

		If the for() loop inside the while() loop is decreased to i<32767 or less then
		the WDT never gets the chance to time out before it is refreshed causing the LED
		to stay off and the program stay in the while loop.

*/

#include <aduc845.h>    		//Defines ADuC845 register map, for ADuC847 or ADuC848 use
					// respective header file.
#include <stdio.h>

sbit	LED = 0x0B4;			// LED on P3.4 on QS eval board
int i;                                  //Variable used in the for() loop

void main(void) {
	LED = 0;        		//Turn LED ON
	for( i=0; i<30000; i++){}  	//Delay to see LED light
	EA = 0;

	WDWR = 1;			// Allow write to WDCON
	WDCON = 0x62;			// timeout=1000mS, WDT enable, Hardware Reset
	while (1)
        	{
		LED = 1;                // Turn LED OFF
		for(i=0; i<32768; i++){} // Delay. If value is =< 32767 the WDT refreshes and LED
					// stays OFF. If the delay is >= 32768, the delay is longer
					// than the WDT timeout and so the WDT causes a hardware
					// reset, the LED will be seen to turn on and off
        WDWR = 1;
	WDCON = 0x62;			//Refresh the WDT. If this refresh occurs before the WDT
					//times out the LED will stay off.
        }
}




