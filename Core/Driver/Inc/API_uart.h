/*
 * API_uart.h
 *
 *  Created on: Apr 16, 2024
 *      Author: jroberto
 */

#ifndef DRIVER_INC_API_UART_H_
#define DRIVER_INC_API_UART_H_

#include "API_delay.h"
#include "API_lcd.h"
#include "API_spi.h"
#include "stm32f4xx_hal.h"
#include <string.h>

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;

extern UART_HandleTypeDef huart;

void updateState();
void debounceFSM_init();
void debounceFSM_update();
void buttonPressed();
void buttonReleased();

bool_t readKey();

#endif /* DRIVER_INC_API_UART_H_ */
