/*
 * anemometre.c
 *
 *  Created on: 24 nov. 2022
 *      Author: timot
 */


#include "config.h"
#if USE_ANEMOMETRE

#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_gpio.h"
#include "stm32f1_extit.h"
#include "anemometre.h"
#include "systick.h"

#define TIMEOUT	5000 // edit when rotation count increase

float vitesse;
uint32_t rotation;
bool_e flag_duration;
uint32_t duration;
uint32_t begin;
uint32_t end;

void countup()
{
  rotation++;
  if(rotation == 6){  //time out when end is upper than uint 16
  		end = HAL_GetTick();
  		duration = end - begin;
  		flag_duration = TRUE;
  		begin = end;
  		rotation = 0;
  	}
}


void Vent_init(void)
{
	BSP_GPIO_PinCfg(ANEMO_GPIO, ANEMO_PIN, GPIO_MODE_IT_RISING,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);
	EXTIT_set_callback(&countup, EXTI_gpiopin_to_pin_number(ANEMO_PIN), TRUE);
}




int Vent_vitesse(void){
	while(1){
		if(flag_duration)
		{
			flag_duration = FALSE;
			//printf("%d\n", duration);
			if(duration){
				//printf("La vitesse du vent est : | vitesse = %d km/h\n", (6*24*100/duration)); // 2.4 * 1000(ms to sec) --> 24 * 100 pour eviter la virgule et un bug
				return 6*24*100/duration;
			}
			else{
				//printf("La vitesse du vent est trop faible\n");
				return 0;
			}
		}

		if(HAL_GetTick() - begin > TIMEOUT)
		{
			rotation = 0;
			begin = HAL_GetTick();
			flag_duration = TRUE;
			duration = 0;
		}
	}
}




#endif
