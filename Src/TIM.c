/*
 * TIM.c
 *
 *  Created on: Mar 4, 2024
 *      Author: ASUS
 */
#include "TIM.h"
#include "GPIO.h"
TIM_RegDef_t *timTab[] = {TIMER1,TIMER2,TIMER3,TIMER4,TIMER5,TIMER6,TIMER7,TIMER8,TIMER9,TIMER10};
						//structure pointer enum ile birbirine denk gelecek

static timer_clock_enable(TIM_RegDef_t *pTimerX){
		if(pTimerX==TIMER1)
			TIMER1_CLOCK_ENABLE();
		else if (pTimerX==TIMER2)
			TIMER2_CLOCK_ENABLE();
		else if (pTimerX==TIMER3)
			TIMER3_CLOCK_ENABLE();
		else if (pTimerX==TIMER4)
			TIMER4_CLOCK_ENABLE();
		else if (pTimerX==TIMER5)
			TIMER5_CLOCK_ENABLE();
		else if (pTimerX==TIMER6)
			TIMER6_CLOCK_ENABLE();
		else if (pTimerX==TIMER7)
			TIMER7_CLOCK_ENABLE();
		else if (pTimerX==TIMER8)
			TIMER8_CLOCK_ENABLE();
		else if (pTimerX==TIMER9)
			TIMER9_CLOCK_ENABLE();
		else if (pTimerX==TIMER10)
			TIMER10_CLOCK_ENABLE();
}

void timer_init(TIMNO e_timer_no, unsigned int prescaler, unsigned int period, unsigned int repeat ){
	timer_clock_enable(timTab[e_timer_no]);

	TIM_RegDef_t *p = timTab[e_timer_no];//structure pointer enum ile birbirine denk gelecek
	p->ARR = period-1;
	p->PSC = prescaler-1;

	p->CNT = 0;
	p->CR1 |= (1u<<0);//timer enable
	//APB1 hatları
}
void timer_reset(TIMNO e_timer_no){
	TIM_RegDef_t *p = timTab[e_timer_no];//structure pointer enum ile birbirine denk gelecek
	p->CNT =0;
}
void timer_start(TIMNO e_timer_no,int start_stop){
	TIM_RegDef_t *p = timTab[e_timer_no];//structure pointer enum ile birbirine denk gelecek
	if (start_stop == TIMER_START)
		p->CR1 |= (1u<<0);
	else
		p->CR1 &= ~(1u<<0);
}
void timer_interrupt_config(TIMNO e_timer_no){
	TIM_RegDef_t *ptimer = timTab[e_timer_no];//structure pointer enum ile birbirine denk gelecek
	ptimer->DIER |= (1u<<0);//interrupt kaynapı aktif oldu

	NVIC_Interrupt_Enable(IRQn_TIM6_DAC);
}
void TIM6_DAC_IRQHandler(){
	Gpio_Toggle_Output_Pin(GPIOD, GPIO_PIN_NO_15);
	Clear_IT_PendingBit();
}

void output_compare_init(TIMNO e_timer_no, unsigned int prescaler, unsigned int period, unsigned int out_cmp_val){
	if (e_timer_no == TIMER6 || e_timer_no == TIMER7)
		return -1;
	timer_clock_enable(timTab[e_timer_no]);

	TIM_RegDef_t *p = timTab[e_timer_no];//structure pointer enum ile birbirine denk gelecek
	p->ARR = period-1;
	p->PSC = prescaler-1;
	timer_reset(e_timer_no);

	//capture/capture 1 selection output mode
	p->CCMR1 &= ~(1U<<0);
	p->CCMR1 &= ~(1U<<1);

	//polarity selection
	p->CCER &= ~(1U<<1);

	p->CCER &= ~(1U<<6);
	p->CCER &= ~(1U<<5);

	p->CR1 |= (1U<<0);//timer enable
}
void pwm_init(TIMNO e_timer_no, unsigned int prescaler, unsigned int period, unsigned int duty_val){
	if (e_timer_no == TIMER6 || e_timer_no == TIMER7)
		return -1;
	timer_clock_enable(timTab[e_timer_no]);

	TIM_RegDef_t *p = timTab[e_timer_no];//structure pointer enum ile birbirine denk gelecek
	p->ARR = period-1;
	p->PSC = prescaler-1;
	timer_reset(e_timer_no);

	p->CCR1 = duty_val;
	//capture/capture 1 selection output mode
	p->CCMR1 &= ~(1U<<0);
	p->CCMR1 &= ~(1U<<1);

	//polarity selection
	p->CCER &= ~(1U<<1);

	p->CCER |= (1U<<6);
	p->CCER |= (1U<<5);
	p->CCER &= ~(1U<<4);//pwm mod 1

	p->CR1 |= (1U<<0);//timer enable
}
