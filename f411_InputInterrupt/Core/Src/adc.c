#include "stm32f4xx.h"
#include "adc.h"

#define GPIOAEN (1u<<0)
#define ADC1ENR (1u<<8)
#define ADC_CH1 (1u<<0)
#define ADC_SEQ_LEN_1 0x00
#define CR2_ADON (1u<<0)
#define CR2_SWSTART (1u<<30)
#define SR_EOC (1u<<1)
#define CR2_CONT (1u<<1)

/*ad configured with 3 channels
 * ch2,ch3,ch5
 * first = ch5
 * second = ch2
 * third = ch3
 *
 */
void pa1_adc_init(void){
	//*********configure the ADC GPIO pin*********


	//enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	//set the mode of pa1 to analog
	GPIOA->MODER |= (1u<<2);
	GPIOA->MODER |= (1u<<3);

	//**********configure the ADC module********
	//enable clock access to ADC1
	RCC->APB2ENR |= ADC1ENR;

	//conversion sequence start
	ADC1->SQR3 = ADC_CH1;

	//conresion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN_1;
	//20 21 22 23 numaralı bitleri 0 yapmamız yeterlidir
	//ama registerin geri kalanına ihtiyacımız olmadığından
	//registerin tamamını 0 ladık

	//enable ADC module
	ADC1->CR2 |= CR2_ADON;
}

void start_conversion(void){
	//enable continuous conversion
	ADC1->CR2 |= CR2_CONT;

	//Start the adc conversion
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void){
	//wait for conversion to be compledeted
	while(!(ADC1->SR & SR_EOC)){}

	//Read converted result
	return (ADC1->DR);
}
