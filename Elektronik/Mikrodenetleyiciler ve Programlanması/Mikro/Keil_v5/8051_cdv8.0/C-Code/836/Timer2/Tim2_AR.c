//====================================================================
//
// Author        : ADI - Apps
//
// Date          : November 2001
//
// File          : Tim2_AR.c
//
// Hardware      : ADuC836
//
// Description   : Flashes light every 256*128 machine cycles (@ 4Hz
//                 for core freq = 1.573MHz) using timer 2 in Auto 
//                 Reload Mode. 
//____________________________________________________________________

#include <stdio.h> 
#include <ADuC836.h>

sbit LED = 0x0B4;

void interrupt_0 () interrupt 5
{
        LED ^= 1;
        TF2 = 0;
}


void main (void)
{
    ET2 = 1;
   	TL2 = 0x00;    
	TH2 = 0x80;    
	RCAP2L = 0x00; 
    RCAP2H = 0x80;

    EA = 1;
	T2CON = 0x04;

	while(1);
}
