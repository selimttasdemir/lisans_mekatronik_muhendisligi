//====================================================================
//
// Author        : ADI - Apps
//
// Date          : November 2001
//
// File          : TempUart.c
//
// Hardware      : ADuC836
//
// Description   : This Program takes a temperature measurement every
//                 second from the on-chip temp sensor and sends the
//                 temp in degrees Celcius up the UART to the PC where
//                 it can be read using hyperterminal
//====================================================================

#include <stdio.h> 
#include <ADuC836.h>

void main (void)
{	
		int i, temp;

		//UART config        
		T3CON = 0x82;
        T3FD = 0x12;
        SCON = 0x52;

        ADCMODE = 0x10;	// ENABLE AUX Mode - Power down 
        ADC1CON = 0x20; // USE INTERNAL REFERENCE PTAT(+) --> PTAT(-) BIPOLAR MODE Fixed +/- 2.5V range 

	printf("____________________________________\nAnalog Devices MicroConverter ADuC834\nTemp Sensor Demo Routine\n");

  
	while(1)
	{	
		RDY1 = 0;
        ADCMODE = 0x12;
		while (RDY1 == 0);	// wait for result	
		temp = ADC1H-128; 		      
		printf("\n\n");
		printf("%d degrees C\n", temp);
	    for (i = 0; i < (10000); i++) {}
	}
}
