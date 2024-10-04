//********************************************************************
//
// Author        : ADI - Apps            www.analog.com/MicroConverter
//
// Date          : April 2002
//
// File          : TIC.c
//
// Hardware      : ADuC832
//
// Description   : Demonstrates the use of the Time Interval Counter as
//				   a 24 hour Real Time Clock. The program asks the user to provide
//				   the current time and prints out the time every 10 seconds				 	
//********************************************************************

#include <stdio.h> 
#include <ADuC832.h>

sbit LED = 0x0B4;

void DELAY(int);
void TIC_int () interrupt 10
{
 	LED ^= 1;
 	TIMECON = 0x53;		// clear TII bit
 	
}

void main (void)
{
	int temp_hour,temp_min,temp_sec;
	char answer;
	//Configure the baud rate 9600
	T3CON = 0x82;
	T3FD  = 0x2D;
	SCON  = 0x52;
	

	printf("\nThe time is now %02BD:%02BD:%02BD\n",HOUR,MIN,SEC);
	printf("Do you wish to change the time? Y/N\n");
	scanf("%c",&answer);

	if (answer=='Y')
	{
		printf("\nEnter the current time in Hours:Mins:Seconds, then press a key to continue\n");
		scanf("%d:%d:%d",&temp_hour,&temp_min,&temp_sec);
	
		TIMECON = 0x01;	//errata fix for 832 TCEN must be 1 to reliably change SFRs
		SEC = temp_sec;
		MIN = temp_min;
		HOUR = temp_hour;
	}
//Configure Time Interval Counter  
	INTVAL = 0x0A;    // 10 seconds
    TIMECON = 0x53;   // configure the Time Interval Counter to count seconds in clock mode

//Configure External Interrupt
	IEIP2 = 0xA4;   // enable TIC interrupt
    EA = 1;			// enable interrupts

	while (1)
	{
	printf("\nThe time is now %02BD:%02BD:%02BD\n",HOUR,MIN,SEC);
	DELAY(1700);	// wait for tx to complete
	PCON = 0x22;	// power down mode
	}
}

void DELAY(int length)
{
while (length >=0)
    length--;
}
