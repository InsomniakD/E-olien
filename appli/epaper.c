/*
 * epaper.c
 *
 *  Created on: 24 nov. 2022
 *      Author: timot
 */


/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
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

int EPAPER_display_info(char preschar[30],char tempchar[30],char humichar[30],char vitchar[30],char tenschar[30],char  puischar[30])
{

	if (EPD_Init(&epd) != 0)
	{
		//printf("e-Paper init failed\n");
		while(1);
	}

	for(int i = 0; i<7500; i++){
		frame_buffer[i] = 0xFF;
	}

	//for(int i = 0; i<300; i++)
		//frame_buffer[200*i/8] = 0xFF;



	Paint paint;
	Paint_Init(&paint, frame_buffer, 200, 300);

	/*Write strings to the buffer */
	Paint_DrawStringAt(&paint, 30, 70,preschar , &Font12, COLORED);
	Paint_DrawStringAt(&paint, 30, 100, tempchar, &Font12, COLORED);
	Paint_DrawStringAt(&paint, 30, 130, humichar, &Font12, COLORED);
	Paint_DrawStringAt(&paint, 30, 160, vitchar, &Font12, COLORED);
	Paint_DrawStringAt(&paint, 30, 190, tenschar, &Font12, COLORED);
	Paint_DrawStringAt(&paint, 30, 220, puischar, &Font12, COLORED);

	Animation_State_Machine();
}

static void Animation_State_Machine(){
				typedef enum
				{
				IMAGE_1,
				IMAGE_2,
				IMAGE_3,
				IMAGE_4,
				}state_e;

				static  state_e previous_state = IMAGE_1;
				static  state_e state = IMAGE_1;

				switch(state)
				{
				case IMAGE_1:
					EPD_DisplayFrameMem(&epd, frame_buffer, gImage_eole1);
					state = IMAGE_2;
					break;

				case IMAGE_2:
					EPD_DisplayFrameMem(&epd, frame_buffer, gImage_eole2);
					state = IMAGE_3;
					break;

				case IMAGE_3:
					EPD_DisplayFrameMem(&epd, frame_buffer, gImage_eole3);
					state = IMAGE_4;
					break;

				case IMAGE_4:
					EPD_DisplayFrameMem(&epd, frame_buffer, gImage_eole4);
					state = IMAGE_1;
					break;
				default:
					break;

				}
}

#endif






