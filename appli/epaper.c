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

int EPAPER_display_info(void)
{
	static unsigned char frame_buffer[(EPD_WIDTH * EPD_HEIGHT / 8)];

	EPD epd;
	if (EPD_Init(&epd) != 0)
	{
		printf("e-Paper init failed\n");
		while(1);
	}

	Paint paint;
	Paint_Init(&paint, frame_buffer, epd.width, epd.height);
	Paint_Clear(&paint, UNCOLORED);

	/* Draw something to the frame_buffer */
	/* For simplicity, the arguments are explicit numerical coordinates */
	Paint_DrawRectangle(&paint, 20, 80, 180, 280, COLORED);
	Paint_DrawLine(&paint, 20, 80, 180, 280, COLORED);
	Paint_DrawLine(&paint, 180, 80, 20, 280, COLORED);
	Paint_DrawFilledRectangle(&paint, 200, 80, 360, 280, COLORED);
	Paint_DrawCircle(&paint, 300, 160, 60, UNCOLORED);
	Paint_DrawFilledCircle(&paint, 90, 210, 30, COLORED);

	/*Write strings to the buffer */
	Paint_DrawFilledRectangle(&paint, 0, 6, 400, 30, COLORED);
	Paint_DrawStringAt(&paint, 100, 10, "NDE DARIUS", &Font24, UNCOLORED);
	Paint_DrawStringAt(&paint, 100, 40, "STEUVEUh", &Font24, COLORED);

	while(1)
	{
		/* Display the frame_buffer */
		EPD_DisplayFrame(&epd, gImage_eole_1);

		HAL_Delay(2000);
		/* Display the image buffer */
		EPD_DisplayFrame(&epd, gImage_eole_2);

		HAL_Delay(2000);

		EPD_DisplayFrame(&epd,gImage_eole_3);
		HAL_Delay(2000);

		EPD_DisplayFrame(&epd,gImage_eole_4);
		HAL_Delay(2000);
	}
}



#endif






