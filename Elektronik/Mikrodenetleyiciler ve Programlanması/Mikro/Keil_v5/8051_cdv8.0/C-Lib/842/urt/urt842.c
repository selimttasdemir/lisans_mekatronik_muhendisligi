//urt842.c
/*
Author: Eckart Hartmann Date:16/10/2003
Description of Software: 
This program demonstrates the UART functions UrtCfg() ,
UrtBsy() , getkey()
and putchar() .
Development progress: Urt834.df

_getkey and putchar in the standard c51s.lib are replaced by new versions.
The enhancements compared to Keil are that T1, T2 or the fractional divider
can be initialised for baudrate generation. Also odd, even or no parity 
can be chosen. No parity and two stop bits (mark parity) is also offered. 
Lastly an error indicator is provided.

This demonstration receives characters and when a newline is received it 
returns the string with slight modification. (Note that for some parity 
errors the newline character is not recognised and 22 characters must be 
entered.) This is repeated 4 times with no, even and odd parity and 2 
stop bits. Each one can use any of the timers at various baudrates by 
changing the parameters for UrtCfg() manually and recompiling.

Windows Hyperterminal can be used for the test with correct operation for
the correct parameters and failure for the others. Note though that the 
difference between 1 and 2 stop bits is normally not detected.

Correct operation is indicated by "Hello " then the characters sent. then
the value of parameter1 of UrtCfg in "pseudo hex".
*/
#include\"..kei842.h\" //; SFR definition file .
#include\"..lib842.h\" //; Function and variable declaration file .
#include<stdio.h>	//"stdio.h"
#include<ctype.h>	//"ctype.h"

void main(void)
	{
	char pcHW[30] = {"Hello World"};
	char c1;
	
 PllWcd(0); // PllWcd writes CD bits.
	UrtCfg(0x07,0x862d);
	printf("\nEnter strings terminated by Enter.\n");
	while(UrtBsy()!=2);	//Ensure printf complete.
	PllWcd(1);
	UrtCfg(0x12,-54);
	scanf("%22s",&pcHW[6]);
	if(cUrtVar&0x80)
		{
		PllWcd(0);
		while(!TI);
 PllDly(5); // PllDly to settle false start.
		UrtCfg(0x06,-108);
		puts("Parity off error");
		}
	c1 = 7;
	while(c1<22 && (pcHW[c1]!=0))	c1++;
    	pcHW[c1++] = ' ';
    	pcHW[c1++] = ((cUrtVar>>4)&0x0f)+'0';
    	pcHW[c1++] = (cUrtVar&0x0f)+'0';
    	pcHW[c1++] = '\n';
    	pcHW[c1++] = 0;
	puts(pcHW);

	PllWcd(0);
	UrtCfg(0x0e,-108);
	scanf("%22s",&pcHW[6]);
	if(UrtBsy()&0x80)
		{
		while(!TI);
		PllDly(5);	// False start settles.
		PllWcd(1);
		UrtCfg(0x16,-54);
		puts("Parity even error");
		}
	c1 = 7;
	while(c1<22 && (pcHW[c1]!=0))	c1++;
    	pcHW[c1++] = ' ';
    	pcHW[c1++] = ((cUrtVar>>4)&0x0f)+'0';
    	pcHW[c1++] = (cUrtVar&0x0f)+'0';
    	pcHW[c1++] = '\n';
    	pcHW[c1++] = 0;
	puts(pcHW);

	PllWcd(1);
	UrtCfg(0x19,-54);
	scanf("%22s",&pcHW[6]);
	if(UrtBsy()&0x80)
		{
		while(!TI);
		PllDly(5);	// False start settles.
		PllWcd(3);
		UrtCfg(0x36,-13);
		puts("Parity odd error");
		}
	c1 = 7;
	while(c1<22 && (pcHW[c1]!=0))	c1++;
    	pcHW[c1++] = ' ';
    	pcHW[c1++] = ((cUrtVar>>4)&0x0f)+'0';
    	pcHW[c1++] = (cUrtVar&0x0f)+'0';
    	pcHW[c1++] = '\n';
    	pcHW[c1++] = 0;
	puts(pcHW);

	PllWcd(2);
	UrtCfg(0x026,-27);
	scanf("%22s",&pcHW[6]);
	if(cUrtVar&0x80)
		puts("2 Stop bit error");
	c1 = 7;
	while(c1<22 && (pcHW[c1]!=0))	c1++;
    	pcHW[c1++] = ' ';
    	pcHW[c1++] = ((cUrtVar>>4)&0x0f)+'0';
    	pcHW[c1++] = (cUrtVar&0x0f)+'0';
    	pcHW[c1++] = '\n';
    	pcHW[c1++] = 0;
	puts(pcHW);
	printf("\nEnd. Press reset to restart.\n");
	while(1);
	}
