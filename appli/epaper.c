/**
  *
  * \file    epaper.c
  * \author  Timothé.D
  * \version V1.0
  * \date    1 December 2022
  * \brief   Programme pour l'utilisation de l'Epaper
  *
  * Ce programme contient les fonctions principale utilisé par l'epaper.
  *
  *
*/
#include "config.h"
#if USE_EPAPER
#include "stm32f1xx_hal.h"
#include "stm32f1xx_nucleo.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "macro_types.h"
#include "stm32f1_gpio.h"
#include "epaper/epd4in2.h"
#include "epaper/epdif.h"
#include "epaper/epdpaint.h"
#include "image_epaper.h"
#define COLORED      1
#define UNCOLORED    0


static void Animation_State_Machine();
static unsigned char frame_buffer[(200*300 / 8)]; //7500
EPD epd;


/**
 * \fn void EPAPER_display_info(char preschar[30],char tempchar[30],char humichar[30],char vitchar[30],char tenschar[30],char  puischar[30])
 * \brief Fonction qui permet la modification des images et qui les envoie vers l'epaper.
 *
 *Les différents paramètres sont ecrit sur une moitié d'image ensuite la machine à états est appelé.
 *
 * \param preschar[30] (tableau de caractères char avec la valeur de la pression), tempchar[30] (tableau de caractères char avec la valeur de la temperature), humichar[30] (tableau de caratère char pour l'humidité), vitchar[30] (tableau de caratère char pour la vitesse), tenschar[30] (tableau de caratère char pour la tension moyenne), puischar[30] (tableau de caratère char pour la puissance moyenne)
 */

void EPAPER_display_info(char preschar[30],char tempchar[30],char humichar[30],char vitchar[30],char tenschar[30],char  puischar[30])
{
	//static unsigned char frame_buffer[(EPD_WIDTH * EPD_HEIGHT / 8)];

	if (EPD_Init(&epd) != 0)
	{
		//printf("e-Paper init failed\n");
		while(1);
	}

	for(int i = 0; i<7500; i++){
		frame_buffer[i] = gImage_blank[i];
	}

	for(int i = 0; i<300; i++)
		frame_buffer[200*i/8] = 0xFF;



	Paint paint;
	Paint_Init(&paint, frame_buffer, 200, 300);
	//Paint_Clear(&paint, UNCOLORED);

	/*Write strings to the buffer */
	Paint_DrawStringAt(&paint, 30, 70,preschar , &Font12, COLORED);
	Paint_DrawStringAt(&paint, 30, 100, tempchar, &Font12, COLORED);
	Paint_DrawStringAt(&paint, 30, 130, humichar, &Font12, COLORED);
	Paint_DrawStringAt(&paint, 30, 160, vitchar, &Font12, COLORED);
	Paint_DrawStringAt(&paint, 30, 190, tenschar, &Font12, COLORED);
	Paint_DrawStringAt(&paint, 30, 220, puischar, &Font12, COLORED);

	Animation_State_Machine();


}

/**
 * \fn static void Animation_State_Machine(
 * \brief Fonction machine à états
 *
 *Elle permet une animation et procède par le biais de la librairie de l'epaper à l'envoie de l'image avec
 *le texte (partie gauche de l'écran de l'epaper) et en même temps de l'image de l'eolienne (partie gauche
 *de l'écran de l'epaper) à chaque état les données sont de nouveaux afficher et l'image de l'eolienne change
 *(pâles qui tournent)
 *
 *
 */


static void Animation_State_Machine(){

	/**
	 * \enum state_e
	 * \brief Différente images a afficher.
	 *
	 * state_e est une série de constantes prédéfinie pour le changement d'état dans la machine à états
	 */
	typedef enum    //definition des états
	{
	IMAGE_1,
	IMAGE_2,
	IMAGE_3,
	IMAGE_4,
	}state_e;

	static  state_e state = IMAGE_1; //définition de l'état initial

	switch(state) //switch de changement d'état
	{
	case IMAGE_1:
		EPD_DisplayFrameMem(&epd, frame_buffer, gImage_eole1); // Affichage d'une certaine image sur l'epaper
		state = IMAGE_2;	//Passage à l'état suivant lors du prochain appel de la fonction
		break;

	case IMAGE_2:
		EPD_DisplayFrameMem(&epd, frame_buffer, gImage_eole2); // affichage d'une certaine image sur l'epaper
		state = IMAGE_3;	//Passage à l'état suivant lors du prochain appel de la fonction
		break;

	case IMAGE_3:
		EPD_DisplayFrameMem(&epd, frame_buffer, gImage_eole3); // affichage d'une certaine image sur l'epaper
		state = IMAGE_4;	//Passage à l'état suivant lors du prochain appel de la fonction
		break;

	case IMAGE_4:
		EPD_DisplayFrameMem(&epd, frame_buffer, gImage_eole4); // affichage d'une certaine image sur l'epaper
		state = IMAGE_1;	//Passage à l'état initial lors du prochain appel de la fonction
		break;
	default:
		break;

	}
}

#endif






