/*
 * API_uart.c
 *
 *  Created on: Apr 16, 2024
 *      Author: jroberto
 */

#include "API_uart.h"

// Static variables for button debounce FSM
static debounceState_t buttonStatus;
static uint8_t counter = 1;
static delay_t debounceDelay;

// State handle for MAX31855 sensor
MAX31855_StateHandle StateHandle;

// Function prototypes
void uartSendString();

// Variables for temperature conversion and display
float tReal;
float Vout;
float tDev;
float Celsius;
float Fahrenheits;
char tempStr[6];
char counterStr[32];
char counterBuffer[5]; // Buffer to hold the counter as string

// Function to switch states based on counter value
void switchingState(uint8_t *counter) {

    switch (*counter) {

        case 1:
            BSP_LED_On(LED1);
            BSP_LED_Off(LED2);
            BSP_LED_Off(LED3);
            LCD_POS_CHAR_H(0);
            LCD_Print((uint8_t *)"PUSH TO START");
            break;

        case 2:
            LCD_Clear();
            BSP_LED_Off(LED1);
            BSP_LED_On(LED2);
            BSP_LED_Off(LED3);
            // Read data from MAX31855 sensor
            MAX31855_ReadData(&StateHandle);
            if (!MAX31855_GetStatus(&StateHandle)) {
                // Get temperature values
                tReal = MAX31855_GetExternalTemperature(&StateHandle);
                tDev = MAX31855_GetInternalTemperature(&StateHandle);
                // Calculate Celsius temperature
                Vout = MAX31855_GetVout(tReal, tDev);
                Celsius = MAX31855_GetMAX31855Temp(Vout, tDev);
                // Convert Celsius to string and display
                snprintf(tempStr, sizeof(tempStr), "%.2f", Celsius);
                LCD_POS_CHAR_H(0);
                LCD_Print((uint8_t *)"Temperature");
                LCD_POS_CHAR_L(0);
                LCD_Print((uint8_t *)"Celsius: ");
                LCD_Print((uint8_t *)tempStr);
                HAL_Delay(1000);
            }
            break;

        case 3:
            LCD_Clear();
            BSP_LED_Off(LED1);
            BSP_LED_Off(LED2);
            BSP_LED_On(LED3);
            // Read data from MAX31855 sensor
            MAX31855_ReadData(&StateHandle);
            if (!MAX31855_GetStatus(&StateHandle)) {
                // Get temperature values
                tReal = MAX31855_GetExternalTemperature(&StateHandle);
                tDev = MAX31855_GetInternalTemperature(&StateHandle);
                // Calculate Celsius temperature
                Vout = MAX31855_GetVout(tReal, tDev);
                Celsius = MAX31855_GetMAX31855Temp(Vout, tDev);
                // Convert Celsius to Fahrenheit and string, then display
                Fahrenheits = MAX31855_CelsiusToFahrenheit(Celsius);
                snprintf(tempStr, sizeof(tempStr), "%.2f", Fahrenheits);
                LCD_POS_CHAR_H(0);
                LCD_Print((uint8_t *)"Temperature");
                LCD_POS_CHAR_L(0);
                LCD_Print((uint8_t *)"Fahrenheit: ");
                LCD_Print((uint8_t *)tempStr);
                HAL_Delay(1000);
            }
            break;

        default:
            LCD_Clear();
            *counter = 1;
            break;
    }
}

// Initialize debounce FSM
void debounceFSM_init(void){
    buttonStatus = BUTTON_UP;
    counter = 1;
}

// Update debounce FSM
void debounceFSM_update(void) {
    delayInit(&debounceDelay, 40);

    switch (buttonStatus) {
        case BUTTON_UP:
            if (BSP_PB_GetState(BUTTON_USER)) {
                buttonStatus = BUTTON_FALLING;
            }
            switchingState(&counter);
            break;

        case BUTTON_FALLING:
            delayRead(&debounceDelay);
            if (BSP_PB_GetState(BUTTON_USER)) {
                buttonStatus = BUTTON_DOWN;
                counter++; // Increment the value of counter
                snprintf(counterBuffer, sizeof(counterBuffer), "%d", counter); // Convert counter to string
                uartSendString((uint8_t*)("Button pressed. Switching status: "));
                uartSendString((uint8_t*)counterBuffer); // Send counter value
                uartSendString((uint8_t*)("\n\r"));
                switchingState(&counter);
            } else {
                buttonStatus = BUTTON_UP;
            }
            break;

        case BUTTON_DOWN:
            if (!BSP_PB_GetState(BUTTON_USER)) {
                buttonStatus = BUTTON_RAISING;
            }
            break;

        case BUTTON_RAISING:
            delayRead(&debounceDelay);
            if (!BSP_PB_GetState(BUTTON_USER)) {
                buttonStatus = BUTTON_UP;
            } else {
                buttonStatus = BUTTON_DOWN;
            }
            break;
    }
}

// Send string over UART
void uartSendString(uint8_t * pstring) {
    HAL_UART_Transmit(&huart, pstring, strlen((char*)pstring), HAL_MAX_DELAY);
}

// Send string over UART with specified size
void uartSendStringSize(uint8_t * pstring, uint16_t size) {
    HAL_UART_Transmit(&huart, pstring, size, HAL_MAX_DELAY);
}

// Receive string over UART with specified size (currently empty function)
void uartReceiveStringSize(uint8_t * pstring, uint16_t size) {
}
