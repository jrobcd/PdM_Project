/*
 * API_delay.c
 *
 *  Created on: Apr 17, 2024
 *      Author: jroberto
 */

#include "API_delay.h"
#include <stdlib.h>

#define DEFAULT_DELAY 10

// Initialize a delay object with a given duration
void delayInit(delay_t *delay, tick_t duration){
    // If duration is non-positive, set it to default value
	if (duration <= 0){
		duration = DEFAULT_DELAY;
	}
	delay->duration = duration;
	delay->running = false;
	delay->startTime = 0;
}

// Check if the delay has elapsed
bool_t delayRead(delay_t *delay){
    // Get the current time
	tick_t currentTime = HAL_GetTick();
	bool isRunning = delay->running;

    // If the delay is running and the elapsed time is greater than or equal to the duration, stop the delay and return true
	if (isRunning && (currentTime - delay->startTime >= delay->duration)){
		delay->running = false;
		return true;
	}

    // If the delay is not running, start it and update the start time
	if (!isRunning) {
		delay->running = true;
		delay->startTime = currentTime;
	}
	return false;
}
