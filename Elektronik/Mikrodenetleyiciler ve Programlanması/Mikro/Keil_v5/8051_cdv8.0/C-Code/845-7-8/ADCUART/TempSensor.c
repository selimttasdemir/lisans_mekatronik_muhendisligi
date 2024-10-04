//********************************************************************
//
// Author        : ADI - Apps            www.analog.com/MicroConverter
//
// Date          : April 2004
//
// File          : TempSensor.c
//
// Hardware      : ADuC845
//
// Description   : sample program that performs single ADC conversions on
//				   the internal Temperature Sensor with a delay between
//				   samples defined by the TIC. The results (in degrees C)
//                 transmitted via the UART.
//				   Between conversions the part enters powerdown mode and is awoken
//				   by the TIC interrupt in 5 second intervals.
//
//Note: ADC1H contains the integer part of the temperature.
//      ADC1M & ADC1L contain the decimal parts of the temperature
//		result. Therefore divide the result by 65536d to get a
//      degree C result.
//This program will not work on an ADuC847 or ADuC848
//********************************************************************

#include <stdio.h>
#include <ADuC845.h>    	

sbit LED = 0x0B4;
long ADC=0;
float temperature=0;


void delay(int length)
{
while (length >=0)
    length--;
}

void TIC_int () interrupt 10
{
	ADCMODE = 0x12;		//ADC1 Enabled, Chop Enabled, Single conversion on Aux ADC
	while (! RDY1) {}
	ADC =   ADC1H*0x10000 + ADC1M*0x100 + ADC0L;    //Combine ADC data registers into one.
	temperature = (ADC - 0x800000)/65536.00;        //Subtract 800000h to remove bipolar offset and by
													//divide 10000h to convert to degrees C.
	printf("%+0.2fC\n", temperature);               //Output result to UART
	RDY1 =0;                                        //Clear the ADC interrupt

      	LED ^=1;                 		//Blink LED twice to indicate completion of conversion.
       	delay(10000);
       	LED ^=1;
       	delay(10000);
       	LED ^=1;
       	delay(10000);
       	LED ^=1;
}


void main (void)
{
 				//Configure UART
   	T3CON = 0x83;      		//9600 Baud rate
    	T3FD = 0x12;
    	SCON = 0x52;
        PCON = 0x10;		//ALE OFF
//Configure TIC
	IEIP2 = 0x04;   	//Enable TIC interrupt
	EA = 1;         	//Enable global interrupts
	TIMECON = 0xD0; 	//Count in seconds
	INTVAL =  0x05; 	//Count duration (5 second delay between temperature readings)
	delay(10000);		//Delay to allow TIC registers be written
		       		//Since TIC operates from 32.768kHz time must be given
				//to ensure the TIC registers are written to correctly.
	ADCMODE = 0x11;		//ADC1 enabled, Chop enabled, ADC Idle mode
        SF = 0x0FF;     	//ADC Speed, 5Hz
   	ADC1CON = 0x0E;		//Internal Vref, Bipolar, Tempsensor.
        TIMECON	= 0xD3;         //Start counting, enable INTVAL counter & TIC counter

	for(;;)                 //Endless loop
	{
        PCON = 0x12;		//ALE OFF & Powerdown mode until awakened by the TIC interrupt
	}

}

