// dac834.c
// This program demonstrates the DAC functions DacCfg(),dacout()

#include<ADuC834.h>	        		// SFR definition file.
#include"lib834.h"			// Function and variable declaration file.
#include<stdio.h>
#include<stdlib.h>

void main(void)
{
	char	cPin,cRef,cAct,cOn,c1;
	char	pcDac[12];
	long	l1;
	
	cPin = cRef = cAct = cOn = 1;	// value per default
	UrtCfg(0x22,-41);				//UrtCfg configures UART (2400 baud). 
	PllWcd(2);						//PllWcd writes CD bits (2).
	
	printf("\n\nADuC816/24/34 DAC Demonstration Program\n");
	printf("=======================================\n");
 	printf("Press key:\n");
	printf("\t P for output on P1.7/DAC pin.\n");
	printf("\t p for output on P1.2/DAC pin.\n");
	printf("\t R for AVdd full scale.\n");
	printf("\t r for Vref full scale.\n");
	printf("\t N for output Normal.\n");
	printf("\t n to zero output.\n");
	printf("\t O for DAC power on.\n");
	printf("\t o for DAC power down.\n");
 	printf("\t Enter decimal DAC value [0-4095] ending with enter.\n");
  	while(!(UrtBsy()&1));				// Wait key.
	while(1)
		{
 		if(UrtBsy()&1)
  			{
    			c1 = _getkey();
       			if(c1=='P')	cPin = 1;	// Which command?      				
       			else if(c1=='p')	cPin = 0;      				
       			else if(c1=='R')	cRef = 1;      				
       			else if(c1=='r')	cRef = 0;      				
       			else if(c1=='N')	cAct = 1;      				
       			else if(c1=='n')	cAct = 0;      				
       			else if(c1=='O')	cOn = 1;      				
       			else if(c1=='o')	cOn = 0;
       		    else if((c1<='9' && c1>='0') || c1=='-')
       	       	     	{
       	            	putchar(c1);
       	             	pcDac[0] = c1;
       	       			gets(&pcDac[1],8);
       	                if((l1=atol(pcDac))>32767) l1 = 32767;
       	                else if(l1<-32768) l1 = -32768;
       	       			c1 = DacOut((int)l1)+'0';
       	                }
 				if(c1>2)	DacCfg(cPin*0x10+cRef*4+cAct*2+cOn);
       	        printf("Action:%c Value = %d DACCON:%bxhex\n",c1,DACH*0x100+DACL,DACCON);
       	     }
 		}	
}
	



