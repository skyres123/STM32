/*
 * Arm_Cortex_M4.h
 *
 *  Created on: Oct 29, 2023
 *      Author: ASUS
 */

#ifndef ARM_CORTEX_M4_H_
#define ARM_CORTEX_M4_H_
#include <stdint.h>
//arm cortex m4 processor NVIC registers
typedef volatile uint32_t IO;

#define PUBLIC
#define PRIVATE 	static

typedef struct{
	IO MEMRMP;
	IO PMC;
	IO EXTICR[4];
	//0x14 + 0x04 = 0x18
	//0x18 + 0x04 = 0x1C
	//0x1C + 0x04 = 20
	uint32_t reserved[2];
	IO CMPCR;
}SYSCFG_RegDef_t;

#define SYSCFG 					((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

//IRQ numaraları
/*
#define IRQn_EXTI0		6
#define IRQn_EXTI1		7
#define IRQn_EXTI2		8
#define IRQn_EXTI3		9
#define IRQn_EXTI4		10
#define IRQn_EXTI9_5	23
#define IRQn_EXTI15_10	40
#define IRQ_HASH_RNG	80
*/
enum{
	IRQ_WWDG,
	IRQ_PVD,
	IRQ_TAMP_STAMP,
	IRQ_RTC_WKUP,
	IRQ_FLASH,
	IRQ_RCC,
	IRQn_EXTI0,
	IRQn_EXTI1,
	IRQn_EXTI2,
	IRQn_EXTI3,
	IRQn_EXTI4,
	IRQn_DMA1_STREAM0,
	IRQn_DMA1_STREAM1,
	IRQn_DMA1_STREAM2,
	IRQn_DMA1_STREAM3,
	IRQn_DMA1_STREAM4,
	IRQn_DMA1_STREAM5,
	IRQn_DMA1_STREAM6,
	IRQn_ADC,
	IRQn_CAN1_TX,
	IRQn_CAN1_RX0,
	IRQn_CAN1_RX1,
	IRQn_SCE,
	IRQn_EXTI9_5,
	IRQn_TIM1_BRK_TIM9,
	IRQn_IM1_UP_TIM10,
	IRQn_TIM1_TRG_COM_TIM11,
	IRQn_TIM1_CC,
	IRQN_TIM2,
	IRQn_TIM3,
	IRQn_TIM4,
	IRQn_I2C1_EV,
	IRQn_I2C1_ER,
	IRQn_I2C2_EV,
	IRQn_I2C2_ER,
	IRQn_SPI1,
	IRQn_SPI2,
	IRQn_USART1,
	IRQn_USART2,
	IRQn_USART3,
	IRQn_EXTI15_10,
	IRQn_RTC_ALARM,
	IRQn_OTG_WKUP,
	IRQn_TIM8_BRK_TIM12,
	IRQn_TIM8_UP_TIM13,
	IRQn_TIM8_TRG_COM_TIM14,
	IRQn_TIM8_CC,
	IRQn_DMA1_STREAM7,
	IRQn_FSMC,
	IRQn_SDIO,
	IRQn_TIM5,
	IRQn_SPI3,
	IRQn_UART4,
	IRQn_UART5,
	IRQn_TIM6_DAC,
	IRQn_TIM7,
	IRQn_DMA2_STREAM0,
	IRQn_DMA2_STREAM1,
	IRQn_DMA2_STREAM2,
	IRQn_DMA2_STREAM3,
	IRQn_DMA2_STREAM4,
	IRQn_ETH,
	IRQn_ETH_WKUP,
	IRQn_CAN2_TX,
	IRQn_CAN2_RX0,
	IRQn_CAN2_RX1,
	IRQn_CAN2_SCE,
	IRQn_OTF_FS,
	IRQn_DMA2_STREAM5,
	IRQn_DMA2_STREAM6,
	IRQn_DMA2_STREAM7,
	IRQn_USART6,
	IRQn_I2C3_EV,
	IRQn_I2C3_ER,
	IRQn_OTG_HS_EP1_OUT,
	IRQn_OTG_HS_EP1_IN,
	IRQn_OTG_HS_WKUP,
	IRQn_OTG_HS,
	IRQn_DCMI,
	IRQn_CRYP,
	IRQn_HASH_RNG,
	IRQn_FPU,






};

/*
#define NVIC_ISER0			((IO*)0xE000E100)
#define NVIC_ISER1			((IO*)0xE000E104)
#define NVIC_ISER2			((IO*)0xE000E108)
#define NVIC_ISER3			((IO*)0xE000E10C)
#define NVIC_ISER4			((IO*)0xE000E110)
#define NVIC_ISER5			((IO*)0xE000E114)
#define NVIC_ISER6			((IO*)0xE000E118)
#define NVIC_ISER7			((IO*)0xE000E11C)

#define NVIC_ICER0			((IO*)0xE000E180)
#define NVIC_ICER1			((IO*)0xE000E184)
#define NVIC_ICER2			((IO*)0xE000E188)
#define NVIC_ICER3			((IO*)0xE000E18C)
#define NVIC_ICER4			((IO*)0xE000E190)
#define NVIC_ICER5			((IO*)0xE000E194)
#define NVIC_ICER6			((IO*)0xE000E198)
#define NVIC_ICER7			((IO*)0xE000E19C)
*/
#define NVIC_BASEADDR		(0xE000E100)
#define SYSTICK_BASEADRR	(0xE000E010)

typedef struct{
	IO NVIC_ISER0;
	IO NVIC_ISER1;
	IO NVIC_ISER2;
	IO NVIC_ISER3;
	IO NVIC_ISER4;
	IO NVIC_ISER5;
	IO NVIC_ISER6;
	IO NVIC_ISER7;
}NVIC_ISER_RegDef_t;
#define NVIC_ISERx			((NVIC_ISER_RegDef_t*)NVIC_BASEADDR)
typedef struct{
	IO NVIC_ICER0;
	IO NVIC_ICER1;
	IO NVIC_ICER2;
	IO NVIC_ICER3;
	IO NVIC_ICER4;
	IO NVIC_ICER5;
	IO NVIC_ICER6;
	IO NVIC_ICER7;
}NVIC_ICER_RegDef_t;
#define NVIC_ICERx			((NVIC_ICER_RegDef_t*)NVIC_BASEADDR+0x80)

PUBLIC void NVIC_Interrupt_Enable(uint8_t Irq_Number);
PUBLIC void NVIC_Interrupt_Disable(uint8_t Irq_Number);

typedef struct{
	IO SYST_CSR;
	IO SYST_RVR;
	IO SYST_CVR;
	IO SYST_CALIB;
	}SYSTICK_RegDef_t;

#define SYSTICK ((SYSTICK_RegDef_t*)SYSTICK_BASEADRR)

#define CPU_CLOCK	(1u<<2)
#define TICKINT		(1u<<1)
#define SYSTICK_EN	(1u<<0)

PUBLIC void Systick_Config(uint32_t tick);
typedef uint32_t clock_t;

PUBLIC clock_t clock();

#define SYSTEM_FREQ 16000000
#endif /* ARM_CORTEX_M4_H_ */
