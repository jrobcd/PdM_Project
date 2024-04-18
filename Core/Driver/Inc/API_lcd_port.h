/*
 * API_i2c_port.h
 *
 *  Created on: Apr 16, 2024
 *      Author: jroberto
 */

#ifndef DRIVER_INC_API_LCD_PORT_H_
#define DRIVER_INC_API_LCD_PORT_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include <stdbool.h>
#include "API_lcd.h"

extern void Error_Handler(void);

_Bool LCD_HW_init(void);
void LCD_Write_Byte(uint8_t valor);
void GPIO_I2C(I2C_HandleTypeDef  *hi2c);

#endif /* DRIVER_INC_API_LCD_PORT_H_ */
