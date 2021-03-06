/*
 * adc.h
 *
 *  Created on: 16 Mar 2022
 *      Author: asus
 */

#ifndef SRC_ADC_H_
#define SRC_ADC_H_

#include <stdint.h>


void pa1_adc_init(void);
uint32_t adc_read(void);
void start_conversion(void);
void pa1_adc_interrupt_init(void);

#define SR_EOC (1u<<1)

#endif /* SRC_ADC_H_ */
