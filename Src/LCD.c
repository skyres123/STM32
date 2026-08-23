/*
 * LCD.c
 *
 *  Created on: Jan 27, 2024
 *      Author: ASUS
 */
#include "LCD.h"
void write_nibble(uint8_t val){

	/*Gpio_Write_Output_Pin(LCD_GPIO_PORT,LCD_GPIO_PD4,((val>>0)&0x1));
	Gpio_Write_Output_Pin(LCD_GPIO_PORT,LCD_GPIO_PD5,((val>>1)&0x1));
	Gpio_Write_Output_Pin(LCD_GPIO_PORT,LCD_GPIO_PD6,((val>>2)&0x1));
	Gpio_Write_Output_Pin(LCD_GPIO_PORT,LCD_GPIO_PD7,((val>>3)&0x1));*/

	Gpio_Write_Output_Pin(LCD_GPIO_PORT,LCD_GPIO_PD7,((val>>3)&0x1));
	Gpio_Write_Output_Pin(LCD_GPIO_PORT,LCD_GPIO_PD6,((val>>2)&0x1));
	Gpio_Write_Output_Pin(LCD_GPIO_PORT,LCD_GPIO_PD5,((val>>1)&0x1));
	Gpio_Write_Output_Pin(LCD_GPIO_PORT,LCD_GPIO_PD4,((val>>0)&0x1));


	Gpio_Write_Output_Pin(LCD_GPIO_PORT,LCD_GPIO_EN,GPIO_PIN_SET);
	delay_us(60);
	Gpio_Write_Output_Pin(LCD_GPIO_PORT,LCD_GPIO_EN,GPIO_PIN_RESET);
	delay_us(40);
}

PUBLIC void lcd_send_command(uint8_t cmd){
	Gpio_Write_Output_Pin(LCD_GPIO_PORT,LCD_GPIO_RS,GPIO_PIN_RESET);//rs=0 lcd command
	Gpio_Write_Output_Pin(LCD_GPIO_PORT,LCD_GPIO_RW,GPIO_PIN_RESET);//RW=0  lcd command

	write_nibble(cmd>>4);//yüksek anlamlı dört bit
	write_nibble(cmd & 0x0F);//düşük anlamlı 4 bit
}
void lcd_print_char(uint8_t data){
	Gpio_Write_Output_Pin(LCD_GPIO_PORT,LCD_GPIO_RS,GPIO_PIN_SET);//rs=1 lcd command
	Gpio_Write_Output_Pin(LCD_GPIO_PORT,LCD_GPIO_RW,GPIO_PIN_RESET);//RW=0  lcd command

	write_nibble((data>>4)&0x0F);//yüksek anlamlı dört bit
	write_nibble(data & 0x0F);//düşük anlamlı 4 bit
}
void lcd_print_string(const char* message){
	while(*message=='\0'){
		lcd_print_char((uint8_t)*message);
		*message++;
	}
}
void lcd_clear_display(){
	lcd_send_command(LCD_CMD_CLEAR);

}
void lcd_display_on(uint8_t mode){
	lcd_send_command(0x08|mode);
}
void lcd_init(){
	//1. gpıo pin init
	Gpio_Handle_t lcd_pin = {LCD_GPIO_PORT,{LCD_GPIO_RS,GPIO_MODE_OUT,GPIO_SPEED_MEDIUM,GPIO_OTYPE_PP,GPIO_PIN_PUPD_NO}};
	Gpio_Init(&lcd_pin);//0 ıncı pini tanımladık


	for(int i=1;i<7;++i){
		lcd_pin.Gpio_PinConfig.PinNumber =i;
		Gpio_Init(&lcd_pin);//1 den 7 ye kadar olan pinleri for döngüsü ile initialize ettik(rs,rw,en ve data hatları)
	}

	delay_ms(80);//min 40ms
	//rs=0 lcd command
	Gpio_Write_Output_Pin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET);
	//rw=0 write lcd
	Gpio_Write_Output_Pin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);
	write_nibble(0x03);
	delay_ms(5);//min 4.1 ms
	write_nibble(0x03);
	delay_us(110);//min 100us
	write_nibble(0x03);
	write_nibble(0x02);

	//00 10 N F  * * //Function set	00 10 10 00		0x28
	lcd_send_command(LCD_CMD_4DL_2N_F5X8);//function set commnad 4 bit data len fon 5*8
	lcd_send_command(0x08);//	LCD_CMD_DON_CON_BON		display on cursor on blink on
	lcd_send_command(0x01);//lcd display
	lcd_send_command(LCD_CMD_INC_NO_SHIFT);//0x06
	//lcd_display_on()?? 0xC decimal 12 0b1100
	lcd_display_on(LCD_CMD_DON_CON_BON);

}
void delay_ms(uint32_t delay){
	for(uint32_t i =0;i<(delay*1000);i++);
}
void delay_us(uint32_t delay){
	for(uint32_t i =0;i<(delay*1);i++);
}
