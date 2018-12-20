#include "TM4C123GH6PM.h"
#include "Dispatcher3.h"


void delayMs(int n);
void EnableInterrupts(void);
void WaitForInterrupts(void);





void InitPort(void){
	
	GPIOF->DIR = 0x0e;
	GPIOF->DEN = 0x0e;
}

void BlinkRed(void){
	
	GPIOF->DATA = 0x2;
	delayMs(1000);
	GPIOF->DATA = 0x00; 
	ReRunMe(10);
	
}

void BlinkBlue(void){
	
	GPIOF->DATA = 0x04;
	delayMs(1000);
	GPIOF->DATA = 0x00; 
	ReRunMe(10);
	
}

void BlinkGreen(void){
	
	GPIOF->DATA = 0x08;
	delayMs(1000);
	GPIOF->DATA = 0x00; 
	ReRunMe(10);
	
}

int main(void)
{
	SYSCTL->RCGCGPIO |= 0x20;
	//Check that the clock is set
	while((SYSCTL->PRGPIO & 0x20) == 0);

	InitPort();
	QueTask(BlinkRed);
	QueTask(BlinkBlue);
	QueTask(BlinkGreen);

	while(1)
	{
		//BlinkBlue();
		//BlinkGreen();
		//BlinkRed();
		Dispatch();
		DecrementDelay();
		
	}
}
// delay n milliseconds (16 MHz CPU clock)
void delayMs(int n)
{
 int i, j;
 for(i = 0 ; i < n; i++)
 for(j = 0; j < 3180; j++)
 {} // do nothing for 1 ms
}
// This function is called by the startup assembly
// code to perform system specific initialization tasks.
