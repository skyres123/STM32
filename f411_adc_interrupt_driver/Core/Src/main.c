#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"

static void adc_callback(void);


uint32_t sensor_value;
int main(void){


	uart2_tx_init();
	pa1_adc_interrupt_init();
	start_conversion();

while(1){


}

	}

static void adc_callback(void){
	sensor_value = ADC1->DR;
	printf("Sensor Value: %d \n\r", (int)sensor_value);
}
void ADC_IRQHandler(void){
	//check for eoc in SR
	if((ADC1->SR & SR_EOC)!=0){
		//clear EOC
		ADC1->SR &=~SR_EOC;

		//do something
		adc_callback();
	}
}

