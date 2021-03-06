#include "stm32f4xx.h"

#define SYSTICK_LOAD_VAL 16000
#define CTRL_ENABLE (1u<<0)
#define CTRL_CLKSRC (1u<<2)
#define CTRL_COUNTFLAG (1u<<16)

void systickDelayMs(int delay){
	//configure systick
	//Reload with number of clocks per miliseconds
	SysTick->LOAD  = SYSTICK_LOAD_VAL;

	//clear systick current register
	SysTick -> VAL = 0;

	//enable systick and select internal clocksource
	SysTick -> CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	for (int i=0; i<delay ; i++){
		//wait until countflag is set

		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0){}
	}
	SysTick->CTRL = 0;
}

