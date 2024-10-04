//********************************************************************
//
// Author        : ADI - Apps            www.analog.com/MicroConverter
//
// Date          : November 2001
//
// File          : TIC.c
//
// Hardware      : ADuC836
//
// Description   : Demonstrates a use of a timer interval counter for 
//		counting longer intervals than the standard 8052 
//		timers are capable of.
//		
//		The LED will, on power up, flash at 12Hz. By pressing
//		the external interrupt button INT0 the counter will 
//		count how long the button is pressed correct to 
//		1/128th of a second. When released the program will 
//		flash the light at the measured time correct only to
//		the nearest unit (1/128s, seconds, minutes or hours)
//		rounded DOWN.
//		eg) If the button was pressed for 0.91000s the light
//		would complement every 0.90625s (less than 1 second
//		therefore it measures in 1/128s and the nearest unit 
//		less than 0.91000s is 0.90625s). However if the light
//		was on for 1.6s it complements every 1s as the nearest
//		unit is now the second.
//		Pressing the INT0 button again will record a new 
//		time interval which will flash the light in the same
//		way.
//********************************************************************

#include <stdio.h> 
#include <ADuC836.h>

sbit LED = 0x0B4;

void int_0 () interrupt 0
{
	//LED ^= 1;
    TIMECON &= 0xFE;  
    TIMECON |= 0x01;
	while (INT0 == 0);
	TIMECON &= 0xFD;
                        
   	if (SEC ==0 && MIN == 0 && HOUR ==0) 
	{
		INTVAL = SEC;
		TIMECON = 0x00;
		TIMECON = 0x03; 
	}
	
	if (SEC !=0 && MIN == 0 && HOUR ==0) 
	{
		INTVAL = SEC;
		TIMECON = 0x00;
		TIMECON = 0x13; 
	}

	if (MIN !=0 && HOUR ==0) 
	{
		INTVAL = MIN;
		TIMECON = 0x00;
		TIMECON = 0x23; 
	}

	if (HOUR !=0) 
	{
		INTVAL = HOUR;
		TIMECON = 0x00;
		TIMECON = 0x33; 
	}
}

void TIC_int () interrupt 10
{
 	LED ^= 1;
}

void main (void)
{
	int i;
//Configure Time Interval Counter  
	TIMECON = 0x03;
    INTVAL = 0x0A;

//Configure External Interrupt
	IT0 = 1;		// edge trig for int0
    EX0 = 1;		// enable external interrupt (int0)
	IEIP2 = 0x04;   // enable TIC interrupt
    EA = 1;			// enable interrupts

	while (1)
	{
		LED^=0;
		for (i = 0; i < 10000; i++) {}
	}
}
