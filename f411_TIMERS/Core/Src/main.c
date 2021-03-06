#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

#define GPIOCEN (1u<<2)
#define GPIOC_13 (1u<<13)

#define LED_PIN GPIOC_13

int main(void){


	//Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOCEN ;


	//Set PA5 as output
	GPIOC->MODER |= (1u<<26);
	GPIOC->MODER &= ~(1u<<27);


	uart2_tx_init();
	tim2_1hz_init();



while(1){

	//wait for uif
	while(!(TIM2->SR & SR_UIF)){}

	//clear uif
	TIM2->SR &= ~SR_UIF;

	GPIOC->ODR ^= LED_PIN;
	printf("A second passed !! \n\r");


}


	}

