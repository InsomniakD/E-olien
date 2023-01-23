/**
  *
  * \file    humidite.c
  * \author  Thomas.C
  * \version V1.0
  * \date    1 December 2022
  * \brief   Programme qui mesure la vitesse du vent
  *
  *Permets par le biais de plusieurs fonctions de mesurer la vitesse du vent.
  *
  *
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

uint32_t durationti = 5000; //temps de mesure de tension
uint32_t beginti;

uint32_t i=0;

uint32_t valeurs_moyennes[4];



/**
 * \fn void tension(void)
 * \brief Fonction qui permet le calcul et l'affichage de la tension.
 *
 */

void tension(void)
	{
		valueT = ADC_getValue(ADC_TENSION_CHANNEL);
		valeurT=((uint32_t)(valueT)*11*3300)/4096;//on le convertit en mV pour pouvoir faire la conversion et rester en entier, on a 3300 mV en max, on multiplie par 11 parce que c'est la valeur de notre pont diviseur de tension, et on divise par 4086 parce que on aura une valeur sur 4096
		//debug_printf("La tension est : %d.%02dV\n", valeurT/1000,(valeurT%1000)/10);//On affiche la valeur en V, en affichant le nombre, en mettant une virgule apr�s 2 chiffres(conversion en V), et on affiche les valeurs apr�s .
	}


/**
 * \fn void intensite(void)
 * \brief Fonction qui permet le calcul et l'affichage de l'intensité.
 *
 */
void intensite(void)
	{
		while(1)
			{HAL_Delay(200);
			valueI = ADC_getValue(ADC_INTENSITE_CHANNEL);
			//debug_printf("L'intensit� est : %dmA\n", valueI);// On divise par la r�sistance de 1ohm, donc on divise par 1; et on obitent une valeur directement en mA
			}

		//valeurI=((uint32_t)(valueI)*11*3300)/4096;//on le convertit en mV pour pouvoir faire la conversion et rester en entier, on a 3300 mV en max, on multiplie par 11 parce que c'est la valeur de notre pont diviseur de tension, et on divise par 4086 parce que on aura une valeur sur 4096
		//debug_printf("L'intensit� est : %dmA\n", valeurI);// On divise par la r�sistance de 1ohm, donc on divise par 1; et on obitent une valeur directement en mA
	}

/**
 * \fn void tension_intensite_puissance(void)
 * \brief Fonction qui permet le calcul et l'affichage de la tension, l'intensité et la puissance.
 *
 */

void tension_intensite_puissance(void)
	{

	while(1)
			{

				valueT = ADC_getValue(ADC_TENSION_CHANNEL);
				valueI = ADC_getValue(ADC_INTENSITE_CHANNEL);
				valeurT=((uint32_t)(valueT)*11*3300)/4096;//on le convertit en mV pour pouvoir faire la conversion et rester en entier, on a 3300 mV en max, on multiplie par 11 parce que c'est la valeur de notre pont diviseur de tension, et on divise par 4086 parce que on aura une valeur sur 4096
				valeurI=((uint32_t)(valueI)*11*3300)/4096;
				valeurP=valeurT*valeurI;
				//debug_printf("La tension est : %d.%02dV\n", valeurT/1000,(valeurT%1000)/10);
				//debug_printf("L'intensite est : %dmA\n", valeurI);
				//debug_printf("La puissance est : %dmW\n\n", valeurP);
				HAL_Delay(1000);
				}
	}

/**
 * \fn uint32_t *moyenne(void)
 * \brief Fonction qui permet le calcul de la tension moyenne, l'intensité moyenne et la puissance moyenne
 *
 * \return valeurs_moyennes un tableau de valeur avec à l'emplacement 0 la valeur de la tenssion moyenne, à l'emplacement 1 la valeur de l'intensité moyenne et à l'emplacement 2 la valeur de la puissance moyenne.
 */



uint32_t *moyenne(void)
	{
	beginti = HAL_GetTick();
	while(1){
			if(HAL_GetTick() - beginti < durationti){
				valueT = ADC_getValue(ADC_TENSION_CHANNEL);
				valueI = ADC_getValue(ADC_INTENSITE_CHANNEL);
				valeurT=((uint32_t)(valueT)*11*3300)/4096;//on le convertit en mV pour pouvoir faire la conversion et rester en entier, on a 3300 mV en max, on multiplie par 11 parce que c'est la valeur de notre pont diviseur de tension, et on divise par 4086 parce que on aura une valeur sur 4096
				valeurI=((uint32_t)(valueI)*11*3300)/4096;
				valeurP=valeurT*valeurI;
				addT=addT+valeurT;
				addI=addI+valeurI;
				addP=addP+valeurP;
				i++;
				if(i>=32){
					i=0; //remise � zero du compteur
					if(moyPrvsP==0 && moyPrvsT==0 && moyPrvsP==0){
						moyT=addT/32;
						moyI=addI/32;
						moyP=addP/32;
					}else{
					moyT=(addT+moyPrvsT)/33;
					moyI=(addI+moyPrvsI)/33;
					moyP=(addP+moyPrvsP)/33;
					}
					moyPrvsP=moyP;
					moyPrvsT=moyT;
					moyPrvsI=moyI;
					addT=addI=addP=0;
					}
				HAL_Delay(200);
				}
			else{
				//return moyT, moyI, moyP;
				//debug_printf("La tension moyenne est : %d.%02dV\nL'intensite moyenne est : %dmA\nLa puissance moyenne est : %dmW\n\n", moyT/1000,(moyT%1000)/10, moyI, moyP/10000);
				valeurs_moyennes[0] = moyT/1000;
				valeurs_moyennes[1] = (moyT%1000)/10;
				valeurs_moyennes[2] = moyI;
				valeurs_moyennes[3] = moyP/10000;
				return valeurs_moyennes;
			}
		}

	}

