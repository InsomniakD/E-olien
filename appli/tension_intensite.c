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

uint32_t moyT;
uint32_t addT;

uint32_t moyI;
uint32_t addI;

uint32_t moyP;
uint32_t addP;

uint32_t moyPrvsP;
uint32_t moyPrvsT;
uint32_t moyPrvsI;

uint32_t i=0;

void tension(void)
	{
		valueT = ADC_getValue(ADC_TENSION_CHANNEL);
		valeurT=((uint32_t)(valueT)*11*3300)/4096;//on le convertit en mV pour pouvoir faire la conversion et rester en entier, on a 3300 mV en max, on multiplie par 11 parce que c'est la valeur de notre pont diviseur de tension, et on divise par 4086 parce que on aura une valeur sur 4096
		debug_printf("La tension est : %d.%02dV\n", valeurT/1000,(valeurT%1000)/10);//On affiche la valeur en V, en affichant le nombre, en mettant une virgule après 2 chiffres(conversion en V), et on affiche les valeurs après .
	}

void intensite(void)
	{
		while(1)
			{HAL_Delay(200);
			valueI = ADC_getValue(ADC_INTENSITE_CHANNEL);
			debug_printf("L'intensité est : %dmA\n", valueI);// On divise par la résistance de 1ohm, donc on divise par 1; et on obitent une valeur directement en mA
			}

		//valeurI=((uint32_t)(valueI)*11*3300)/4096;//on le convertit en mV pour pouvoir faire la conversion et rester en entier, on a 3300 mV en max, on multiplie par 11 parce que c'est la valeur de notre pont diviseur de tension, et on divise par 4086 parce que on aura une valeur sur 4096
		//debug_printf("L'intensité est : %dmA\n", valeurI);// On divise par la résistance de 1ohm, donc on divise par 1; et on obitent une valeur directement en mA
	}

void tension_intensite_puissance(void)
	{
	while(1)
			{
				HAL_Delay(500);
				valueT = ADC_getValue(ADC_TENSION_CHANNEL);
				valueI = ADC_getValue(ADC_INTENSITE_CHANNEL);
				valeurT=((uint32_t)(valueT)*11*3300)/4096;//on le convertit en mV pour pouvoir faire la conversion et rester en entier, on a 3300 mV en max, on multiplie par 11 parce que c'est la valeur de notre pont diviseur de tension, et on divise par 4086 parce que on aura une valeur sur 4096
				valeurI=((uint32_t)(valueI)*11*3300)/4096;
				valeurP=valeurT*valeurI;
				debug_printf("La tension est : %d.%02dV\n", valeurT/1000,(valeurT%1000)/10);
				debug_printf("L'intensité est : %dmA\n", valeurI);
				debug_printf("La puissance générée est : %dµW\n", valeurP);
				}
	}

void moyenne(void)
	{
	while(1)
				{
				HAL_Delay(200);
				valueT = ADC_getValue(ADC_TENSION_CHANNEL);
				valueI = ADC_getValue(ADC_INTENSITE_CHANNEL);
				valeurT=((uint32_t)(valueT)*11*3300)/4096;//on le convertit en mV pour pouvoir faire la conversion et rester en entier, on a 3300 mV en max, on multiplie par 11 parce que c'est la valeur de notre pont diviseur de tension, et on divise par 4086 parce que on aura une valeur sur 4096
				valeurI=((uint32_t)(valueI)*11*3300)/4096;
				valeurP=valeurT*valeurI;
				addT=addT+valeurT;
				addI=addI+valeurI;
				addP=addP+valeurP;
				i++;
				if(i==32){
					i=0; //remise à zero du compteur
					if(moyPrvsP==0 && moyPrvsT==0 && moyPrvsP==0){
						moyT=addT/32;
						moyI=addI/32;
						moyP=addP/32;
					}else{
					moyT=(addT+moyPrvsT)/33;
					moyI=(addI+moyPrvsI)/33;
					moyP=(addP+moyPrvsP)/33;
					}
					debug_printf("La tension moyenne est : %d.%02dV\n", moyT/1000,(moyT%1000)/10);
					debug_printf("L'intensité moyenne est : %dmA\n", moyI);
					debug_printf("La puissance moyenne générée est : %dmW\n", moyP/10000);
					moyPrvsP=moyP;
					moyPrvsT=moyT;
					moyPrvsI=moyI;
					addT=addI=addP=0;
					}

				}
	}

