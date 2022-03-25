#include"stm32f0xx.h"



int main(void){
	 RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	 GPIOA->MODER |= GPIO_MODER_MODER5_0;

/*
	 GPIOA->OTYPER |= (1<<5);


	 //GPIOA->OSPEEDR &= ~(1<<11);

	 GPIOA->PUPDR &= ~((1<<10)|(1<<11));*/
	 //GPIOA->OSPEEDR &= ~((1<<10)|(1<<11));
	 //GPIOA->OTYPER &= ~(1<<5);
while(1){
	 GPIOA->BSRR = GPIO_BSRR_BS_5;
/*	 for(int i=0;i<10000;i++){}
	 GPIOA->BSRR = GPIO_BSRR_BR_5;
	 for(int j=0;j<10000;j++){}*/
}

}
