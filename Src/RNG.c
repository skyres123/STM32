/*
 * RNG.c
 *
 *  Created on: Nov 7, 2023
 *      Author: ASUS
 */

#include "RNG.h"

PUBLIC void RNG_Init(){
	//PLL aktif ediliyor
	RCC->CR |= PLLON;//pll aktif
	//PLLREADY biti kontrol adult
	while(!(RCC->CR & PLLREADY));

	RNG_CLOCK_ENABLE();
	//enable interruppt
	RNG->CR |= RNG_IE;
	//IE interruptları enable ettik
	//rngen in RNG_CR
	RNG->CR |= RNG_RNGEN;//rng_en enable ettik
	//kesmeyi nvic den enable ediyoruz
	NVIC_Interrupt_Enable(IRQn_HASH_RNG);
}
PUBLIC uint32_t RNG_Get_Random_Number(){
	if(RNG->CR & RNG_RNGEN)
		return RNG->DR;
	return RNG_ERROR;
}
void HASH_RNG_IRQHandler (){
	uint32_t rand_num ;
	if(!(RNG->SR & RNG_SEIS) && !(RNG->SR & RNG_CEIS) && (RNG->SR & RNG_DRDY)){
		rand_num = RNG->CR;
		//RNG->CR &=~RNG_IE;
		//RNG->CR &=~RNG_RNGEN;
		//NVIC_Interrupt_Disable(IRQn_HASH_RNG);
	}
	else if(RNG->SR & RNG_CEIS){
		RNG->CR &=~ RNG_CEIS;//ceis biti resetlendi
		RCC->AHB2RSTR |= RNG_RNGRST;//RNG bit resetlendi
		RCC->AHB2RSTR &=~ RNG_RNGRST;//rng nin resetlanmesi durdu
		RNG->CR &=~RNG_RNGEN;//RNG yi reinitialize ettik
	}
	else if(RNG->SR & RNG_SEIS){
		RNG->CR &=~ RNG_SEIS;//ceis biti resetlendi
		RCC->AHB2RSTR |= RNG_RNGRST;//RNG bit resetlendi
		RCC->AHB2RSTR &=~ RNG_RNGRST;//rng nin resetlanmesi durdu
		RNG->CR &=~RNG_RNGEN;//RNG yi reinitialize ettik
	}
}




