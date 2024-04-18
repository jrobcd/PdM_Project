/*
 * API_spi.c
 *
 *  Created on: Apr 13, 2024
 *      Author: jroberto
 */

#include "stm32f4xx_hal.h"
#include "API_spi.h"

#define K_TYPE_CONST 41.276

// Initialize MAX31855 sensor
void MAX31855_Init(MAX31855_StateHandle *MAX31855, SPI_HandleTypeDef * hspi) {
    // Assign SPI handle
    MAX31855->hspi = hspi;
    // Configure chip select pin
    MAX31855->nss.pin = SPI_CS_PIN;
    MAX31855->nss.port = SPI_CS_GPIO_PORT;
    // Set initial NSS state
    MAX31855_SetNSSState(MAX31855, GPIO_PIN_SET);
}

// Get the status of the MAX31855 sensor
uint8_t MAX31855_GetStatus(MAX31855_StateHandle *MAX31855) {
    // Check for various faults
    if(MAX31855->ocFault)
    {
        return 1; // Open circuit fault
    }
    else if(MAX31855->scgFault)
    {
        return 2; // Short to ground fault
    }
    else if(MAX31855->scvFault)
    {
        return 3; // Short to Vcc fault
    }
    else
    {
        return 0; // No fault
    }
}

// Convert external temperature read from MAX31855 to Celsius
float MAX31855_GetExternalTemperature(MAX31855_StateHandle *MAX31855) {
    return MAX31855->extTemp * 0.25;
}

// Convert internal temperature read from MAX31855 to Celsius
float MAX31855_GetInternalTemperature(MAX31855_StateHandle *MAX31855){
    return MAX31855->intTemp * 0.0625;
}

// Convert Celsius temperature to Fahrenheit
float MAX31855_CelsiusToFahrenheit(float celsius) {
    float fahrenheit = celsius * (9.0 / 5.0) + 32.0;
    return fahrenheit;
}

// Read data from MAX31855 sensor
/*
 * MAX31855_ReadData function reads data from the MAX31855 temperature sensor
 * and processes it to update the state variables accordingly.
 *
 * Parameters:
 *   MAX31855: Pointer to the MAX31855 state.
 *
 * Description:
 *   This function initiates the SPI communication with the MAX31855 sensor,
 *   receives the data payload, and updates the state variables based on the
 *   received data. It also handles the fault indicators and temperature readings.
 *   The received data is processed to extract the fault flags and temperature
 *   readings for both internal and external temperatures.
 */
void MAX31855_ReadData(MAX31855_StateHandle *MAX31855){

    uint8_t payload[4];  // Array to store the received data payload
    int32_t frame;        // Variable to reconstruct the 32-bit frame from the payload

    // Select MAX31855 by pulling NSS pin low
    MAX31855_SetNSSState(MAX31855, GPIO_PIN_RESET);

    // Receive data payload from the MAX31855 sensor
    HAL_SPI_Receive(MAX31855->hspi, payload, 4, 1000);

    // Deselect MAX31855 by pulling NSS pin high
    MAX31855_SetNSSState(MAX31855, GPIO_PIN_SET);

    // Reset fault indicators and temperature readings
    MAX31855->scvFault = 0;
    MAX31855->scgFault = 0;
    MAX31855->ocFault = 0;
    MAX31855->fault = 0;
    MAX31855->extTemp = 0;
    MAX31855->extTempSign = 0;
    MAX31855->intTemp = 0;
    MAX31855->intTempSign = 0;

    // Reconstruct 32-bit frame from the received payload
    frame = payload[0];
    frame = frame << 8;
    frame = frame | payload[1];
    frame = frame << 8;
    frame = frame | payload[2];
    frame = frame << 8;
    frame = frame | payload[3];

    // Extract internal and external temperatures and fault flags from the frame
    int32_t extTemp = frame; // External temperature
    int32_t intTemp = frame; // Internal temperature

    // Check fault flags and update the corresponding state variables
    if(frame & 0b00000000000000000000000000000100)
    {
        MAX31855->scvFault = 1;
    }
    if(frame & 0b00000000000000000000000000000010)
    {
        MAX31855->scgFault = 1;
    }
    if(frame & 0b00000000000000000000000000000001)
    {
        MAX31855->ocFault = 1;
    }
    if(frame & 0b00000000000000010000000000000000)
    {
        MAX31855->fault = 1;
    }
    if(frame & 0b10000000000000000000000000000000)
    {
        MAX31855->extTempSign = 1;
    }
    if(frame & 0b00000000000000010000000000000000)
    {
        MAX31855->intTempSign = 1;
    }

    // Process external temperature data
    extTemp >>= 18;
    if (MAX31855->intTempSign) {
        extTemp = ~(extTemp & 0b11111111111111);
    }
    MAX31855->extTemp = extTemp;

    // Process internal temperature data
    intTemp = ((intTemp >> 4) & 0b11111111111);
    if (MAX31855->intTempSign)
    {
        intTemp =~(intTemp | 0b1111100000000000); // Experimental code, not tested!
    }
    MAX31855->intTemp = intTemp;
}


// Set the chip select state of MAX31855
void MAX31855_SetNSSState(MAX31855_StateHandle *MAX31855, GPIO_PinState state) {
    HAL_GPIO_WritePin(MAX31855->nss.port, MAX31855->nss.pin, state);
}

// Calculate Vout from real temperature and cold junction temperature
float MAX31855_GetVout(float tReal, float tDev) {
    float Vout = K_TYPE_CONST * (tReal - tDev);
    return Vout;
}

// Calculate MAX31855 temperature from Vout and cold junction temperature
float MAX31855_GetMAX31855Temp(float Vout, float tDev) {
    float Celsius = -1 * ((Vout) / (K_TYPE_CONST + tDev));
    return Celsius;
}
