//********************************************************************
//
// Author        : ADI - Apps            www.analog.com/MicroConverter
//
// Date          : April 2002
//
// File          : TIC.c
//
// Hardware      : ADuC832
//
// Description   : Demonstrates the use of the Time Interval Counter to
//			       Wake Up the MicroConverter. The Time Interval Counter
//				   is set up to wake up the part after 10 seconds and toggle
//				   the L.E.D. on the evaluation board (P3.4). The part is 
//				   then placed back in power down for another 10 seconds						 	
//********************************************************************

#include <stdio.h> 
#include <ADuC832.h>

sbit LED = 0x0B4;

void TIC_int () interrupt 10
{
 	LED ^= 1;
 	TIMECON = 0x13;		// clear TII bit
}

void main (void)
{

//Configure Time Interval Counter  
   TIMECON = 0x13; 	// configure the Time Interval Counter to count seconds
   INTVAL = 0x0A;    // 10 seconds

//Configure External Interrupt
	IEIP2 = 0xA4;   // enable TIC interrupt
    EA = 1;			// enable interrupts

	while (1)
	{
	PCON = 0x22;	// power down mode
	}
}
