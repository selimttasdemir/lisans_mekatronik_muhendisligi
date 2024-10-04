//********************************************************************
//
// Author        : ADI - Apps            www.analog.com/MicroConverter
//
// Date          : 17 October 2003
//
// File          : pllcon.c
//
// Hardware      : ADuC845, ADuC847, ADuC848
//
// Description   : Demonstrates that the CPU can run at different
//               speeds determined by the CD bits in the PLLCON SFR.
//               2 to the power of CD (a 3 bit number), is the divider
//               ratio that determines the clock frequency at which
//               the CPU will run. (CD=0 =>fcore=12.58MHz,
//               CD=7 => fcore=98.3kHz)
//
//               Every time the INT0 button is pressed (i.e. every time
//		 and external interrupt is received on INT0) the CD bits
//		 in the PLLCON SFR are incremented by 1 thereby halving
//		 the core frequency. Once the CD bits = 7 the next INT0
//		 interrupt resets the CD bits back to 0.
//
//********************************************************************

#include <stdio.h>
#include <ADuC845.h>	//To use the ADuC847 or ADuC848 parts simply change the header file to
						//<ADuC847.h> or <ADuC848.h>

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
