/*
 * gpıo.c
 *
 *  Created on: 10 Ağu 2023
 *      Author: ASUS
 */
#include "GPIO.h"


PRIVATE void Gpio_Periph_Clock_Enr(GPIO_RegDef_t* pGpıoX){
	if(pGpıoX==GPIOA)
		GPIOA_CLOCK_ENABLE();
	else if (pGpıoX==GPIOB)
		GPIOB_CLOCK_ENABLE();
	else if (pGpıoX==GPIOC)
		GPIOC_CLOCK_ENABLE();
	else if (pGpıoX==GPIOD)
		GPIOD_CLOCK_ENABLE();
	else if (pGpıoX==GPIOE)
		GPIOE_CLOCK_ENABLE();
	else if (pGpıoX==GPIOF)
		GPIOF_CLOCK_ENABLE();
	else if (pGpıoX==GPIOG)
		GPIOG_CLOCK_ENABLE();
	else if (pGpıoX==GPIOH)
		GPIOH_CLOCK_ENABLE();
	else if (pGpıoX==GPIOI)
		GPIOI_CLOCK_ENABLE();

}
//port to code
PRIVATE uint8_t Get_Port_Code(GPIO_RegDef_t* pGpıoX){
	if(pGpıoX==GPIOA)
		return GPIOA_PORT_CODE;
	else if (pGpıoX==GPIOB)
		return GPIOB_PORT_CODE;
	else if (pGpıoX==GPIOC)
		return GPIOC_PORT_CODE;
	else if (pGpıoX==GPIOD)
		return GPIOD_PORT_CODE;
	else if (pGpıoX==GPIOE)
		return GPIOE_PORT_CODE;
	else if (pGpıoX==GPIOF)
		return GPIOF_PORT_CODE;
	else if (pGpıoX==GPIOG)
		return GPIOG_PORT_CODE;
	else if (pGpıoX==GPIOH)
		return GPIOH_PORT_CODE;
	else if (pGpıoX==GPIOI)
		return GPIOI_PORT_CODE;
}

PUBLIC void Gpio_Init(Gpio_Handle_t *pGpio_Handle){
	uint32_t temp=0;
	//clock aktif et
	Gpio_Periph_Clock_Enr(pGpio_Handle->pGpioX);
	//pin mode ayarla

	//pGpio_Handle->pGpioX->MODER;//gerçek register
	//pGpio_Handle->Gpio_PinConfig->PinMode;//clientin girdiği pin mode
	if(pGpio_Handle->Gpio_PinConfig.PinMode <= GPIO_MODE_ANALOG){
		temp = (pGpio_Handle->Gpio_PinConfig.PinMode<<(2* pGpio_Handle->Gpio_PinConfig.PinNumber));
		pGpio_Handle->pGpioX->MODER &= ~(0b11<<(2* pGpio_Handle->Gpio_PinConfig.PinNumber));//değer göndermeden önce registeri resetledik
		pGpio_Handle->pGpioX->MODER |= temp;
		//moder registerinin 						//moder registerinde ilgili bitin moder register
		//ilgili bitleri gösteir					  bitlerine pin numarasını 2 ile çarpıyoruz
	}
	else{
		//interrupt mode

		if(pGpio_Handle->Gpio_PinConfig.PinMode == GPIO_MODE_FE_IT){//only falling edge
			EXTI->FTSR |= (1u>>pGpio_Handle->Gpio_PinConfig.PinNumber);
			EXTI->RTSR &= ~(1u>>pGpio_Handle->Gpio_PinConfig.PinNumber);
		}
		else if (pGpio_Handle->Gpio_PinConfig.PinMode == GPIO_MODE_RE_IT){//only rising age
			EXTI->FTSR &= ~(1u>>pGpio_Handle->Gpio_PinConfig.PinNumber);
			EXTI->RTSR |= (1u>>pGpio_Handle->Gpio_PinConfig.PinNumber);
		}
		else if (pGpio_Handle->Gpio_PinConfig.PinMode == GPIO_MODE_FRE_IT){//rising and falling edge
			EXTI->FTSR |= (1u>>pGpio_Handle->Gpio_PinConfig.PinNumber);
			EXTI->RTSR |= (1u>>pGpio_Handle->Gpio_PinConfig.PinNumber);
		}
		//used port pin selection by SYSCFG_EXTICRx
		SYSCFGR_CLOCK_ENABLE();
		uint8_t syscfgr_exti_reg_no = pGpio_Handle->Gpio_PinConfig.PinNumber/4;
		uint8_t syscfgr_exti_reg_bit_no = pGpio_Handle->Gpio_PinConfig.PinNumber%4;
		uint8_t port_code = Get_Port_Code(pGpio_Handle->pGpioX);
		SYSCFG->EXTICR[syscfgr_exti_reg_no] |= (port_code<<(syscfgr_exti_reg_bit_no*4));
		//Eneble IMR
		EXTI->IMR |= (1U<<pGpio_Handle->Gpio_PinConfig.PinNumber);
		//NVIC kısmı

	}

	//speed ayarla
	temp = (pGpio_Handle->Gpio_PinConfig.PinSpeed<<(2* pGpio_Handle->Gpio_PinConfig.PinNumber));
	pGpio_Handle->pGpioX->OSPEEDR &= ~(0b11<<(2* pGpio_Handle->Gpio_PinConfig.PinNumber));//değer göndermeden önce registeri resetledik
	pGpio_Handle->pGpioX->OSPEEDR |= temp;

	//pull up pull down
	temp = (pGpio_Handle->Gpio_PinConfig.PinPuPd<<(2* pGpio_Handle->Gpio_PinConfig.PinNumber));
	pGpio_Handle->pGpioX->PUPDR &= ~(0b11<<(2* pGpio_Handle->Gpio_PinConfig.PinNumber));//değer göndermeden önce registeri resetledik
	pGpio_Handle->pGpioX->PUPDR |= temp;

	//otype ayarla
	temp = (pGpio_Handle->Gpio_PinConfig.PinOtype<<(pGpio_Handle->Gpio_PinConfig.PinNumber));
	pGpio_Handle->pGpioX->OTYPER &= ~(0b01<<(pGpio_Handle->Gpio_PinConfig.PinNumber));//değer göndermeden önce registeri resetledik
	pGpio_Handle->pGpioX->OTYPER|= temp;
	//alternate func mod ise ayarla
	if(pGpio_Handle->Gpio_PinConfig.PinAlternateFunctionMode == GPIO_MODE_ALTERNATE)
	{
		uint8_t afr_low_high =pGpio_Handle->Gpio_PinConfig.PinNumber /8;
		uint8_t afr_pin_no = pGpio_Handle->Gpio_PinConfig.PinMode %8;

		pGpio_Handle->pGpioX->AFR[afr_low_high] &= ~(0x0F<<(4*afr_pin_no));
		pGpio_Handle->pGpioX->AFR[afr_low_high] |= pGpio_Handle->Gpio_PinConfig.PinAlternateFunctionMode<<(4*afr_pin_no);
	}
}


PUBLIC void Gpio_Write_Output_Pin(GPIO_RegDef_t *pGpioX, uint8_t pin_no, uint8_t val ){

	if(val==GPIO_PIN_SET)
		pGpioX->ODR |= (1u<<pin_no);
	else
		pGpioX->ODR &= ~(1u<<pin_no);
}
PUBLIC void Gpio_Write_Output_Port(GPIO_RegDef_t *pGpioX, uint16_t val){
	pGpioX->ODR = val;//
}
PUBLIC void Gpio_Toggle_Output_Pin(GPIO_RegDef_t *pGpioX, uint8_t pin_no){
	pGpioX->ODR ^= (1u<<pin_no);//pini toggle eden fonksiyon
}
PUBLIC uint32_t Gpio_Read_Input_Pin(GPIO_RegDef_t *pGpioX, uint8_t pin_no){
//y=x&(1<<n)
	uint32_t res=0;
	res = (pGpioX->IDR &(1u<<pin_no));
	return res!=0 ? GPIO_PIN_SET :GPIO_PIN_RESET;
}

PUBLIC void Clear_Pending_Reg(uint8_t pin_no){
	//
	if(EXTI->PR & (1u<<pin_no))
		EXTI->PR |= (1u<<pin_no);
}
int Toggle_Board_Random_Leds(){
	//0,1,2,3 seklinde olacak
	uint32_t leds_no = (RNG_Get_Random_Number()%4+12);
	for(int i =0; i < 1000000; i++);
	Gpio_Toggle_Output_Pin(GPIOD,leds_no);
	for(int i =0; i < 1000000; i++);
	//delay fonksiyonu eklenecek

}

