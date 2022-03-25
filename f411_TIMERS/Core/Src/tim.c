#include "stm32f4xx.h"


#define TIM2EN (1u<<0)
#define CR1_CEN (1u<<0)

void tim2_1hz_init(void){
	//enable clock access to tim2
	RCC->APB1ENR |= TIM2EN;

	//set the prescalar value
	TIM2->PSC =  1600-1; //16 000 000 / 1600 = 10 000

	//	set auto reload value
	TIM2 -> ARR = 10000-1; //10 000/10 000 = 1

	//clear counter
	TIM2->CNT = 0;

	//enable the timer
	TIM2->CR1 |= CR1_CEN;

}
