# STM32 Thermocouple Temperature Sensing and Display Project

This project utilizes an STM32 microcontroller (specifically the STM32F429ZI) to interface with a MAX31855 thermocouple sensor via SPI and display temperature readings on an LCD using I2C. Additionally, it incorporates a button for user interaction.

## Components Used

- STM32F429ZI microcontroller
- MAX31855 thermocouple sensor
- LCD display with I2C interface
- Push button

## Project Files

- `API_delay.h` and `API_delay.c`: API for delay functions.
- `API_i2c.h`: Header file for I2C API.
- `API_lcd_port.h` and `API_lcd_port.c`: API for LCD port configuration.
- `API_lcd.h` and `API_lcd.c`: API for LCD functions.
- `API_spi.h` and `API_spi.c`: API for SPI communication.
- `API_uart.h` and `API_uart.c`: API for UART communication.
- `main.h` and `main.c`: Main files for project execution.

## Description

The project is programmed in C using the STM32 IDE. The `main.c` file contains the main function of the project, which involves reading temperature data from the MAX31855 sensor, converting it to Celsius and Fahrenheit, and displaying it on the LCD. User interaction is facilitated through a push button, which allows the user to switch between displaying temperature in Celsius and Fahrenheit.

## Connection Details

| Component         | Pin/Connection |
|-------------------|----------------|
| MAX31855          |                |
| GND               | GND            |
| VCC               | 3.3V           |
| DO(DATA OUTPUT)   | PA_6           |
| CS(CHIP SELECT)   | PA_4           |
| CLCK(CLOCK)       | PA_5           |
| LCD               |                |
| GND               | GND            |
| VCC               | 5V             |
| SDA               | PB_9           |
| SCL               | PB_8           |

## Operation

1. Upon startup, the system initializes and displays "PUSH TO START" on the LCD.
2. Pressing the push button switches the display between Celsius and Fahrenheit readings.
3. The system reads temperature data from the MAX31855 sensor, calculates the temperature in the desired unit, and displays it on the LCD.
4. The process repeats, allowing the user to continuously monitor temperature readings.

## Additional Information

- Every time the button is pressed, the status is displayed on the terminal.

