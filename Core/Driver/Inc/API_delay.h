/*
 * API_delay.h
 *
 *  Created on: Apr 17, 2024
 *      Author: jroberto
 */

#ifndef DRIVER_INC_API_DELAY_H_
#define DRIVER_INC_API_DELAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"

#include <stdbool.h>

typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

void Error_Handler(void);
void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );

#ifdef __cplusplus
}
#endif

#endif /* DRIVER_INC_API_DELAY_H_ */
