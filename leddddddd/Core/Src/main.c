#include "stm32f4xx.h"

int main(void){

	RCC->AHB1ENR |= (1<<2);

	GPIOC->MODER |= (1<<26);



	//GPIOC->PUPDR |= (1<<27);
	//GPIOC->PUPDR &= ~(1<<26);
while(1){
	GPIOC->ODR &= ~(1<<13);
	//GPIOC->ODR &= ~(1<<(13+16));

	GPIOC->ODR |= (1<<13);

}
}
