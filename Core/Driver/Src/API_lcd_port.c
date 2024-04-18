/*
 * API_i2c.c
 *
 *  Created on: Apr 16, 2024
 *      Author: jroberto
 */

#include"API_i2c.h"
#include "API_lcd.h"

// Include necessary header files

// External declaration of the I2C handle
extern I2C_HandleTypeDef hi2c1;

// Function to write a byte to the LCD via I2C
void LCD_Write_Byte(uint8_t valor){
    // Transmit the byte via I2C
	if(HAL_I2C_Master_Transmit (&hi2c1, LCD_DIR << 1, &valor, sizeof(valor), HAL_MAX_DELAY) != HAL_OK)
        Error_Handler(); // Handle transmission error if any
}
