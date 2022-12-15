/*
 * tension_intensite.c
 *
 *  Created on: 24 nov. 2022
 *      Author: timot
 */


//test

//#define ADC_TENSION_CHANNEL	AN0
#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "macro_types.h"
#include "stm32f1_gpio.h"
#include "stm32f1_adc.h"

#define ADC_TENSION_CHANNEL		ADC_0
#define ADC_INTENSITE_CHANNEL		ADC_1

int16_t value;
uint32_t valeur;

// on va plutot utiliser le mV
// on va plutot le mettre sur 1024 puis le reconvertir , on multiplie puis on divise ( on peut pas l'inverse)

void tension(void)
	{
		value = ADC_getValue(ADC_TENSION_CHANNEL);
		valeur=((uint32_t)(value)*11*3300)/4096;//on le convertit en mV pour pouvoir faire la conversion et rester en entier, on a 3300 mV en max, on multiplie par 11 parce que c'est la valeur de notre pont diviseur de tension, et on divise par 4086 parce que on aura une valeur sur 4096
		debug_printf("La tension est : %d.%02d\n", valeur/1000,(valeur%1000)/10);//On affiche la valeur en V, en affichant le nombre, en mettant une virgule après 2 chiffres(conversion en V), et on affiche les valeurs après .
	}

/*void intensite(void)
	{
			ADC_init();
		value = ADC_getValue(ADC_INTENSITE_CHANNEL);
		printf("%lf\n", value);

	}
*/
