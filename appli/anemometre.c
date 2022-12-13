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


float vitesse;
uint32_t rotation;
bool_e flag_duration;
uint16_t duration;
uint16_t begin;
uint16_t end;

void countup()
{
  rotation++;
  if(rotation == 10){  //time out when end is upper than uint 16
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

void Vent_vitesse(void){

	if(flag_duration)
	{
		flag_duration = FALSE;
		printf("%d\n", duration);
		printf("La vitesse du vent est : | vitesse = %d km/h\n", 10/2*2.4/duration);
	}
}


	/*
	rotation = 0 ;
	//HAL_GPIO_EXTI_Callback(ANEMO_PIN)

	HAL_Delay(1000 * RecordTime);
	EXTIT_set_callback(&countup, EXTI_gpiopin_to_pin_number(ANEMO_PIN), FALSE);
	vitesse = (float)rotation / (float)RecordTime * 2,4;

	return (int)vitesse;
	*/




/*
void donnees(void)
{
	debug_printf("La vitesse du vent est : | vitesse = %d km/h\n", Vent_vitesse());
}
*/




#endif
