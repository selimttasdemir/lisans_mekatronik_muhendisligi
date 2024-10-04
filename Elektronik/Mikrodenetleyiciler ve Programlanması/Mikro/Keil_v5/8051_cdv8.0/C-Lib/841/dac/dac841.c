//dac841.c
/*
Author: Eckart Hartmann Date:15/10/2003
Description of Software: 
	This program demonstrates the DAC functions 
DacCfg() , DacOut() ,
	See PrintHelp() for details.
	This code assumes a 11.059MHz crystal and 9600 baudrate.
Development progress: Dac841.df
*/
#include\"..kei841.h\" //; SFR definition file .
#include\"..lib841.h\" //; Function and variable declaration file .
#include<stdio.h>	//"stdio.h"
#include<ctype.h>	//"ctype.h"
#include<stdlib.h>	//"stdlib.h"

void PrintHelp(void);

void main(void)
	{
	char 	c1;		//Temporary variable.
	char	cXRef;		//External ref flag ('R' pressed).
	char	cChan;		//Selected channel.
	int	iVal;
	int	i1;

 UrtCfg(0x03,0x8608); // UrtCfg configures UART.
	PrintHelp();
	DacCfg(0x1f);
	while(1)
		{
 		if(UrtBsy()&1)		//If key pressed.
  			{	// Act on command.
  			while((c1 = _getkey())=='w');	//Wait if 'w'.
    			if(c1=='r' || c1=='R')
      				{	//Ramp.
       			        putchar(c1);
	    			if(c1=='r')	cChan = 0;      				
       				else	cChan = 1;
       		      		for(i1=0; i1<0x1000; i1++)
       	                                DacOut(cChan,i1);
        		      	}
        	        else if(c1=='f' || c1=='F')
                 		{	//Full scale.
       			        putchar(c1);
                 		if(c1=='f')	cXRef = 0;
 	       			else	cXRef = 1;
	       		        DacCfg(0x1f+0x60*cXRef);
				}
			else if(c1=='h')	PrintHelp();
  			else if(c1=='0' || c1=='1')
    				{
       			        putchar(c1);
       			        putchar(':');
       				cChan = c1-'0';
       		                iVal = (getchar()-'0')*1000;
       	                 	iVal += (getchar()-'0')*100;
       	                 	iVal += (getchar()-'0')*10;
       	                 	iVal += (getchar()-'0');
                                DacOut(cChan,iVal);
      			}	}
 		}	
	}
void PrintHelp(void)
	{
	printf("To change settings during conversions press one of:\n");
	printf("\t f for Vref full scale.\n");
	printf("\t F for AVdd full scale.\n");
	printf("\t r to ramp DAC0 full scale.\n");
	printf("\t R to ramp DAC1 full scale.\n");
	printf("\t 0 plus 4 digits for that output on DAC0.\n");
	printf("\t 1 plus 4 digits for that output on DAC1.\n");
	printf("\t h for this help screen.\n");
	printf("\t w to wait.\n");
	printf("Press a key to end help.\n\n");
	_getkey();
	}
	
