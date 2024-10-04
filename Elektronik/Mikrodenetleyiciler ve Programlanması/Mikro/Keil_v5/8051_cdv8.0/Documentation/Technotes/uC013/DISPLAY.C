/* Program: LCD.C																							*/
/* Author: ADI Applications                                                         */
/* Date: 22 Oct 2001                                                                */
/*                                                                                  */
#include<aduc824.h>
#include<stdio.h>

sbit LCD_RS = 0x0A6;											//Register Select line = port 2.6
sbit LCD_WR = 0x0A7;                               //Read/Write line = port 2.7
sbit LCD_EN = 0x0B6;                               //Enable line = port 3.6
sfr  LCD_DATA = 0x080;                             //Data bus = port 0
sbit busy = 0x087;                                 //busy bit = db7

void sendcmd(unsigned);										//Function which sends commands to the LCD controller
void chkbusy(void);                                //Checks the busy status of the LCD controller
void sendchar(unsigned);                           //Function which sends text to the LCD display

void display(double value,int flag,int t2rollover, double error) //Main routine, takes in the value to display, init flag, and timer2 rollover
{
data unsigned char buf[16];								//Databuffer for text to be displayed
data unsigned char ends[4]=("um K");					//units 
data unsigned char abv[2];                         //Hz
data int y=0,type=0;											//variables used later

 
if (flag == 0)                                     //If initialising the display just write the heading on the LCD screen
{	sendcmd(0x038); 											//Functiun set
	sendcmd(0x06);												//Entry set
	sendcmd(0x02);											   //Home
	sendcmd(0x0C);												//Display on, cursor, etc

   		sprintf(buf, "FREQUENCY ");					//Move text into the buffer
			y=0;
			while (buf[y]!='\0')								//Sends text out to LCD display, one charachter at a time
			    {
			    sendchar(buf[y]);
			    y++;
			    }
}		


if (flag == 1)													//If flag = 1 then just display the frequency result
{
sendcmd(0xC0);                           				//the start of the 2nd line       

value += (t2rollover*65535);   							//Calculate true frequncy allowing for timer 2 rollover
if (value>=10000)
{value -= ((value/100)*error);}

for(;;)															//Formatting loop which calculates units required
 {
 if ((value/10)>=(100)) 		
     {type = 3;
      value=(value/1000);
      break;}
            
 if ((value/10)>=(0.1))
     {type = 2;
      break;}	
      	
 if ((value*1000) >1)                                    
     {type = 1;
      if (value*100>100)
	 {type=2;
	  break;}
      value=(value*1000);
	  break;}

 if ((value*1000000) >1)
     {type = 0;
      value=(value*1000000);
      break;}
  type=2;
  break;	
  }

abv[0]='H';                              				//Units Hz
abv[1]='z';
abv[2]='\0';

sprintf(buf, "%0.3f%c%s      ",value,ends[type],abv); //Converts the result into one string
        y=0;
	while (buf[y]!='\0')											//Displays string on 2nd line of display
		{
	       	sendchar(buf[y]);
		 		y++;
		}
}
}


/* Function to check the busy status of the LCD controller */
void chkbusy(void)
{
data int i; 
data unsigned temp;
LCD_DATA = 0x0FF;									 // configure as ip's
LCD_RS = 0x00;	  									 // CLEARS RS LINE
LCD_WR = 0x01;	 									 // SETS R/W LINE
i++;
i++;
i++;
i++;
do{
LCD_EN = 1;	  										  // CLOCKS E HIGH
i++;
i++;
i++;
i++;
temp = LCD_DATA;
i++;	
i++;
i++;
LCD_EN = 0;      										// CLOCKS E LOW
i++;		
i++;		
} while (busy == 0);
}


/* Function which sends commands out to the LCD controller */
void sendcmd(unsigned cmd)
{
data int i;
chkbusy();    										// CHECKS BUSY FLAG
LCD_DATA = cmd; 									// SENDS TO PORT 0
LCD_WR = 0;     									//CLEARS R/W LINE
LCD_RS = 0;     									// CLEARS RS LINE
i++;
LCD_EN = 1;											// CLOCKS E HIGH
i++;		
i++;
i++;
i++;
i++;
LCD_EN = 0; 										// CLOCKS E LOW
}
		
void sendchar(unsigned ch)
{
data int i;
chkbusy();
LCD_DATA = ch;  									// SENDS TO PORT 0
LCD_WR = 0;											// CLEARS R/W LINE
LCD_RS = 1;											// SETS RS LINE HIGH FOR DATA
i++;
LCD_EN = 1;											// CLOCKS E HIGH
i++;		
i++;
i++;
i++;
i++;
LCD_EN = 0; 										// CLOCKS E LOW
}


