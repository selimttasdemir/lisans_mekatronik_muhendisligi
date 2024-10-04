/*
  Author:		MicroConverter Apps

  Date:		April 2004

  Hardware:	ADuC845, ADuC847, ADuC848. Use the respective header files

  Description:    Show the operation of the Watch Dog Timer.
		The LED lights for a time before starting to blink. The WDT is configured
		for a 1s delay and a hardware reset. While the LED is blinking the WDT
		times out and resets the part causing the sequemce to begin again.
		The WDT will always reset the part because there is no provision made to
		refresh the WDT as would nornally be the case. See WDT_2.C for an example of
		the WDT being refreshed.
*/

#include <aduc845.h>
#include <stdio.h>

sbit	LED = 0x0B4;		// LED on P3.4 on QS eval board
int i;

void main(void) {
	LED = 0;       		//Turn LED on
	for( i=0; i<30000; i++){} //Delay
	EA = 0;
	WDWR = 1;		// Allow write to WDCON
	WDCON = 0x62;		// timeout=1000mS, WDT enable, Hardware Reset
	while (1)               //Endless loop. Blink LED until WDT times out & resets the part.
         {
         	LED ^=1;                //Compliment LED
         	for(i = 0; i < 5000; i++) {}   //Delay
         }
}




