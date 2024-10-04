//********************************************************************
//
// Author        : ADI - Apps            www.analog.com/MicroConverter
//
// Date          : 27 Jan 2004
//
// File          : uartc.c
//
// Hardware      : ADuC845, ADuC847, ADuC848
//
// Description   : Receives a character via the UART from Hyperterminal
//		   and transmits back to Hyperterminal via the UART the
//		   original entered character + 1 and +2.
//********************************************************************

#include <stdio.h>
#include <ADuC845.h>  //To use the ADuC847 or ADuC848 simply change the header file to
					  //<ADuC847.h> or <ADuC848.h>

sbit LED = 0x0B4;

void main (void)
{
   char  MyBuf;

    	T3CON = 0x83;	//Configure UART for 9600 Baud rate
    	T3FD = 0x12;
    	SCON = 0x50;

	for(;;)
		{
 		while (! RI) {}		// Wait for character to be entered via Hyperterminal
 	        RI = 0;	 		// Clear the RI interrupt
 	        			// Character is available in SBUF

        	SBUF = SBUF+1;		// Transmit SBUF+1 via UART
        	while(! TI) {}         	// Wait for completion of Tx
                TI=0;			// Clear the Tx interrupt

     		MyBuf = SBUF;	    	//
        	SBUF = MyBuf+2;     	// Transmit MyBuf+2 via UART
	    	while(! TI) {}          // Wait for transmission completion
		TI =0;			// Clear the interrupt
		}
}

