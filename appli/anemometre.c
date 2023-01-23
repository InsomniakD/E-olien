/**
  *
  * \file    humidite.c
  * \author  Timothé.D
  * \version V1.0
  * \date    1 December 2022
  * \brief   Programme qui mesure la vitesse du vent
  *
  *Permets par le biais de plusieurs fonctions de mesurer la vitesse du vent.
  *
  *
*/


#include "config.h"
#if USE_ANEMOMETRE

#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_gpio.h"
#include "stm32f1_extit.h"
#include "anemometre.h"
#include "systick.h"

#define TIMEOUT	10000 // edit when rotation count increase

float vitesse;
uint32_t rotation;
bool_e flag_duration;
uint32_t duration;
uint32_t begin;
uint32_t end;



/**
 * \fn void countup()
 * \brief Fonction qui effectue le compte des rotation de l'anémomètre
 *
 *Si le nombre de rotation est 6 alors on définis la durée total pour laquel ces 6 tours on été éffectués
 */

void countup()
{
  rotation++;
  if(rotation >= 6){  //time out when end is upper than uint 16
  		end = HAL_GetTick();
  		duration = end - begin;
  		flag_duration = TRUE;
  		begin = end;
  		rotation = 0;
  	}
}


/**
 * \fn void Vent_init(void)
 * \brief Fonction qui effectue l'initialisation du capteur
 *
 * Permets d'initialiser les ports et de créer un calback pour appeler à chaque impulsion provenant de
 * l'anémomètre soit pour chaque tours.
 */

void Vent_init(void)
{
	BSP_GPIO_PinCfg(ANEMO_GPIO, ANEMO_PIN, GPIO_MODE_IT_RISING,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);
	EXTIT_set_callback(&countup, EXTI_gpiopin_to_pin_number(ANEMO_PIN), TRUE);
}

/**
 * \fn int Vent_vitesse(void){
 * \brief Fonction quic calcul la vitesse du vent.
 *
 * \return la vitesse du vent en km/h si duration à une valeur,  0 sinon.
 *
 */

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
