//======================================================================
//
// Author        : ADI - Apps
//
// Date          : 16 October 2003
//
// File          : Blink.c
//
// Hardware		 : ADuC845, ADuC847, ADuC848
//
// Description   : Blink LED with delay for MicroConverter DEMO
//
//======================================================================

#include <stdio.h>
#include <ADuC845.h>  //To use the ADuC847 or ADuC848 simply change the header file to 
					  //<ADuC847.h> or <ADuC848>

void delay(int);
void main(void)
{

// LED ON
// Loop forever
for(;;)
{
P3 ^= 0x10;
delay(10000);
}

}


// Delay routine
void delay(int length)
{
while (length >=0)
    length--;
}

