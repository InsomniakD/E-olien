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
#define ADC_INTENSITE_CHANNEL		ADC_1 //il doit pas marcher et ne prend pas ce qu'il se passe sur PA1

int16_t valueT;
uint32_t valeurT;

int16_t valueI;
uint32_t valeurI;

int16_t valueP;
uint32_t valeurP;

void tension(void)
	{
		valueT = ADC_getValue(ADC_TENSION_CHANNEL);
		valeurT=((uint32_t)(valueT)*11*3300)/4096;//on le convertit en mV pour pouvoir faire la conversion et rester en entier, on a 3300 mV en max, on multiplie par 11 parce que c'est la valeur de notre pont diviseur de tension, et on divise par 4086 parce que on aura une valeur sur 4096
		debug_printf("La tension est : %d.%02dV\n", valeurT/1000,(valeurT%1000)/10);//On affiche la valeur en V, en affichant le nombre, en mettant une virgule après 2 chiffres(conversion en V), et on affiche les valeurs après .
	}

void intensite(void)
	{
		while(1)
			{HAL_Delay(20);
			valueI = ADC_getValue(ADC_INTENSITE_CHANNEL);
			debug_printf("L'intensité est : %dmA\n", valueI);// On divise par la résistance de 1ohm, donc on divise par 1; et on obitent une valeur directement en mA
			}
		valeurI=((uint32_t)(valueI)*11*3300)/4096;//on le convertit en mV pour pouvoir faire la conversion et rester en entier, on a 3300 mV en max, on multiplie par 11 parce que c'est la valeur de notre pont diviseur de tension, et on divise par 4086 parce que on aura une valeur sur 4096
		debug_printf("L'intensité est : %dmA\n", valeurI);// On divise par la résistance de 1ohm, donc on divise par 1; et on obitent une valeur directement en mA
	}

void puissance(void)
	{
	valueP= ADC_getValue(ADC_INTENSITE_CHANNEL)*ADC_getValue(ADC_TENSION_CHANNEL);
	valeurP=(((uint32_t)(valueI)*11*3300)/4096)*(((uint32_t)(valueT)*11*3300)/4096);
	debug_printf("La puissance générée est : %dµW\n", valeurP);//mV*mA=µW

	}
