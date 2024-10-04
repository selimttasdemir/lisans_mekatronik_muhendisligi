//********************************************************************
//
// Author        : ADI - Apps            www.analog.com/MicroConverter
//
// Date          : 16 October 2003
//
// File          : 847uart.c
//
// Hardware      : ADuC845, ADuC847, ADuC848 (taking into account fact that the ADuC848 is a 16-bit ADC)
//
// Description   : sample program that performs ADC conversions in
//                 continuous mode and sends results to a PC via the
//                 UART. Operates on the RTD (PT100) on the eval board
//				   via Ain1->Ain2 ADC inputs. The switches (S4) on the
//				   eval board must be set as follows to get this program
//				   working correctly...RTD AIN1, RTD AIN2, RTD REFIN+
//				   and RTD REFIN- must be set to ON. All other switches
//				   must be off.
//********************************************************************

#include <stdio.h>
#include <ADuC845.h>    //To use this with an ADuC847 or ADuC848, simply change the
					    //header file to <ADuC847.h> or <ADuC848>

sbit LED = 0x0B4;

void ADC_int () interrupt 6
{
	LED ^= 1;
	printf("\n\n");
	printf("%bX%bX%bX",ADC0H,ADC0M,ADC0L);  //Remove ADC0L when using the ADuC848
    RDY0 = 0;
}

void main (void)
{
 			//Configure UART
    T3CON = 0x83;	//9600 Baud rate
    T3FD = 0x12;
    SCON = 0x52;

			//CONFIGURE ADC AND START CONVERTING....
    ICON = 0x01;	//Turn on IEXC1 source to drive RTD.
    SF = 0x200;
    ADC0CON1 = 0x22;	//Full Buffer, Unipolar, 80mV range.
    ADC0CON2 = 0x4A;	//Refin+/-, Ain1->Ain2
    EADC = 1;           //Enable ADC Interrupt
    EA = 1;             //Enable Global Interrupts
    ADCMODE = 0x23;	// continuous conversion on Main channel on main channel

	//WAIT FOR INTERRUPTS....
	while(1);
}

