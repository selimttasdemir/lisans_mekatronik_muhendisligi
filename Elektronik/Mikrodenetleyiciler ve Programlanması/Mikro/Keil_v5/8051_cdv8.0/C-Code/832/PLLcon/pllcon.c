//********************************************************************
//
// Author        : ADI - Apps            www.analog.com/MicroConverter
//
// Date          : April 2002
//
// File          : pllcon.c
//
// Hardware      : ADuC832
//
// Description   : Demonstrates that the CPU can run at different 
//               speeds determined by the CD bits in the PLLCON SFR. 
//               2 to the power of CD (a 3 bit number), is the divider 
//               ratio that determines the clock frequency at which 
//               the CPU will run. (CD=0 =>fcore=16.777216MHz, 
//               CD=7 => fcore=131.072kHz) 
//
//	             The program turns on and off the LED.
//               With the higher frequency (CD=0 =>fcore=16.77MHz)
//				 the LED toggles at about 40Hz.
//				 By pressing the INT0 button the CD bit is 
//               incremented (CD=1 =>fcore=8.38MHz) and the LED will 
//               toggle at half the frequency as before. At the 
//               minimum frequency (CD=7, fcore=131kHz) the LED 
//               toggles at 0.320Hz. By pressing INT0 button again 
//               CD rolls over to 0 again and the LED
//		         toggles at 40Hz again.
//
//********************************************************************

#include <stdio.h> 
#include <ADuC832.h>

sbit LED = 0x0B4;

void DELAY(int length);
void interrupt_0 () interrupt 0
{
	if (PLLCON==0x07)
	{PLLCON=0x00;}
	else
	{PLLCON++;}
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
		DELAY(1700);
	}
}	

void DELAY(int length)
{
while (length >=0)
    length--;
}
