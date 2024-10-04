//********************************************************************
//
// Author        : ADI - Apps            www.analog.com/MicroConverter
//
// Date          : Feb 2003
//
// File          : 836uart.c
//
// Hardware      : ADuC836
//
// Description   : sample program that performs ADC conversions in
//                 continuous mode and sends results to a PC via the
//                 UART.
//		
//********************************************************************

#include <stdio.h> 
#include <ADuC836.h>

sbit LED = 0x0B4;

void ADC_int () interrupt 6
{
	LED ^= 1;
	printf("\n\n");
	printf("%bX%bX",ADC0H,ADC0M);  
    RDY0 = 0;
}

void main (void)
{

	//Configure UART 
    T3CON = 0x82;
    T3FD = 0x12;
    SCON = 0x52;

	//CONFIGURE ADC AND START CONVERTING....
	SF = 0x200; 
    ADC0CON = 0x45;
    EADC = 1;
    EA = 1;
    ADCMODE = 0x23;	// continuous conversion on Main channel on main channel

	//WAIT FOR INTERRUPTS....
	while(1);
}
        
