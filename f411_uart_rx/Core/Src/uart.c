/*
 * uart.c
 *
 *  Created on: 15 Mar 2022
 *      Author: asus
 */
#include "uart.h"
#define GPIOEN (1u<<0)
#define UART2EN (1u<<17)

#define CR1_TE (1u<<3)
#define CR1_RE (1u<<2)

#define CR1_UE (1u<<13)
#define SR_TXE (1u<<7)
#define SR_RXNE (1u<<5)

#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ

#define UART_BAUDRATE 115200


static void uart_set_baudrate( USART_TypeDef *USARTx ,uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

void uart2_write(int ch);


int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

void uart2_rxtx_init(void){
	//---------configure uart gpıo pin--------
	//enable clock accsess to gpioa
	RCC->AHB1ENR |= GPIOEN;
	// set PA2 mode to alt. func. mode
	GPIOA->MODER &= ~(1u<<4);
	GPIOA->MODER |= (1u<<5);
	//set PA2 alternate. function. type to UART_TX (AF07)
	GPIOA->AFR[0] |= (1u<<8);
	GPIOA->AFR[0] |= (1u<<9);
	GPIOA->AFR[0] |= (1u<<10);
	GPIOA->AFR[0] &= ~(1u<<11);
	//set PA3 mode to alt. func. mode
	GPIOA->MODER &= ~(1u<<6);
	GPIOA->MODER |= (1u<<7);
	//set PA3 alternate. function. type to UART_RX (AF07)
	GPIOA->AFR[0] |= (1u<<12);
	GPIOA->AFR[0] |= (1u<<13);
	GPIOA->AFR[0] |= (1u<<14);
	GPIOA->AFR[0] &= ~(1u<<15);
	//---------configure uart module ---------
	//enable clock access
	RCC->APB1ENR |= UART2EN;
	//configure the uart baud rate
	uart_set_baudrate(USART2 ,APB1_CLK ,UART_BAUDRATE);
	//congigure the transfer direction
	USART2 -> CR1 = (CR1_TE | CR1_RE);
	//enable uart module
	USART2 -> CR1 |= CR1_UE;
}

void uart2_tx_init(void){
	//---------configure uart gpıo pin--------
	//enable clock accsess to gpioa
	RCC->AHB1ENR |= GPIOEN;

	// set PA2 mode to alt. func. mode
	GPIOA->MODER &= ~(1u<<4);
	GPIOA->MODER |= (1u<<5);

	//set PA2 alternate. function. type to UART_TX (AF07)
	GPIOA->AFR[0] |= ((1u<<10)|(1u<<9)|(1u<<8));
	GPIOA->AFR[0] &= ~(1u<<11);

	//---------configure uart module ---------
	//enable clock access
	RCC->APB1ENR |= UART2EN;

	//configure the uart baud rate
	uart_set_baudrate(USART2 ,APB1_CLK ,UART_BAUDRATE);

	//congigure the transfer direction
	USART2 -> CR1 = CR1_TE;

	//enable uart module
	USART2 -> CR1 |= CR1_UE;

}
char uart2_read (void){
	//make sure receive data register is not empty
		while (!(USART2-> SR & SR_RXNE)){}

		//Read Data
		return USART2->DR;
}

void uart2_write(int ch){
	//make sure transmit data register is empty
	while (!(USART2-> SR & SR_TXE)){}

	//write to transmit data register
	USART2 -> DR = (ch & 0xFF);
}


static void uart_set_baudrate( USART_TypeDef *USARTx ,uint32_t PeriphClk, uint32_t BaudRate){
 USARTx->BRR  = compute_uart_bd(PeriphClk ,BaudRate);
}
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate){
return	((PeriphClk + (BaudRate/2u))/BaudRate);
}

