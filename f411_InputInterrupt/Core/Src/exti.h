/*
 * extı.h
 *
 *  Created on: 20 Mar 2022
 *      Author: asus
 */

#ifndef SRC_EXTI_H_
#define SRC_EXTI_H_

#include "stm32f4xx.h"

void pc13_exti_init(void);

#define LINE13	(1u<<13)

#endif /* SRC_EXTI_H_ */
