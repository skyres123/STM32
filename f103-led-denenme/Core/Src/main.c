#include "stm32f1xx.h"

int main(void){
RCC->APB2ENR |= (1<<4);

GPIOC->CRH |= ((1<<20));
GPIOC->CRH &=~((1<<21)|(1<<23)|(1<<22));

while(1){
	GPIOC->ODR |= (1<<13);
	//for(int i=0;i<100000;i++);
	GPIOC->ODR &= ~(1<<13);
	//for(int i=0;i<100000;i++);
}
}
