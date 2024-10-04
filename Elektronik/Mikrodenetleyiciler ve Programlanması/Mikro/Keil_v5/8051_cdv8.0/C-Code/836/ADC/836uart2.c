//********************************************************************
//
// Author        : ADI - Apps            www.analog.com/MicroConverter
//
// Date          : Feb 2003
//
// File          : 836uart2.c
//
// Hardware      : ADuC836
//
// Description   : sample program that performs ADC conversions in
//                 continuous mode and sends results to a PC via the
//                 UART.  program also accepts commands from the PC
//                 via incoming characters on the UART.  an ASCII "0"
//                 innitiates a zero-scale calibration, and an ASCII
//                 "1" innitiates a full-scale calibration.
//		
//********************************************************************

#include <stdio.h> 
#include <ADuC836.h>

sbit LED = 0x0B4;
int recieved;

void delay(int length)
{
while (length >=0)
    length--;
}

void calzero()
{
	printf("\n\n");
	printf("Calibrating zero\n");
    RDY0 = 0;
    ADCMODE = 0x24;             
    while (RDY0 == 0);
    RDY0 = 0;
	printf("End of the calibration\n");
}

void calgain()
{    
	printf("\n\n");    
    printf("Calibrating gain\n");
	RDY0 = 0;
   	ADCMODE = 0x25;
    while (RDY0 == 0);
    RDY0 = 0;
	printf("End of the calibration\n");
}

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
	//CONFIGURE ADC
	SF = 0x200; 
    ADC0CON = 0x45;
	printf("press 0 for zero calibration\n");
	printf("press 1 for full-scale calibration\n");
	printf("else press another key to start continuous conversion\n");
	delay(1000);
	while(1)
	{
		recieved = getkey();
		switch (recieved)
		{
			case '0':	
			{
			EADC = 0;		// disable ADC interrupt
			EA = 0;			// disable interrupt
			calzero();	
			}
			case '1':	
			{
			EADC = 0;		// disable ADC interrupt
			EA = 0;			// disable interrupt
			calgain();	
			}
			default:{}
		}
		RDY0 = 0;
		EADC = 1;		// enable ADC interrupt
		EA = 1;			// enable interrupt
		ADCMODE = 0x23;	// start conversion in continuous mode
    	//while(1);		// wait for interrupt.
	}
}
       
 
