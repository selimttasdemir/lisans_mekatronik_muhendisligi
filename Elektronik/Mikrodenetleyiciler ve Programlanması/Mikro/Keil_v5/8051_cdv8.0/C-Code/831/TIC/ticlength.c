//********************************************************************
//
// Author        : ADI - Apps            www.analog.com/MicroConverter
//
// Date          : April 2002
//
// File          : TIC.c
//
// Hardware      : ADuC831
//
// Description   : Demonstrates the use of the Time Interval Counter to
//					count an interval of 96 hours		
//					A message is displayed constantly on the hyperterminal window
//					after the time has elapsed.
//					Note: This code can be chaged to 96second period by
//					setting Timecon=0x01B; to show its use 	
//********************************************************************

#include <stdio.h> 
#include <ADuC831.h>

sbit LED = 0x0B4;

void TIC_int () interrupt 10
{
	TIMECON=0x00;
	LED ^= 1;
}

void main (void)
{
//Configure the baud rate 9600
	T3CON = 0x85;
	T3FD  = 0x08;
	SCON  = 0x52;

//Configure Time Interval Counter  
	TIMECON = 0x03B; 	// configure the Time Interval Counter to count a single period in hours
					  //set to 0x01B to time 96 seconds



	INTVAL = 0x60;    // 96 hours

//Configure External Interrupt
	IEIP2 = 0xA4;   // enable TIC interrupt
   	EA = 1;			// enable interrupts

	PCON = 0x22;	// enterpowerdown
	while (1)
	{
	printf("96 Hour Have Elapsed\n");
	}
}



