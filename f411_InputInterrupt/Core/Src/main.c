#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "exti.h"
#include "systick.h"
#include "tim.h"

#define GPIOAEN (1u<<0)
#define GPIOA_5 (1u<<5)

#define LED_PIN GPIOA_5

static void exti_callback(void);

int main(void){



	//Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;


	//Set PA5 as output
	GPIOA->MODER |= (1u<<10);
	GPIOA->MODER &= ~(1u<<11);

	pc13_exti_init();
	uart2_tx_init();


while(1){

}

}
static void exti_callback(void){

	printf("Butona basildi!!!! :)");
	GPIOA->ODR ^= LED_PIN;
}

void EXTI15_10_IRQHandler(void){
	if ((EXTI->PR & LINE13)!=0){
		//Do something
		exti_callback();
		//clear the PR flag
		EXTI->PR |= LINE13;
	}
}

