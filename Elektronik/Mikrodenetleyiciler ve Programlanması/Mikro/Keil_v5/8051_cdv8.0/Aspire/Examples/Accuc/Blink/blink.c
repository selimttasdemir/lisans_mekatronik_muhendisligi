//****************************************************
// Module     : Blink
// Description: Flash Display LED on Eval Board
//***************************************************


char P3_4 @ bit [0xB4];                			//define bit, Port 3 bit 4 'display' led
unsigned char ucLength=0x20; 				// Global variable

void INT0_int (void);
void main(void);
extern unsigned char delay(unsigned char ucDelay);

//*********************************************
// Function:	INT0_int
// Input:	void
// output:	void
// description: INT 0 Interrup:
//              Increases the variable length by 0x10 each interrupt until 0x80 is reached
//*********************************************

void INT0_int (void) @0x03 //interrupt 0 vector
{
ucLength--;
if(ucLength<=0x10)
  ucLength=0x30;
}
//*********************************************
// Function:	main
// Input:	void
// output:	void
//*********************************************
void main(void)
{

 EX0 = 1;				// Enable INT0 Interrupt
 IT0 = 1;				// INT0 interrupt edge triggered
 EA  = 1;				// Enable Interrupts

 for(;;)
    {
    P3_4^=0x1; //XOR display LED with 1
    (void)delay(ucLength);
    }

}




