/*
 * Arm_Cortex_M4.c
 *
 *  Created on: Oct 29, 2023
 *      Author: ASUS
 */
#include "Arm_Cortex_M4.h"

static volatile clock_t tmTickCount;

PUBLIC void NVIC_Interrupt_Enable(uint8_t Irq_Number){
	if(Irq_Number<32)
			NVIC_ISERx->NVIC_ISER0 |= (1u<<Irq_Number%32);
	else if (Irq_Number<64)
			NVIC_ISERx->NVIC_ISER1 |= (1u<<Irq_Number%32);
	else if (Irq_Number<=81)
			NVIC_ISERx->NVIC_ISER2 |= (1u<<Irq_Number%32);
	else if (Irq_Number<128)
			NVIC_ISERx->NVIC_ISER3 |= (1u<<Irq_Number%32);
	else if (Irq_Number<160)
			NVIC_ISERx->NVIC_ISER4 |= (1u<<Irq_Number%32);
	else if (Irq_Number<192)
			NVIC_ISERx->NVIC_ISER5 |= (1u<<Irq_Number%32);
	else if (Irq_Number<224)
			NVIC_ISERx->NVIC_ISER6 |= (1u<<Irq_Number%32);
	else if (Irq_Number<240)
			NVIC_ISERx->NVIC_ISER7 |= (1u<<Irq_Number%32);

//stm32f407de 82 adet(0 dan 81 e) kesme olduğu için Irq_Number
//81 den daha büyük bir değer alamaz

}
PUBLIC void NVIC_Interrupt_Disable(uint8_t Irq_Number){
	if(Irq_Number<32)
				NVIC_ICERx->NVIC_ICER0 |= (1u<<Irq_Number%32);
	else if (Irq_Number<64)
				NVIC_ICERx->NVIC_ICER1 |= (1u<<Irq_Number%32);
	else if (Irq_Number<=81)
				NVIC_ICERx->NVIC_ICER2 |= (1u<<Irq_Number%32);
	else if (Irq_Number<128)
				NVIC_ICERx->NVIC_ICER3 |= (1u<<Irq_Number%32);
	else if (Irq_Number<160)
				NVIC_ICERx->NVIC_ICER4 |= (1u<<Irq_Number%32);
	else if (Irq_Number<192)
				NVIC_ICERx->NVIC_ICER5 |= (1u<<Irq_Number%32);
	else if (Irq_Number<224)
				NVIC_ICERx->NVIC_ICER6 |= (1u<<Irq_Number%32);
	else if (Irq_Number<240)
				NVIC_ICERx->NVIC_ICER7 |= (1u<<Irq_Number%32);
}

PUBLIC void Systick_Config(uint32_t tick){
	SYSTICK->SYST_RVR = tick-1;
	SYSTICK->SYST_CVR =0;

	SYSTICK->SYST_CSR |=(1u<<2); //CPU_CLOCK;
	SYSTICK->SYST_CSR |=(1u<<1); //TICKINT;

	SYSTICK->SYST_CSR |=(1u<<0); //SYSTICK_EN;
}

void SysTick_Handler(){
	++tmTickCount;
}
clock_t clock(){
	  return tmTickCount;
}

