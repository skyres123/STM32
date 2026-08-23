/*
 * usart.c
 *
 *  Created on: Apr 9, 2025
 *      Author: ASUS
 */
#include "usart.h"
#include "stm32f407xx.h"

void Usart_Periph_Clock_Enr(UART_RegDef_t* pUsartX){
		if(pUsartX==USART1)
		USART1_CLOCK_ENABLE();
		else if(pUsartX==USART2)
		USART2_CLOCK_ENABLE();
		else if(pUsartX==USART3)
		USART3_CLOCK_ENABLE();
		else if(pUsartX==USART4)
		USART4_CLOCK_ENABLE();
		else if(pUsartX==USART5)
		USART5_CLOCK_ENABLE();
		else if(pUsartX==USART6)
		USART6_CLOCK_ENABLE();

}

void uart_init(USART_Handle_t *pUsart_handle){
	//clock enable edilidi
	Usart_Periph_Clock_Enr(pUsart_handle->pUsartX);

	//mod
	if(pUsart_handle->usart_Config.mode==USART_MODE_ONLY_TX)
		pUsart_handle->pUsartX->CR1|=(1u<<3);//TE enable
	else if(pUsart_handle->usart_Config.mode==USART_MODE_ONLY_RX)
		pUsart_handle->pUsartX->CR1|=(1u<<2);//RE enable
	else if(pUsart_handle->usart_Config.mode==USART_MODE_BOTH_TXRX){
		pUsart_handle->pUsartX->CR1|=(1u<<3);//TE enable
	    pUsart_handle->pUsartX->CR1|=(1u<<2);//RE enable
	}
	//word length
	//pUsart_handle->pUsartX->CR1


