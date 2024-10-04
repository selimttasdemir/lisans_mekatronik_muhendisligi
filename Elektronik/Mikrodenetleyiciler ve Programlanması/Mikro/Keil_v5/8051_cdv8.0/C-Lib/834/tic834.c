//tic834.c
/*	This program demonstrates the TIC functions TicCfg(), TicGo(), TicVal(), TicHr(), TicMin(), TicSec() and
TicHth().
*/
#include<ADuC834.h>			//SFR definition file.
#include"lib834.h"  	//Function and variable declaration file.
#include<stdio.h>

char	cTFlag;				//Flag set by TIC interupt.

void ticint(void) interrupt 10 using 0
	{
	cTFlag = 1;
	T0 = !T0;
	TIMECON &= 0x0fb;		//Clear interupt flag.
	}

void main(void)
	{
	UrtCfg(0x22,-41);		//UrtCfg configures UART (2400 baud).
	PllWcd(2);				//PllWcd writes CD bits (2).

	printf("\n\nADuC816/24/34 TIC Demonstration Program\n");
	printf("=======================================\n");
	TicCfg(0);
 	printf("255 hour mode selected and ");
 	TicGo(23, 59, 55, 00);
	printf("time set to 23h59m55s00.\n");
	printf("Time now: %02bdh%02bdm%02bds,%02bd.\n",TicHr(),TicMin(),TicSec(),TicHth());
	printf("Wait 10.5 secs...\n");
	PllDly(10500);
	printf("Time now: %02bdh%02bdm%02bds,%02bd.\n",TicHr(),TicMin(),TicSec(),TicHth());
 	TicVal(10,1);
	printf("Interrupt enabled on 10 counts of SEC counter.\n");
 	cTFlag = 0;
	printf("Interrupt flag set to 0.\n");
	printf("Wait 7 secs...\n");
	PllDly(7000);
	printf("Flag is now %bd.\n",cTFlag); 
	printf("Wait 4 secs and for interrupt.\n");
	PllDly(4000);
	printf("Interrupt flag is now %bd.\n",cTFlag); 
	printf("Time now: %02bdh%02bdm%02bds,%02bd.\n",TicHr(),TicMin(),TicSec(),TicHth());
	TicCfg(1);
	printf("Timer stopped.\n");
	printf("After further 4 secs delay time stays 0.\n");
	PllDly(4000);
	printf("Time now: %02bdh%02bdm%02bds,%02bd.\n",TicHr(),TicMin(),TicSec(),TicHth());
	while(1)
		{ 	}
	}
	


