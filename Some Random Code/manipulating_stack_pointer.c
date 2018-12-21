#include "TM4C123GH6PM.h"                    // Device header

volatile uint32_t tick;
volatile uint32_t _tick;

uint32_t red_stack[40];
uint32_t blue_stack[40];

uint32_t *red_sp = &red_stack[40];
uint32_t *blue_sp = &blue_stack[40];

void GPIOF_Init(void);
void SysTick_Handler(void);
uint32_t getTick(void);
void DelayS(uint32_t seconds);
void main_red(void);
void main_blue(void);

int main()
{
	
	GPIOF_Init();
							// Red Stack Frames
							*(--red_sp) = (1U << 24); /* XPSR 24th bit should be 1 */
							*(--red_sp) = (uint32_t) & main_red;  // This is the stack pointer for red 
							*(--red_sp) = 0x0000000DU;
							*(--red_sp) = 0x0000000AU;
							*(--red_sp) = 0x0000000EU;
							*(--red_sp) = 0x0000000AU;
							*(--red_sp) = 0x0000000EU;
							*(--red_sp) = 0x0000000DU;
	
							// Blue Stack Frames
							*(--blue_sp) = (1U << 24); /* XPSR 24th bit should be 1 */
							*(--blue_sp) = (uint32_t) & main_blue;  // This is the stack pointer for red 
							*(--blue_sp) = 0x0000000DU;
							*(--blue_sp) = 0x0000000AU;
							*(--blue_sp) = 0x0000000EU;
							*(--blue_sp) = 0x0000000AU;
							*(--blue_sp) = 0x0000000EU;
							*(--blue_sp) = 0x0000000DU;
	while(1)
 {}

}


void main_blue(void){
	while(1){
		GPIOF->DATA = 0x8;
		DelayS(1);
		GPIOF->DATA = 0;
		DelayS(1);
	}
}

void main_red(void){
	
	while(1){
		GPIOF->DATA = 0x2;
 		DelayS(1);
		GPIOF->DATA = 0;
		DelayS(1);
	}
}
void GPIOF_Init(void)
{
	SYSCTL->RCGCGPIO |= 0x20;
	GPIOF->DEN |= 0xE;
	GPIOF->DIR |= 0xE;
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/100U);
	__enable_irq();
}

void SysTick_Handler(void){
	++tick;
}

uint32_t getTick(void){
	 __disable_irq();
	_tick = tick;  //  This takes 3 instructions. Thus we need to disable IRQ 
	__enable_irq();
	return _tick;
}

void DelayS(uint32_t seconds){
	seconds *= 100;
	uint32_t temp = getTick();
	while((getTick() - temp) < seconds) {}
	
}
