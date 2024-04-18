/*
 * API_spi.h
 *
 *  Created on: Apr 13, 2024
 *      Author: jroberto
 */

#ifndef DRIVER_INC_API_SPI_H_
#define DRIVER_INC_API_SPI_H_
#define SPI_CS_PIN GPIO_PIN_4
#define SPI_CS_GPIO_PORT GPIOA

typedef struct {
	uint16_t pin;
	GPIO_TypeDef *port;
} MAX31855_GPIO;

typedef struct {
	MAX31855_GPIO nss;
	SPI_HandleTypeDef *hspi;
	uint8_t fault;
	uint8_t ocFault;
	uint8_t scgFault;
	uint8_t scvFault;
	int32_t intTemp;
	uint8_t intTempSign;
	int32_t extTemp;
	uint8_t extTempSign;
} MAX31855_StateHandle;

extern MAX31855_StateHandle MAX31855_Handle;

void MAX31855_Init(MAX31855_StateHandle *MAX31855, SPI_HandleTypeDef * hspi);
uint8_t MAX31855_GetStatus(MAX31855_StateHandle *MAX31855);
float MAX31855_GetExternalTemperature(MAX31855_StateHandle *MAX31855);
float MAX31855_GetInternalTemperature(MAX31855_StateHandle *MAX31855);
void MAX31855_ReadData(MAX31855_StateHandle *MAX31855);
void MAX31855_SetNSSState(MAX31855_StateHandle *MAX31855, GPIO_PinState state);
float MAX31855_GetExternalTemperatureInFahrenheit(MAX31855_StateHandle *MAX31855);
float MAX31855_GetInternalTemperatureInFahrenheit(MAX31855_StateHandle *MAX31855);
float MAX31855_GetVout(float tReal, float tDev);
float MAX31855_GetMAX31855Temp(float Vout, float tDev);
float MAX31855_CelsiusToFahrenheit(float celsius);

#endif /* DRIVER_INC_API_SPI_H_ */
