//====================================================================
//
// Author        : ADI - Apps
//
// Date          : 17 October 2003
//
// File          : Tim2_AR.c
//
// Hardware      : ADuC845, ADuC847, ADuC848
//
// Description   : Flashes LED on P3.4 every approx 20Hz
//____________________________________________________________________

#include <stdio.h>
#include <ADuC845.h>	//Use <ADuC847.h> or <ADuC848.h> if using an ADuC847 or ADuC848 part.

sbit LED = 0x0B4;

void interrupt_0 () interrupt 5
{
        LED ^= 1;
        TF2 = 0;
}


void main (void)
{
    ET2 = 1;
   	TL2 = 0x0;
	TH2 = 0x67;
	RCAP2L = 0x0;
    RCAP2H = 0x67;

    EA = 1;
	T2CON = 0x04;

	while(1);
}
