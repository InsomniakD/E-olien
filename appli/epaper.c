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
#define COLORED      0
#define UNCOLORED    1

int EPAPER_display_info()
{
	static unsigned char frame_buffer[(EPD_WIDTH * EPD_HEIGHT / 8)];

	EPD epd;
	if (EPD_Init(&epd) != 0)
	{
		printf("e-Paper init failed\n");
		while(1);
	}

	for(int i = 0; i<15000; i++){
		frame_buffer[i] = gImage_eole_1[i];
	}

	Paint paint;
	Paint_Init(&paint, frame_buffer, epd.width, epd.height);
	//Paint_Clear(&paint, UNCOLORED);

	/*Write strings to the buffer */
	Paint_DrawStringAt(&paint, 30, 70, "test", &Font12, UNCOLORED);
	Paint_DrawStringAt(&paint, 30, 100, "Pression : hPa", &Font12, UNCOLORED);
	Paint_DrawStringAt(&paint, 30, 130, "Humidité : %%", &Font12, UNCOLORED);
	Paint_DrawStringAt(&paint, 30, 160, "Vitesse du vent : km/h", &Font12, UNCOLORED);
	Paint_DrawStringAt(&paint, 30, 190, "Tension moyenne : V", &Font12, UNCOLORED);
	Paint_DrawStringAt(&paint, 30, 220, "Puissance moyenne : W", &Font12, UNCOLORED);
	EPD_DisplayFrame(&epd, frame_buffer);

	/*
	while(1)
	{
		// Display the frame_buffer
		EPD_DisplayFrame(&epd, gImage_eole_1);

		HAL_Delay(2000);
		// Display the image buffer
		EPD_DisplayFrame(&epd, gImage_eole_2);

		HAL_Delay(2000);

		EPD_DisplayFrame(&epd,gImage_eole_3);
		HAL_Delay(2000);

		EPD_DisplayFrame(&epd,gImage_eole_4);
		HAL_Delay(2000);
	}
*/
}



#endif






