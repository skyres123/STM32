/*
 * uart.h
 *
 *  Created on: 15 Mar 2022
 *      Author: asus
 */

#ifndef SRC_UART_H_
#define SRC_UART_H_
#include "stm32f4xx.h"
#include <stdint.h>

void uart2_tx_init(void);
char uart2_read (void);
void uart2_rxtx_init(void);
void uart2_rx_interrupt_init(void);

#define SR_RXNE (1u<<5)


#endif /* SRC_UART_H_ */
