//======================================================================
//
// Author        : ADI - Apps
//
// Date          : April 2004
//
// File          : int0_Blink.c
//
// Hardware		 : ADuC845, ADuC847, ADuC848
//
// Description   : Blink LED with delay for MicroConverter DEMO
//			Delay is controlled by variable length.
//                 Pressing the INT0 button on the eval board increases
//                 the value of the 'length' variable which when multiplied
//		   by some value (in this case 2000) becomes the delay such
//		   that the LED can be seen to flash.
//
//======================================================================

#include <stdio.h>
#include <ADuC845.h>			// ADuC845 registers.
					//To run this on an ADuC847 or ADuC848 simply
					//change this include file to <ADuC847.h> or ADuC848.h>

int length=1;				// Global variable
int del = 1;

// INT0 Interrup: Increases the variable length by 1 each interrupt until 10 is reached
void INT0_int () interrupt 0 using 2
{
	length++;			// Increase delay
	if (length > 10)
		{
		length = 1;     // If length is at 10 reset to 1
		}
}

void delay(int);
// Main routine
void main(void)
{
EX0 = 1;				// Enable INT0 Interrupt
IT0 = 1;				// INT0 interrupt edge triggered
EA = 1;					// Enable Interrupts
for(;;)					// Loop Forever
	{
	P3 ^= 0x10;             // Complement P3.4
	del=length*2000;        //multiply length by some value (2000 in this case) such
				// 		that the LED can be seen to flash
	delay(del);          // Call delay routine
	}
}

void delay(int del)      // Delay routine
{
while (del >=0)
    del--;
}



