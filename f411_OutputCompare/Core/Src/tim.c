#include "stm32f4xx.h"


#define TIM2EN (1u<<0)
#define CR1_CEN (1u<<0)
#define OC_TOGGLE ((1u<<4)|(1u<<5))
#define CCER_CC1E (1u<<0)

#define GPIOAEN (1u<<0)
#define AFR5_TIM (1u<<20)

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

void tim2_pa5_output_compare(void){
	//enable clock access to gpıoa
	RCC-> AHB1ENR |= GPIOAEN;

	//set pa5 mode to alternate function
	GPIOA->MODER |= (1u<<11);
	GPIOA->MODER &=~(1u<<10);

	//set pa5 alternate function type to TIM2_CH1
	GPIOA->AFR[0] |= AFR5_TIM;

	//enable clock access to tim2
	RCC->APB1ENR |= TIM2EN;

	//set the prescalar value
	TIM2->PSC =  1600-1; //16 000 000 / 1600 = 10 000

	//	set auto reload value
	TIM2 -> ARR = 10000-1; //10 000/10 000 = 1

	//Set output compare mode
	 TIM2->CCMR1 =OC_TOGGLE;

	//enable timer2 ch1 in compare mode
	TIM2->CCER |= CCER_CC1E;

	//clear counter
	TIM2->CNT = 0;

	//enable the timer
	TIM2->CR1 |= CR1_CEN;

}
