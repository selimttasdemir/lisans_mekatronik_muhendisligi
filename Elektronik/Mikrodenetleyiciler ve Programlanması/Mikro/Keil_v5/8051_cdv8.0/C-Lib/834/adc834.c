//********************************************************************
//
// Author        : ADI 
//
// Date          : November 2001
//
// File          : Adc834.c
//
// Hardware      : ADuC834
//
// Description   : This program demonstrates the Sigma Delta ADC functions 
//	Software communicates with a terminal at 9600 baud. Program guides 
//	user through selection of options ending with a command list. Then 
//	continuous conversions are started and displayed. While measurements 
//	are output the user can issue single key commands to change settings. 
//	Also included are a help and wait option.
//		
//********************************************************************

#include<ADuC834.h>		// SFR definition file.
#include"lib834.h"		// Function and variable declaration file.
#include<stdio.h>
#include<ctype.h>		//"ctype.h"
#include<stdlib.h>		//"stdlib.h"

void PrintHelp(void);

void main(void)
	{
	long	lMain;		//Latest main ADC result.
	long	lOld;		//Previous main ADC result.
	long	lAux;		//Aux ADC result.
	char data *cp1;		//Pointer to raw result buffer.		
	char 	c1;		//Loop counter.
	char	cErr;		//Value returned by AdcErr();
	char	cPin;		//Pin selection flag ('3' pressed).
	char	cXref;		//Main ADC external ref flag ('X' pressed).
	char	cAxRef;		//Aux ADC external ref flag ('R' pressed).
	char	cMode;		//Conversion mode.
	char	cUp;		//Main ADC unipolar flag ('U' pressed).
	char	cAuP;		//Aux ADC unipolar flag ('P' pressed).
	char	cRn;		//Range value for main ADC (number pressed).
	char	cSf;		//Decimation factor SF.
	char	cE1;		// '<', '=' or '>' for main ADC.
	char	cE2;		// '<', '=' or '>' for aux ADC.
	char	cGet;		//Autoranging flag ('G' pressed).
	double	dReal;		//Used for voltage calculation.
	double	dEr;		//Difference between successive main conversions.
	int	iAux;		//Aux raw result using AdcGet();
	char	pcSf[5];
	
	cRn = 7;
	cSf = 69;
	cAuP = cUp = cPin = cAxRef = cXref = 0;

	UrtCfg(0x12,-20);	//configures UART.
	PllWcd(1);		//writes CD bits.

	printf("\n\nADuC816/24/34 ADC Demonstration Program\n");
	printf("=======================================\n");
	printf("Step 1 of 5:\n");		//Select main ADC input pin.
	printf("\tPress 3 for Main input on AIN3/4.\n");
	printf("\tOther key for Main input on AIN1/2.\n");
  	c1 = _getkey();
  	if(c1=='3')	cPin = 1;		// Save choice?
	
	printf("Step 2 of 5:\n");		//Select main reference.
	printf("\tPress X for external 2.5V reference.\n");
	printf("\tOther key for internal reference.\n");
  	c1 = _getkey();
  	if(c1=='X')	cAxRef = cXref = 1;	// Save choice?
	
	printf("Step 3 of 5:\n");	//Select which full scale callibration.
	printf("\tPress c for chip full-scale callibration.\n");
	printf("\tApply full scale and press C for system full-scale callibration.\n");
	printf("\tOther key for no full-scale callibration.\n");
  	c1 = _getkey();
  	if((c1&0xdf)=='C')				//If c or C.
  		{
  		if(c1=='c')	cMode = 5;		// Which callibrate?
   		else	cMode = 7;
		AdcCfg(0x40*cXref+cRn+0x10*cPin,0x40*cAxRef,255);
		AdcGo(cMode);				// Callibrate full scale.
		while(((cErr = AdcErr())&0xc0));	// Wait until done.
		}
 	
	printf("Step 4 of 5:\n");	//Select which full scale callibration.
	printf("\tPress z for chip zero callibration.\n");
	printf("\tApply 0V and press Z for system zero callibration.\n");
	printf("\tOther key for no zero callibration.\n");
  	c1 = _getkey();
  	if((c1&0xdf)=='Z')				//If z or Z.
  		{
  		if(c1=='z')	cMode = 4;		// Which zero;
   		else	cMode = 6;
		AdcCfg(0x40*cXref+cRn+0x10*cPin,0x40*cAxRef,255);
		AdcGo(cMode);				// Callibrate zero.
		while(((cErr = AdcErr())&0xc0));	// Wait until done.
		}
	printf("Step 5 of 5:\n");	//Select options during cenversions.
	PrintHelp();			//Display instructions to user.
  	cMode = 3;			//Continuous conversion mode.
	AdcCfg(0x40*cXref+8*cUp+cRn+0x10*cPin,0x40*cAxRef+8*cAuP,cSf);
				//Configure as per user selections.
       	AdcGo(cMode);	//Start continuous conversion.
	while(1)
		{
 		if(UrtBsy()&1)		//If key pressed.
  			{	// Act on command.
  			while((c1 = _getkey())=='w');	//Wait if 'w'.
    			if(c1=='U')		cUp = 1;      				
       			else if(c1=='u')	cUp = 0;      				
       			else if(c1=='X')	cXref = 1;      				
       			else if(c1=='x')	cXref = 0;      				
       			else if(c1=='P')	cAuP = 1;      				
       			else if(c1=='p')	cAuP = 0;      				
       			else if(c1=='R')	cAxRef = 1;      				
       			else if(c1=='r')	cAxRef = 0;      				
       			else if(c1=='G')	cGet = 1;      				
       			else if(c1=='g')	cGet = 0;
			else if(c1=='h')	PrintHelp();
       		      	else if(c1<'8')		cRn = c1&7;
       			else if(c1=='s')
       	       	        	{
				printf("\nSF=");
       	       			gets(pcSf,4);
       	                        cSf=atoi(pcSf);
       	                        }
	   			//Configure as per user selections.
			AdcCfg(0x40*cXref+8*cUp+cRn+0x10*cPin,
     				0x40*cAxRef+8*cAuP,cSf);
       			AdcGo(cMode);	//Start continuous conversion.
     			}
		while(((cErr = AdcErr())&0xc0));
 		if(cErr&8)	cE1 = (lMain<0) ? '<' : '>';
       		else	cE1 = '=';	// Main in range?
  		if(cErr&4)	cE2 = (lAux<0) ? '<' : '>';
    		else	cE2 = '=';	// Aux in range?
 		lOld = lMain;
       		if(cGet)		//If autorange
       			{
       		        lMain = AdcGet(&iAux);	// get autorange result.
       	         	lAux = (long)iAux<<16;
       		        }
		else			// else read continuous results.
 			{
			lMain = AdcRd(0);
			lAux = AdcRd(1);
			cp1 = AdcAdr();
  			}
    			//Convert lAux to volts and display.
   		dReal = 1.28*((double)lAux/0x7fffffff)*(1+cAxRef);
		printf("Aux:%c%+9.6f%V ***",cE2,dReal);
    			//Convert lMain to volts and display.
   		dReal = 1.28*((double)lMain/0x7fffffff)*(1+cXref);
		printf(" Main%c%+9.6f%V ***",cE1,dReal);
    			//Convert change in lMain to volts and display.
    		dEr = 1.28*((double)(lMain-lOld)/0x7fffffff)*(1+cXref);
		printf(" Step:%+7.1fuV",dEr*1000000.0);
 			//Display SF, RN and cErr.
 		printf(" SF:%3d RN:%c Err:%02bx",(int)SF,(ADC0CON&7)|'0',cErr);
  			//Display user selected settings.
    		printf(" %c%c%c%c%c\n",cGet?'G':'g',(ADC1CON&8)?'P':'p',
     			(ADC1CON&0x40)?'R':'r',(ADC0CON&8)?'U':'u',
     			(ADC0CON&0x40)?'X':'x');
	}	}

void PrintHelp(void)
	{
	printf("To change settings during conversions press one of:\n");
	printf("\t U for main unipolar mode (UNI0=1).\n");
	printf("\t u for main bipolar mode.\n");
	printf("\t X for main external reference (XREF0=1).\n");
	printf("\t x for main internal reference.\n");
	printf("\t P for aux unipolar mode (UNI1=1).\n");
	printf("\t p for aux bipolar mode.\n");
	printf("\t R for aux external reference (XREF1=1).\n");
	printf("\t r for aux internal reference.\n");
	printf("\t G to use AdcGet() (Autorange).\n");
	printf("\t g to use AdcGo() and AdcRd() (Manual range).\n");
	printf("\t 0 to 7 for range (RN2-0).\n");
	printf("\t s to start changing decimation factor SF.\n");
	printf("\t w to wait.\n");
	printf("\t h for help.\n");
//	printf("Press a key for more help.\n");
//	_getkey();
	printf("Results line will show:\n");
	printf("\tAux: aux measurement *** Main: main measurement *** ,\n");
	printf("\tStep: difference between last two main results,\n");
	printf("\tSF: Decimation factor,   RN: Range of main ADC,\n");
	printf("\tErr: Error code for main and aux ADC,\n");
	printf("\t5 characters indicating user selections,\n");
	printf("Press a key to end help.\n");
	_getkey();
	}
	
