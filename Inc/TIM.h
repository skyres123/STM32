/*
 * TIM.h
 *
 *  Created on: Mar 4, 2024
 *      Author: ASUS
 */

#ifndef TIM_H_
#define TIM_H_
#include <stdint.h>
#include "stm32f407xx.h"
#include "Arm_Cortex_M4.h"

typedef enum TIMNO{
	TIMER_1,
	TIMER_2,
	TIMER_3,
	TIMER_4,
	TIMER_5,
	TIMER_6,
	TIMER_7,
	TIMER_8,
	TIMER_9,
	TIMER_10,

}TIMNO;

#define TIMER_START 1
#define TIMER_STOP  0

#define Clear_IT_PendingBit()	(TIMER6->SR &= ~(1u<<0))

void timer_init(TIMNO e_timer_no,unsigned int prescaler,unsigned int period, unsigned int repeat);
void timer_start(TIMNO e_timer_no,int start_stop);
void timer_reset(TIMNO e_timer_no);
void timer_interrupt_config(TIMNO e_timer_no);

void output_compare_init(TIMNO e_timer_no, unsigned int prescaler, unsigned int period, unsigned out_cmp_val);
void pwm_init(TIMNO e_timer_no, unsigned int prescaler, unsigned int period, unsigned int duty_val);


#endif /* TIM_H_ */


