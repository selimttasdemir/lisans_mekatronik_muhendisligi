//======================================================================
//
// Author        : ADI - Apps
//
// Date          : October 2003
//
// File          : Blink.c
//
// Description   : Blink LED with delay for MicroConverter DEMO            
//
//======================================================================
       
#include <stdio.h>
#include <ADuC841.h>

void delay(int);
void main(void)
{

// LED ON
// Loop forever
for(;;)
{
P3 ^= 0x10;
delay(100000);
}

}


// Delay routine

void delay(int length)
{
while (length >=0)
    length--;
}

