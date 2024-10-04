//********************************************************************
//
// Author        : ADI - Apps            www.analog.com/MicroConverter
//
// Date          : October 2003
//
// File          : PDown.c
//
// Hardware      : ADuC841
//
// Description   : Demonstrates a use of a timer interval counter to
//		wake the ADuC841 out of Power down mode after a user
//		specified Power down time.
//
//		The LED will, on power up, flash at 5Hz. After 5s
//		the ADuC841 will enter power down mode (the LED will 
//		stop flashing in the off position). 
//		
//		By pressing the external interrupt 0 button (INT0) or
//		when the user specified time runs out (20s in this 
//		example) the ADuC841 will wake up and continue 
//		blinking as before for 5s before entering power down
//		mode again.
//
//********************************************************************

#include <stdio.h> 
#include <ADuC841.h>

sbit LED = 0x0B4;

void DELAY(int);


void int0 () interrupt 0
{		                                                         
}

void TIC_int () interrupt 10
{		                                                         
}

void main (void)
{
	int i;
	IEIP2 = 0xA4;
    IT0 = 1;
    EX0 = 1;
	EA = 1; 

	while(1)
	{ 
   		for(i=0;i<500;i++)
		{
		DELAY(8000);
		LED ^= 1;
		}
			INTVAL = 0x14;
			TIMECON = 0x13;
        	LED = 1;    
        	PCON = 0x22;
            
        	TIMECON = 0x00;
	}
}

void DELAY(int length)
{
while (length >=0)
    length--;
}
