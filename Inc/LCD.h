/*
 * LCD.h
 *
 *  Created on: Jan 27, 2024
 *      Author: ASUS
 */

#ifndef LCD_H_
#define LCD_H_
#include <stm32f407xx.h>
#include "GPIO.h"

#define LCD_GPIO_PORT GPIOD

enum{
	LCD_GPIO_RS,//GPIOD pin 0
	LCD_GPIO_RW,//GPIOD pin 1
	LCD_GPIO_EN,//GPIOD pin 2
	LCD_GPIO_PD4,//GPIOD pin 3
	LCD_GPIO_PD5,//GPIOD pin 4
	LCD_GPIO_PD6,//GPIOD pin 5
	LCD_GPIO_PD7,//GPIOD pin 6
};

#define LCD_CMD_4DL_2N_F5X8		0x28
#define LCD_CMD_DON_CON_BON		0x0F
#define LCD_CMD_INC_NO_SHIFT	0x06
#define LCD_CMD_CLEAR			0x01


void lcd_init();
void write_nibble(uint8_t val);
void Lcd_clear_display();
void lcd_send_command(uint8_t cmd);
void lcd_print_char(uint8_t data);
void lcd_print_string(const char* message);
void lcd_display_on(uint8_t mode);
//tasınabilir
void delay_ms(uint32_t delay);
void delay_us(uint32_t delay);



#endif /* LCD_H_ */
