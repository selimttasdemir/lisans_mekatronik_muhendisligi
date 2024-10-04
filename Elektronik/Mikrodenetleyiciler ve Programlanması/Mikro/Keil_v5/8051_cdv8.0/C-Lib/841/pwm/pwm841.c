//pwm841.c
/*
Author: Eckart Hartmann Date:15/10/2003
Description of Software: 
	This program demonstrates the PWM functions 
PwmCfg() , PwmW16() , PwmW8() .
Development progress: pwm834.df .
*/
#include\"..kei841.h\" //; SFR definition file .
#include\"..lib841.h\" //; Function and variable declaration file .
#include<stdio.h>	//"stdio.h"
#include<ctype.h>	//"ctype.h"

	unsigned int uPwm;

//Use T1 interupt to ramp uPwm at constant rate.
void t0int(void) interrupt 1 using 0
	{
	uPwm += 4;
	P34 = !P34;
	}

void t1int(void) interrupt 3 using 0
	{
	uPwm += 4;
	P34 = !P34;
	}

void main(void)
	{
	unsigned int u1;
	double	dY;	//Factor to liniarize PWM in NRZ mode.

	PwmW8(0,0,0);
	uPwm = 16000;
	TH0 = 10;
	TL0 = 10;
        TMOD |= 0x2;	//T0 reload.
        TR0 = 1;	//Start T0.
        IE = 0x82;	//Enable T0 interupt.
/*	TH1 = 40;
	TL1 = 40;
        TMOD |= 0x20;	//T1 reload.
        TR1 = 1;	//Start T1.
        IE = 0x88;	//Enable T1 interupt.
*/ UrtCfg(0x02,-72); // UrtCfg configures UART.

	printf("\n\nADuC841 PWM Demonstration Program\n");
	printf("=======================================\n");
	printf("Connect 10k resistor from P2.6 (PWM out)\n");
	printf("via 100nF to ground. Connect oscilloscope\n");
	printf("accross capacitor. Repeat for P2.7.\n");
	printf("Oscilloscope will show slow ramps.\n");
	
    	dY = 0.001;	//Typical value.
    	PwmCfg(0x067);	//Dual RZ sigma delta at fosc/4.
	
	while(1)
		{
	        u1 = uPwm-(int)((uPwm-0x8000)*dY);
      		if(uPwm<0x8000)	u1 = uPwm;
		PwmW16(1,u1);	//Corrected.
      		PwmW16(0,uPwm);	//Plain.
//      		PwmW16(1,uPwm);	//Plain.
	}	}
	
