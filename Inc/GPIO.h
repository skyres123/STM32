/*
 * gpio.h
 *
 *  Created on: 10 Ağu 2023
 *      Author: ASUS
 */

#ifndef GPIO_H_
#define GPIO_H_
#include <stdint.h>
#include "stm32f407xx.h"
#include "Arm_Cortex_M4.h"
#include "RNG.h"

typedef struct{
	uint8_t PinNumber;
	uint8_t PinMode;
	uint8_t PinSpeed;
	uint8_t PinOtype;
	uint8_t PinPuPd;
	uint8_t PinAlternateFunctionMode;
}Gpio_PinConfig_t;//gpıo portunun özellikleri

typedef struct{
	GPIO_RegDef_t *pGpioX;
	Gpio_PinConfig_t Gpio_PinConfig;

}Gpio_Handle_t;//portu ifade ediyor___ nested structure

#define GPIO_PORT_PIN_BLUE (1u<<15)
#define GPIO_PORT_PIN_RED (1u<<14)
#define GPIO_PORT_PIN_ORANGE (1u<<13)
#define GPIO_PORT_PIN_GREEN (1u<<12)



#define GPIO_PORT_ALL_LEDS (0b1111<<12)//discovery kartında tüm ledleri yakan makro
#define GPIO_PORT_RAINBOW (GPIO_PORT_PIN_BLUE|GPIO_PORT_PIN_RED|GPIO_PORT_PIN_ORANGE|GPIO_PORT_PIN_GREEN)
//discovery kartında tüm ledleri yakan makro 2

//GPIO pin modes
enum {
	GPIO_MODE_IN=0,
	GPIO_MODE_OUT,
	GPIO_MODE_ALTERNATE,
	GPIO_MODE_ANALOG,
	//interrupt modları
	GPIO_MODE_FE_IT,
	GPIO_MODE_RE_IT,//
	GPIO_MODE_FRE_IT,//
};
//GPIO Alternate function modes
enum{
	GPIO_AF0,
	GPIO_AF1,
	GPIO_AF2,
	GPIO_AF3,
	GPIO_AF4,
	GPIO_AF5,
	GPIO_AF6,
	GPIO_AF7,
	GPIO_AF8,
	GPIO_AF9,
	GPIO_AF10,
	GPIO_AF11,
	GPIO_AF12,
	GPIO_AF13,
	GPIO_AF14,
	GPIO_AF15,
};

//GPIO PIN NUMBER
enum{
		GPIO_PIN_NO_0,
		GPIO_PIN_NO_1,
		GPIO_PIN_NO_2,
		GPIO_PIN_NO_3,
		GPIO_PIN_NO_4,
		GPIO_PIN_NO_5,
		GPIO_PIN_NO_6,
		GPIO_PIN_NO_7,
		GPIO_PIN_NO_8,
		GPIO_PIN_NO_9,
		GPIO_PIN_NO_10,
		GPIO_PIN_NO_11,
		GPIO_PIN_NO_12,
		GPIO_PIN_NO_13,
		GPIO_PIN_NO_14,
		GPIO_PIN_NO_15,
};

//for discovery card
enum{GPIO_PIN_GREEN=12,
	GPIO_PIN_ORANGE,
	GPIO_PIN_RED,
	GPIO_PIN_BLUE};
//GPIO PIN SPPED
enum{
	GPIO_SPEED_LOW,
	GPIO_SPEED_MEDIUM,
	GPIO_SPEED_HIGH,
	GPIO_SPEED_VERY_HIGH
};
//GPIO OUTPUT TYPE
enum{
	GPIO_OTYPE_PP,
	GPIO_OTYPE_OD
};

//GPIO PULL UP/PULL DOWN
enum{
	GPIO_PIN_PUPD_NO,
	GPIO_PIN_PU,
	GPIO_PIN_PD,
};

enum{
	GPIO_PIN_RESET,
	GPIO_PIN_SET,
};

enum{
	GPIOA_PORT_CODE,
	GPIOB_PORT_CODE,
	GPIOC_PORT_CODE,
	GPIOD_PORT_CODE,
	GPIOE_PORT_CODE,
	GPIOF_PORT_CODE,
	GPIOG_PORT_CODE,
	GPIOH_PORT_CODE,
	GPIOI_PORT_CODE,
};

/*
0x4002 2000 - 0x4002 23FF GPIOI
0x4002 1C00 - 0x4002 1FFF GPIOH
0x4002 1800 - 0x4002 1BFF GPIOG
0x4002 1400 - 0x4002 17FF GPIOF
0x4002 1000 - 0x4002 13FF GPIOE
0x4002 0C00 - 0x4002 0FFF GPIOD
0x4002 0800 - 0x4002 0BFF GPIOC
0x4002 0400 - 0x4002 07FF GPIOB
0x4002 0000 - 0x4002 03FF GPIOA
*/

PRIVATE void Gpio_Periph_Clock_Enr(GPIO_RegDef_t* pGpıoX);
PRIVATE uint8_t Get_Port_Code(GPIO_RegDef_t* pGpıoX);
PUBLIC void Gpio_Init(Gpio_Handle_t *pGpio_Handle);

PUBLIC void Gpio_Write_Output_Pin(GPIO_RegDef_t *pGpioX, uint8_t pin_no, uint8_t val );
PUBLIC void Gpio_Write_Output_Port(GPIO_RegDef_t *pGpioX, uint16_t val);
PUBLIC void Gpio_Toggle_Output_Pin(GPIO_RegDef_t *pGpioX, uint8_t pin_no);
PUBLIC uint32_t Gpio_Read_Input_Pin(GPIO_RegDef_t *pGpioX, uint8_t pin_no);
PUBLIC void Clear_Pending_Reg(uint8_t pin_no);
#endif /* GPIO_H_ */
