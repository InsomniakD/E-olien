/*
 * tension_intensite.h
 *
 *  Created on: 24 nov. 2022
 *      Author: timot
 */

#ifndef TENSION_INTENSITE_H_
#define TENSION_INTENSITE_H_
#include "config.h"
#if USE_TENSION_INTENSITE

#include <stdint.h>
#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "macro_types.h"
#include "stm32f1_gpio.h"
#include "stm32f1_adc.h"

void tension(void);
void intensite(void);
void puissance(void);

#endif /* TENSION_INTENSITE_H_ */
#endif
