//======================================================================
//
// Author        : ADI - Apps
//
// Date          : 5 November 2001
//
// File          : Blink.c
//
// Description   : Blink LED with 100mSec delay for MicroConverter DEMO            
//
//======================================================================
       
#include <stdio.h>
#include <ADuC834.h>

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

