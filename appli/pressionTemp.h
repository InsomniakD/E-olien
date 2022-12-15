/*
 * pression.h
 *
 *  Created on: 13 déc. 2022
 *      Author: timot
 */

#ifndef PRESSIONTEMP_H_
#define PRESSIONTEMP_H_

#include "config.h"
#if USE_BMP180
#include "stm32f1_i2c.h"

#include "stm32f1xx.h"
#include "stm32f1_i2c.h"
#include "math.h"

/* Default I2C pin */
#ifndef BMP180_I2C
#define BMP180_I2C					I2C1
//#define BMP180_I2C_PINSPACK			I2C_PinsPack_1
#endif

/* Default I2C speed */
#ifndef BMP180_I2C_SPEED
#define BMP180_I2C_SPEED			100000
#endif

/* BMP180 I2C address */
#ifndef BMP180_I2C_ADDRESS
#define BMP180_I2C_ADDRESS			0xEE
#endif

/* Registers */
#define	BMP180_REGISTER_CONTROL 	0xF4
#define	BMP180_REGISTER_RESULT 		0xF6
#define BMP180_REGISTER_EEPROM		0xAA

/* Commands */
#define	BMP180_COMMAND_TEMPERATURE 	0x2E
#define	BMP180_COMMAND_PRESSURE_0 	0x34
#define	BMP180_COMMAND_PRESSURE_1 	0x74
#define	BMP180_COMMAND_PRESSURE_2 	0xB4
#define	BMP180_COMMAND_PRESSURE_3 	0xF4

/* Minimum waiting delay, in microseconds */
#define BMP180_TEMPERATURE_DELAY	4500
#define BMP180_PRESSURE_0_DELAY		4500
#define BMP180_PRESSURE_1_DELAY		7500
#define BMP180_PRESSURE_2_DELAY		13000
#define BMP180_PRESSURE_3_DELAY		25000



/**
 * @brief  BMP180 result enumerations
 */
typedef enum {
	BMP180_Result_Ok = 0x00,            /*!< Everything OK */
	BMP180_Result_DeviceNotConnected,   /*!< Device is not connected to I2C */
	BMP180_Result_LibraryNotInitialized /*!< Library is not initialized */
} BMP180_Result_t;


/**
* @brief  Options for oversampling settings
* @note   This settings differs in samples for one result
*         and sample time for one result
*/
typedef enum {
	BMP180_Oversampling_UltraLowPower = 0x00,      /*!< 1 sample for result */
	BMP180_Oversampling_Standard = 0x01,           /*!< 2 samples for result */
	BMP180_Oversampling_HighResolution = 0x02,     /*!< 3 samples for result */
	BMP180_Oversampling_UltraHighResolution = 0x03 /*!< 4 samples for result */
} BMP180_Oversampling_t;

/**
 * @brief  BMP180 main structure
 */
typedef struct {
	float Altitude;                        /*!< Calculated altitude at given read pressure */
	uint32_t Pressure;                     /*!< Pressure in pascals */
	float Temperature;                     /*!< Temperature in degrees */
	uint16_t Delay;                        /*!< Number of microseconds, that sensor needs to calculate data that you request to */
	BMP180_Oversampling_t Oversampling; /*!< Oversampling for pressure calculation */
} BMP180_t;


//Fonction de démo...
void pression_mesure(void);

/**
 * @brief  Initializes BMP180 pressure sensor
 * @param  *BMP180_Data: Pointer to @ref BMP180_t structure
 * @retval Member of @ref BMP180_Result_t
 */
BMP180_Result_t BMP180_Init(BMP180_t* BMP180_Data);


#endif /* PRESSIONTEMP_H_ */
