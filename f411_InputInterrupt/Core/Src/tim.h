/*
 * tim.h
 *
 *  Created on: 18 Mar 2022
 *      Author: asus
 */

#ifndef SRC_TIM_H_
#define SRC_TIM_H_

void tim2_1hz_init(void);
void tim2_pa5_output_compare(void);
void tim3_pa6_input_capture(void);
void tim2_pa5_pwm(void);
void analogWrite(int DutyCycle);

#define SR_UIF (1u<<0)
#define SR_CC1IF (1u<<1)

#endif /* SRC_TIM_H_ */
