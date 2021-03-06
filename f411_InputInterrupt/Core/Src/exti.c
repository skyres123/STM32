
#include "exti.h"

#define GPIOCEN (1u<<2)
#define SYSCFGEN (1u<<14)

void pc13_exti_init(void){

	//disable global interupt
	__disable_irq();

	//enable clock acces for gpıoc
	RCC->AHB1ENR |= GPIOCEN;

	//set pc13 as input
	GPIOC->MODER &=~ (1u<<26);
	GPIOC->MODER &=~ (1u<<27);

	//enable clock acces to syscnf
	RCC->APB2ENR |= SYSCFGEN;

	//select portc for exti13
	SYSCFG->EXTICR[3] |= (1u<<5);

	//unmask extı13
	EXTI->IMR |= (1u<<13);

	//select falling adge trigger
	EXTI->FTSR |= (1u<<13);

	//enable extı line in nvic
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	//enable gobal interrupt
	__enable_irq();

}




