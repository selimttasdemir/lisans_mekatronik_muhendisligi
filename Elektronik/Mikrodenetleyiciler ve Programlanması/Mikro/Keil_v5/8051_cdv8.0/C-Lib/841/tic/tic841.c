//tic841.c
/*
Author: Eckart Hartmann Date:15/10/2003
Description of Software: 
	This program demonstrates the TIC functions 
TicCfg() , TicGo() , TicVal() ,
TicHr() , TicMin() , TicSec() , TicHth() ,
Development progress: Tic834.df
*/
#include\"..kei841.h\" //; SFR definition file .
#include\"..lib841.h\" //; Function and variable declaration file .
#include<stdio.h>	//"stdio.h"
#include<ctype.h>	//"ctype.h"
#include<stdlib.h>	//"stdlib.h"

char	cTFlag;		//Flag set by TIC interupt.

void ticint(void) interrupt 10 using 0
	{
	cTFlag = 1;
	P34 = !P34;
//	TIMECON &= 0x0fb;	//Clear interupt flag.
	}

void main(void)
	{
 UrtCfg(0x03,0x8608); // UrtCfg configures UART (2400 baud).

	printf("\n\nADuC841 TIC Demonstration Program\n");
	printf("=======================================\n");
	TicCfg(0);
 	printf("255 hour mode selected and ");
 	TicGo(23, 59, 55, 00);
	printf("time set to 23h59m55,00\n");
	printf("\tTime now: %02bdh%02bdm",TicHr(),TicMin());
	printf("%02bd,%02bd.\n",TicSec(),TicHth());
	printf("Wait for 10.5s\n");
	PllDly(10500);
	printf("\tTime now: %02bdh%02bdm",TicHr(),TicMin());
	printf("%02bd,%02bd.\n",TicSec(),TicHth());
 	TicVal(10,1);
	printf("Interupt enabled at 10 counts of SEC counter. ");
 	cTFlag = 0;
	printf("Interupt flag set to 0. Wait 7s.\n");
	PllDly(7000);
	printf("\tInterupt flag is now %bd.",cTFlag); 
	printf("\tTime now: %02bdh%02bdm",TicHr(),TicMin());
	printf("%02bd,%02bd.\n",TicSec(),TicHth());
	printf("Wait 4s for interupt.\n"); 
	PllDly(4000);
	printf("\tInterupt flag is now %bd.",cTFlag); 
	printf("\tTime now: %02bdh%02bdm",TicHr(),TicMin());
	printf("%02bd,%02bd.\n",TicSec(),TicHth());
	TicCfg(1);
	printf("Timer stop and reload.\n");
	printf("\tTime now: %02bdh%02bdm",TicHr(),TicMin());
	printf("%02bd,%02bd.\n",TicSec(),TicHth());
	printf("After further 4s delay time unchanged.\n");
	PllDly(4000);
	printf("\tTime now: %02bdh%02bdm",TicHr(),TicMin());
	printf("%02bd,%02bd.\n",TicSec(),TicHth());
	printf("\n\n\tThe End.\n\n\n");
	while(1)
		{
 	}	}
	
