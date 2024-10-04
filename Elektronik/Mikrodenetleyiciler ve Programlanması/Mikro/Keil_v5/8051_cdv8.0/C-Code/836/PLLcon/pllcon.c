//********************************************************************
//
// Author        : ADI - Apps            www.analog.com/MicroConverter
//
// Date          : November 2001
//
// File          : pllcon.c
//
// Hardware      : ADuC836
//
// Description   : Demonstrates that the CPU can run at different 
//               speeds determined by the CD bits in the PLLCON SFR. 
//               2 to the power of CD (a 3 bit number), is the divider 
//               ratio that determines the clock frequency at which 
//               the CPU will run. (CD=0 =>fcore=12.58MHz, 
//               CD=7 => fcore=98.3kHz) 
//
//	             The program turns on and off the LED approx every 
//               70,000 machine cycles. With the higher frequency 
//		         (CD=0 =>fcore=12.58MHz) the LED toggles at about 
//               16Hz. By pressing the INT0 button the CD bit is 
//               incremented (CD=1 =>fcore=6.3MHz) and the LED will 
//               toggle at half the frequency as before. At the 
//               minimum frequency (CD=7, fcore=700kHz) the LED 
//               toggles at 0.125Hz. By pressing INT0 button again 
//               CD rolls over to 0 again and the LED
//		         toggles at 16Hz again.
//
//********************************************************************

#include <stdio.h> 
#include <ADuC836.h>

sbit LED = 0x0B4;
int i;

void interrupt_0 () interrupt 0
{
	LED ^= 1;
	i = 9999;
	PLLCON++;
	PLLCON &= 0x07;
}
void main (void)
{
	PLLCON = 0x00;
	IT0 = 1;
    EX0 = 1;            
                               
	EA = 1;              

	while(1)
	{
		LED ^=1;
		for (i = 0; i < 10000; i++) 
		{
		}
	}
}	
