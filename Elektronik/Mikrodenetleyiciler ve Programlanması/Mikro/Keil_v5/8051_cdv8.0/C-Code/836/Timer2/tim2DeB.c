//====================================================================
//
// Author        : ADI - Apps
//
// Date          : November 2001
//
// File          : Tim2DeB.c
//
// Hardware      : ADuC836
//
// Description   : Code example to show how the debugger can be 'halted'.
//                 i.e. if user code does not appear to be executing
//                 correctly and seems to have missed the breakpoints
//                 then you can halt (stop) the ADuC834 from running
//                 and examine where code is being executed from.
//
//                 The debugger uses timer 2 as the baudrate generater
//                 on the ADuC834. When timer 2 is used as a baudrate
//                 generator it does not generate timer 2 interrupts 
//                 using the TF2 flag. However the EXF2 flag can still
//                 be used to generate a 3rd external interrupt. Usually
//                 this extra option is not used however.
//
//                 In order to halt the ADuC834 the following code must
//                 be included in code before it is assembled. A 
//                 breakpoint must be set on the RETI instruction of 
//                 the TIMER 2 ISR. Hence if the code goes 'missing' 
//                 and the T2EX pin (Pin 2) grounded then a Timer 2 
//                 interrupt will occur hitting your breakpoint. Single
//                 stepping over the RETI instruction will show you 
//                 where the code was executing.
//
//                 NOTE: On the ADuC834 evalutaion board the T2EX pin
//                 appears at J3.7. A ground connection is provided 
//                 at J2.8 directly across from it. Hence connecting
//                 a link here will cause the timer 2 interrupt.
//
//                 The following code example shows how this approach
//                 could be used around the simple blink routine                 
//____________________________________________________________________

#include <stdio.h> 
#include <ADuC836.h>

sbit LED = 0x0B4;
int value = 1;

void int0 () interrupt 0
{
    value++;
}

void timer2_int () interrupt 5
{
    EXF2 = 1;
}

void main (void)
{	
	int i;
    T2CON = 0x08; 
    ET2 = 1;
   	EA = 1;
        
	IT0 = 1;
    EA = 1; 
    EX0 = 1;
		
	while(1)
	{
        LED ^= 1;
        for (i = 0; i < (value*1000); i++) 
		{}
	}
}
