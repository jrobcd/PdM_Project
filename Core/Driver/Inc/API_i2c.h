/*
 * API_i2c.h
 *
 *  Created on: Apr 16, 2024
 *      Author: jroberto
 */

#ifndef DRIVER_INC_API_I2C_H_
#define DRIVER_INC_API_I2C_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include <stdbool.h>

#define I2C_CLOCK_RATE 100000


_Bool I2C_HW_init(void);

#endif /* DRIVER_INC_API_I2C_H_ */
