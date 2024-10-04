//======================================================================
//
// Author        : ADI - Apps
//
// Date          : 5 November 2001
//
// File          : adctrig.c
//
// Description   : Flash led an initial rate of 100ms
//		  Pressing INTO triggers single conversion
//		  The ADC result is written to external memory
//		  The delay rate is increased
//		  The program waits for the next INTO to repeat the 
//		  above sequence
//
//======================================================================

#include <stdio.h>
#include <ADuC834.h>

int loop;

void interrupt_0 () interrupt 0
{	
  	unsigned xdata test[3];
	ADCMODE=0x22;
	while ( RDY0==0 )
	{
	}	
	RDY0 = 0;
	test[0] = ADC0L;
	test[1] = ADC0M;
	test[2] = ADC0H;
	loop++;
}

void main (void)
{	
	int i,j;
	
	ADCMODE = 0x20;
	ADC0CON = 0x47;
	IT0 = 1;
	EA = 1;
	EX0 = 1;
	loop = 0x00;
	
	while(1)
	{
		P3 ^= 0x10;
		for (i = 0; i < 1000 ; i++)
		{
			for (j = 0x00; j <= loop ; j++);
		}
	}
}
