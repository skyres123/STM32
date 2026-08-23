/*
 * usart.h
 *
 *  Created on: Apr 9, 2025
 *      Author: ASUS
 */

#ifndef USART_H_
#define USART_H_

#include "stm32f407xx.h"

enum{
	USART_CR1_SBK=0,
	USART_CR1_RWU,
	USART_CR1_RE,
	USART_CR1_TE,
	USART_CR1_IDLEIE,
	USART_CR1_RXNEIE,
	USART_CR1_TCIE,
	USART_CR1_TXEIE,
	USART_CR1_PEIE,
	USART_CR1_PS,
	USART_CR1_PCE,
	USART_CR1_WAKE,
	USART_CR1_M,
	USART_CR1_UE,
	USART_CR1_RES,//KULLANILMAYACAK
	USART_CR1_OVER8,
}USART_CR1;

enum{
	USART_CR2_ADD0,
	USART_CR2_ADD1,
	USART_CR2_ADD2,
	USART_CR2_ADD3,
	USART_CR2_RES1,
	USART_CR2_LBDL,
	USART_CR2_LBDIE,
	USART_CR2_RES2,
	USART_CR2_LBCL,
	USART_CR2_CPHA,
	USART_CR2_CPOL,
	USART_CR2_CLKEN,
	USART_CR2_STOP0,
	USART_CR2_STOP1,
	USART_CR2_LINEN,
	USART_CR1_RES3,
}USART_CR2;

//usart modes
enum{
	USART_MODE_ONLY_TX,
	USART_MODE_ONLY_RX,
	USART_MODE_BOTH_TXRX,
};
//word lengths
enum{
	USART_WORDLEN_8BITS,
	USART_WORDLEN_9BITS,
};

//stop bit adedi
enum{
	USART_STOPBITS_0_5,
	USART_STOPBITS_1,
	USART_STOPBITS_1_5,
	USART_STOPBITS_2,
};

//paritiy
enum{
	USART_PARITY_NO,
	USART_PARITY_EVEN,
	USART_PARITY_ODD,
};

//hardware flow control
enum{
	USART_HW_FLOW_CONTROL_NO,
	USART_HW_FLOW_CONTROL_CTS,
	USART_HW_FLOW_CONTROL_RTS,
	USART_HW_FLOW_CONTROL_CTS_RTS,
};


typedef struct{
	uint8_t mode;
	uint8_t word_length;
	uint8_t stop_bit;
	uint16_t baudrate;
	uint8_t parity_control;
	uint8_t hwflowcontrol;
}USART_Config_t;//uart özellikleri

typedef struct{
	UART_RegDef_t *pUsartX;
	USART_Config_t usart_Config;

}USART_Handle_t;//portu ifade ediyor___ nested structure

PRIVATE void Usart_Periph_Clock_Enr(GPIO_RegDef_t* pGpıoX);
void Uart_init(USART_Handle_t *pUsart_handle);

#endif /* USART_H_ */
