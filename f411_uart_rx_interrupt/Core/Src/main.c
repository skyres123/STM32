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

char key;

static void uart_callback (void);

int main(void){



	//Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;


	//Set PA5 as output
	GPIOA->MODER |= (1u<<10);
	GPIOA->MODER &= ~(1u<<11);

	uart2_rx_interrupt_init();


while(1){

}

}
static void uart_callback (void){
	key = USART2->DR;

	if (key == '1'){
		GPIOA->ODR |= LED_PIN;
	}
	else{
		GPIOA->ODR &= ~LED_PIN;
	}

}
void USART2_IRQHandler(void){
	//check if RXNE is set
	if (USART2->SR  & SR_RXNE){
		//do something
		uart_callback ();
	}
}

