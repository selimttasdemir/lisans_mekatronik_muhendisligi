//****************************************************
// Module     : LedFlash
// Description: Flash Display LED on Eval Board
//***************************************************
#define MAX_DELAY 0x80

char P3_4 @ bit [0xB4];                			//define bit, Port 3 bit 4 'display' led
unsigned int length=0x10; 				// Global variable

void INT0_int (void);
void main(void);
unsigned char delay(unsigned char ucDelay); 	//defined in assembly module
void CheckLength(void);

//*********************************************
// Function:	INT0_int
// Input:	void
// output:	void
// description: INT 0 Interrup:
//              Increases the variable length by 0x10 each interrupt until 0x80 is reached
//*********************************************

void INT0_int (void) @0x03 //interrupt 0 vector
{
	length+=0x10;			// Increase delay
}
//*********************************************
// Function:	main
// Input:	void
// output:	void
//*********************************************
void main(void)
{
 unsigned char ucRet=0;

 EX0 = 1;				// Enable INT0 Interrupt
 IT0 = 1;				// INT0 interrupt edge triggered
 EA  = 1;				// Enable Interrupts

 for(;;)
    {
    CheckLength();
    ucRet=0;

    ucRet=delay(length);

    P3_4^=0x1; //XOR display LED with 1

    (void)delay(length);

    P3_4^=0x1; //XOR display LED with 1



    }

}

void CheckLength(void)
{
       if (length >MAX_DELAY)
 	{
    	length = 0x10;             // If length is at 10 reset to 1
    	}
}


unsigned char delay(unsigned char ucDelay)
{

unsigned char i=0;
for (i=0;i<=ucDelay;i++);

return 0;
}

