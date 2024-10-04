/* 
Author		: MicroConverter Apps

Date		: April 2004

Hardware	: ADuC845, ADuC847

Description	: Performs conversions on an external RTD connected as shown in the diagram below, and 
			  returns the result via the UART to a PC. Use Hyperterminal to view the results.

			  This progrqam will also work on an ADuC848 except account must be taken of the fact that
			  the ADuC848 ADC is only 16-bits. Therefore the calculations will have to be edited as will 
			  the output code. 
			  
	
	  ADuC845/7: RTD sensors
RTD CONNECTIVITY & CALCULATION
                    |-------|
          o---------| RTD#1 |-------o-------- Ain1
          |         |-------|       |
          |                         o-------- IEXC1(Ain7).....200uA
          |
          0-------------------------o-------- Ain2
          \                         |
          /                         o-------- Refin+
          \5k56 RTD load
          /
          |
          o---------------------------------- Refin-
          |
         AGND
 RTD equation = Trtd = (Rrtd-100ohm)/0.3851ohm/'C
    therefore at 0ohm Trtd = (-100)/0.3851 = -259.67'C
 Voltage across 5k6 resistor = 200uA x 5k56 = 1.112V
    Using 80mV unipolar range we get (1.112V x 80mV)/2.5v = 35.56mV
 therefore with 35.56V across RTD Trtd =
             Trtd = [(35.56mV/200uA) - 100]/0.3851  = +202.03'C
 Total temperature span = -259.67'C -> +202.03'C = 461.70
 The offset is the 0ohm figure of -259.67'C

ADuC845/847 Eval board S4 switch settings: RTD Ain1, RTD Ain2, RTD REFIN+, RTD REFIN- should be ON.
All other switches should be OFF.
*/


#include<ADuC845.h>        	//To use ADuC847 simply change this include file to <ADuC847.h>
#include<stdio.h>

long ADC=0;            		       		// raw ADC conversion result
float RTD=0;       				// final result

void serial_init()
{
  T3CON = 0x83;         			//configure timer 3...
  T3FD  = 0x12;          			//...for 9600 baud
  SCON  = 0x52;
}


void main (void)
{
      	serial_init();        			//Configure serial port for 9600 Baud
  	ADC0CON1 = 0x22;      			// Full Buff, unipolar, 0->80mV
  	SF       = 0x45;      			// ADC rate = 20Hz
 	ADCMODE  = 0x24;			// Ofs Cal
  	ADCMODE  = 0x25;			// Gain cal

       	ADC0CON1 = 0x22;    			//Full Buff, unipolar, 80mV
   	ICON     = 0x01;    			//Enable RTD#1 current source (IEXC1 on pin 11/Ain7)


	for(;;)					//Do forever
  	{
  	//RTD measurement and temperature calculation
    	  ADC0CON2 = 0x4A;    			// Refin+/-, Ain1->Ain2
    	  ADCMODE  = 0x22;    			// Single conv, primary ADC....Conv on RTD on Ain1
    	  while(! RDY0){}     			// Wait for RDY0 Flag
    	  ADC = ADC0H*0x10000+ADC0M*0x100+ADC0L;// raw ADC data
    	  RTD = 461.7*ADC/16777215.0-259.67;   // gain & offset
  	   	        			//Based on [Trtd = (Rrtd - 100ohms)/0.3851ohms/'C] sensor
    	  RDY0     = 0;       			// clear ready bit...
          printf("%+.2fC\n", RTD);

       	}
}
