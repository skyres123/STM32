#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"



int main(void){



	tim2_pa5_pwm();

while(1){
	for(int i=0;i<26666;i++){
		analogWrite(i);
		//systickDelayMs(1000);
	}
	for(int j=26666;j>0;j--){
		analogWrite(j);
		//systickDelayMs(1000);
		}
}

}


