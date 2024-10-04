//pll834.c
/* Pll834.c
This program demonstrates the PLL functions PllDly(), PllWCd() and PllRCd()
The test waits 1s to ensure PLL is stable, reads the CD bits and
then checks the CD bits. If an error occurs P3.4 pulses every second.
Then 0ms, 1ms, 255ms, 256ms, 257ms, 32.6s,33s and 65.535s are measured off with 
P3.4 toggling after each time period. The periods can thus be checked on an 
oscilloscope. If the test has passed P3.4 flickers continuously.
*/

#include<ADuC834.h>	//SFR definition file.
#include"lib834.h"  //Function and variable declaration file.
#include<stdio.h>

void PllErr(char cDly);
void flicker(void);

void main(void)
	{
	PllDly(1000);
	PllWcd(2);
	if(PllRcd()!=2)	PllErr(3);
	T0 = 0;
	PllDly(0);
	T0 = !T0;
	PllDly(1);
	T0 = !T0;
	PllDly(255);
	T0 = !T0;
	PllDly(256);
	T0 = !T0;
	PllDly(257);
	T0 = !T0;
	PllDly(32600);
	T0 = !T0;
	PllDly(33000);
	T0 = !T0;
	PllDly(65535);
	T0 = !T0;
	while(1)	flicker();
	}
	
void PllErr(char cDly)
{
	while(1)
        {
		PllDly(cDly*1000);
		T0 = 1;
		PllDly(100);
		P3 = 0x00;
		}	
}
	
void flicker(void)
{
	char c1;	
    for(c1=0; c1<32; c1++)
        {
		PllDly(30);
		T0 = 1;
		PllDly(30);
		P3 = 0x00;
		}
}


