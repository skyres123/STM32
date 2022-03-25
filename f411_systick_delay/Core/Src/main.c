#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"

#define GPIOAEN (1u<<0)
#define GPIOA_5 (1u<<5)

#define LED_PIN GPIOA_5

int main(void){
	uart2_tx_init();

	//Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;


	//Set PA5 as output
	GPIOA->MODER |= (1u<<10);
	GPIOA->MODER &= ~(1u<<11);




while(1){


	printf("A second passed !! \n\r");
	GPIOA->ODR ^= LED_PIN;
	systickDelayMs(1000);
}


	}

