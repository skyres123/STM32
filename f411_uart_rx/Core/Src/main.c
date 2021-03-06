#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

#define GPIOAEN (1u<<0)
#define GPIOA_5 (1u<<5)

#define LED_PIN GPIOA_5
char key;
int main(void){
	//GPIOA clock enabled
	RCC->AHB1ENR  |= GPIOAEN;
	//GPIOA pin5 set as output
	GPIOA -> MODER |= (1u<<10);
	GPIOA -> MODER &= ~(1u<<11);
	uart2_rxtx_init();
while(1){
	key = uart2_read();
		if (key=='1'){
			GPIOA->ODR |= LED_PIN;
			printf("button pressed");
		}
		else{
			GPIOA->ODR &= ~LED_PIN;
			printf("button not pressed");
		}
	}

}
