//pll834.c
/*
Author: Eckart Hartmann Date:17/10/2003
Description of Software: 
	This program demonstrates the PLL functions:
PllDly() ,
PllWcd() and
PllRdd() .

The test waits 1s to ensure PLL is stable, reads the CD bits and
then checks the CD bits. If an error occurs P3.4 pulses every second.
Then 0ms, 1ms, 255ms, 256ms, 257ms, 32.6s,33s and 65.535s are measured off with 
P3.3 toggling after each time period. The periods can thus be checked on an 
oscilloscope. If the test has passed P3.4 flickers continuously.
Development progress: Pll814.df
*/
#include\"..kei842.h\" //; SFR definition file .
#include\"..lib842.h\" //; Function and variable declaration file .

void PllErr(char cDly);
void flicker(void);

void main(void)
	{
	PllDly(1000);
	PllWcd(2);
	if(PllRcd()!=2)	PllErr(3);
	P34 = 0;
	PllDly(0);
	P34 = !P34;
	PllDly(1);
	P34 = !P34;
	PllDly(255);
	P34 = !P34;
	PllDly(256);
	P34 = !P34;
	PllDly(257);
	P34 = !P34;
	PllDly(32600);
	P34 = !P34;
	PllDly(33000);
	P34 = !P34;
	PllDly(65535);
	P34 = !P34;
	while(1)	flicker();
	}
	
void PllErr(char cDly)
	{
	while(1)
        	{
		PllDly(cDly*1000);
		P34 = 1;
		PllDly(100);
		P3 = 0x00;
	}	}
	
void flicker(void)
	{
	char c1;
	
        for(c1=0; c1<32; c1++)
        	{
		PllDly(30);
		P34 = 1;
		PllDly(30);
		P3 = 0x00;
	}	}

