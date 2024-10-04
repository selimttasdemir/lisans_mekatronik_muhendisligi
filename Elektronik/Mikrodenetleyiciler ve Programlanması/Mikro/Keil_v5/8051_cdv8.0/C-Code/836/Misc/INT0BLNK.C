//======================================================================
//
// Author        : ADI - Apps
//
// Date          : 5 November 2001
//
// File          : Int0blnk.c
//
// Description   : Blinks LED continuously.
//                 200mSec period @ 50% duty cycle.
//		   Pressing Int0 delays LED toggle rate by 200mSec            
//
//======================================================================

   
#include <stdio.h>
#include <ADuC836.h>

void delay(int);

int  time=1000;

void ext_int() interrupt 0{
	time+= 500 ;
	return;
			  }

void main(void)
{

// Enable external interrupt 0
EX0 = 1;
// Enable global interrupts
EA = 1; 
// LED ON
// Loop forever
for(;;)
{
P3 = 0x10;
delay(time);
}

}


void delay(int length)
{
while (length >=0)
    length--;
}


