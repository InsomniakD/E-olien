/*
 * anemometre.h
 *
 *  Created on: 24 nov. 2022
 *      Author: timot
 */

#ifndef ANEMOMETRE_H_
#define ANEMOMETRE_H_
#include "config.h"
#define readanemo
#if USE_ANEMOMETRE

#include <stdint.h>
#include "macro_types.h"
#include "stm32f1xx_hal.h"
void Vent_init(void);

#endif /* ANEMOMETRE_H_ */
#endif
