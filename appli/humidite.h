/*
 * temperature_humidite.h
 *
 *  Created on: 24 nov. 2022
 *      Author: timot
 */

#ifndef DHT11_H_
#define DHT11_H_
#include "config.h"
#if USE_DHT11

#include <stdint.h>
#include "macro_types.h"
#include "stm32f1xx_hal.h"

uint8_t humidite_valeur(void);
void humidite_init(GPIO_TypeDef * GPIOx, uint16_t GPIO_PIN_x);

running_e humidite_state_machine_get_datas(uint8_t * humidity_int, uint8_t * humidity_dec, uint8_t * temperature_int, uint8_t * temperature_dec);

#endif /* DHT11_H_ */
#endif
