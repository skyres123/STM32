/*
 * RNG.h
 *
 *  Created on: 1 Eki 2023
 *      Author: ASUS
 */

#ifndef RNG_H_
#define RNG_H_
#include <stdint.h>
#include "stm32f407xx.h"
#include "Arm_Cortex_M4.h"


//RNG Error
#define RNG_ERROR -1
//RNG Control
#define PLLON 		(1u<<24)
#define PLLREADY 	(1u<<25)

#define RNG_RNGRST	(1u<<6)

//rng sr
#define RNG_DRDY	(1u<<0)
#define RNG_CECS	(1u<<1)
#define RNG_SECS	(1u<<2)
#define RNG_CEIS 	(1u<<5)
#define RNG_SEIS	(1u<<6)

#define RNG_IE 		(1u<<3)
#define RNG_RNGEN	(1u<<2)

PUBLIC void RNG_Init();
PUBLIC void RNG_Number_Generator_Enr();
PUBLIC uint32_t RNG_Get_Random_Number();
void HASH_RNG_IRQHandler ();

#endif /* RNG_H_ */
