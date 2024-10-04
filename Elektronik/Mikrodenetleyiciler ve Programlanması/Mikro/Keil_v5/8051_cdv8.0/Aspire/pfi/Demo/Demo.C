//======================================================================
//
// Author        : ADI - Apps
//
// Date          : May 2002
//
// File          : Blink.c
//
// Description   : Blink LED with delay for MicroConverter DEMO
//		   Delay is controlled by variable length.
//		   i.e. delay = 100ms x length
//		   100ms is calculated based on a 11.0592MHz crystal
//
//======================================================================

#include <stdio.h>
#include <reg51.h>			// Generic 8051 registers

extern void delay(int length);         	// Function defination


int length=1;				// Global variable

// INT0 Interrup: Increases the variable length by 1 each interrupt until 10 is reached
void INT0_int () interrupt 0 using 2
{
	length++;			// Increase delay
	if (length > 10)
		{
		length = 1;             // If length is at 10 reset to 1
		}
}


// Main routine
void main(void)
{
EX0 = 1;				// Enable INT0 Interrupt
IT0 = 1;				// INT0 interrupt edge triggered
EA = 1;					// Enable Interrupts

for(;;)					// Loop Forever
{
P3 ^= 0x10;                         	// Complement P3.4
delay(length);                          // Call delay routine
}

}



