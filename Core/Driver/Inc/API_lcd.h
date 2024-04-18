/*
 * API_lcd.h
 *
 *  Created on: Apr 16, 2024
 *      Author: jroberto
 */

#ifndef DRIVER_INC_API_LCD_H_
#define DRIVER_INC_API_LCD_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include <stdbool.h>

#define DATOS 1
#define CONTROL 0

#define LCD_DIR 39

typedef enum
{
  LCD_OK       = 0,
  LCD_ERROR    = 1,
} LCD_Status_t;

#define EN (1<<2)
#define BL (1<<3)

#define CLR_LCD 1
#define RETURN_HOME (1<<1)
#define ENTRY_MODE (1<<2)
#define DISPLAY_CONTROL (1<<3)
#define CURSOR_DISPLAY_SHIFT (1<<4)
#define FUNTION_SET (1<<5)
#define SET_CGRAM (1<<6)
#define SET_DDRAM (1<<7)

#define DISPLAY_ON (1<<2)
#define CURSOR_ON (1<<1)
#define CURSOR_BLINK 1
#define AUTOINCREMENT (1<<1)
#define _4BIT_MODE 40

#define HIGH_NIBBLE 240
#define LOW_NIBBLE 4

#define FirstRow 128
#define SecondRow 192

#define COMANDO_INI1 48
#define COMANDO_INI2 32

_Bool LCD_Init(void);
void LCD_Print (uint8_t *texto);
void LCD_Data (uint8_t dato);
void LCD_ASCII_Data (uint8_t dato);
void LCD_BSD_Data (uint8_t dato);
void LCD_Clear(void);
void LCD_POS_CHAR_H(uint8_t posH);
void LCD_POS_CHAR_L(uint8_t posL);
void LCD_CursorOFF(void);
void LCD_CursorOn(void);

#endif /* DRIVER_INC_API_LCD_H_ */
