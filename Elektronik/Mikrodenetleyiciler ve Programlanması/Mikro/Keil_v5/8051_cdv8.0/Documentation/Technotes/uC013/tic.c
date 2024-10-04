/* Program: TIC.C																							*/
/* Author: ADI Applications                                                         */
/* Date: 22 Oct 2001                                                                */
/*                                                                                  */

/* Description: 
/*This program implements a frequency measurement using the Timer 2 counter pin P1.0     */
/*Timer 0 is used as our reference base, Timer 0 overflows every 10ms and a frequency    */  
/*measurement is made every second. 																	  */	
/*A full description of this is given in technote uC013 at www.analog.com/microconverter */
/*                                                                                       */

#include<aduc824.h>								//Include ADuC824 SFR definition file

													   //Status Flags
bit one_second 			 = 0x20;         	//Bit is set once 100 T0 overflows, i.e. 1sec elapsed
bit t0_counting 			 = 0x21; 			//Bit is set while 100 T0 overlows are being counted

data unsigned char overflow_left;	 		//Count of T0 overflows remaining until 1 sec elapsed
data unsigned int ufrequency;					//Frequency result
data double ufreq;
data unsigned int t2rollover;					//No of Timer 2 rollovers, allows higher frequency range
static data double error=0;

ext0_isr() interrupt 0 using 2
{
error = ((ufreq-34465)/1000);
}

tic_isr() interrupt 10 using 2
{
TR2 = 0;
one_second = 1;		 							//Status flag now updated to indicated frequency result is present
 
}



/*Timer 2 Interrupt Service Routine */
timer_2_isr() interrupt 5 using 2     		//use register bank 2
{
t2rollover++;										//if timer2 has rolled over frequency measurement will be inaccurate unless we keep track of number of rollovers
TF2=0;												//Clear timer2 roll over flag
}



/* External LCD Display routine */
extern void display(double value, int flag,int t2rollover, double error);
/* Function Decleration for Function which obtains the frequency */
void get_frequency(void);

void main(void) 
{ 
display(0,0,0,0);									//Initialise display 
t2rollover = 0;                           //Ensure value is 0 to start with
PLLCON = 0x00 ;                           //CD=0 i.e. Core running at 12.582912MHz
TMOD = 0x01 ;										//Initialise T0, 16bit autoreload mode, not started yet
T2CON = 0x02 ;										//Initialise T2, 16bit counter mode, not started yet
INTVAL = 0x01;

IEIP2 = 0x04;										//Enable TIC interrupt

EX0 = 1;
ET0 = 1;												//Enable T0 interrupt
ET2 = 1;												//Enable T2 interrupt
EA  = 1;												//Enable Global interrupts

one_second = 0; 		     						//Status flags both set to zero
t0_counting = 0; 

while(1)												//Do forever 
{ 
if(!t0_counting )									//If not waiting on the 100 T0 timeouts, Start T0 
{ 
overflow_left = 100;		 						//100*10ms = 1sec 
one_second = 0; 									//Clear this flag to be sure 
t0_counting = 1;			 						//Set flag to indicate counting T0 timeouts
TIMECON = 0x05B;
TR2 = 1; 											//Start Timer 2
} 
if( one_second )		                     //If flag indicates 1Sec elapsed calculate frequency
{ 
t0_counting = 0; 									//Clear flags
one_second = 0; 

ufrequency = ((TH2 << 8) + TL2); 			//Frequency is the value in TH2,TL2 + 65535*no to T2 rollovers
display(ufrequency,1,t2rollover,error);         //Send this info to display routine
  
  ufreq = ufrequency;
  
  
  RCAP2L = 0x00;									//Re-initialise timer values back to zero for next measurement
  RCAP2H = 0x00;
  TL2 = 0x00;
  TH2 = 0x00;
  t2rollover = 0;

  TMOD = 0x01 ;									//Initialise T0, 16bit autoreload mode, not started yet
  T2CON = 0x02 ;									//Initialise T2, 16bit counter mode, not started yet
} 
}														//end while 
}														//end main  
 
 



 
