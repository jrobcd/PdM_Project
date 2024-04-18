/*
 * API_lcd.c
 *
 *  Created on: Apr 16, 2024
 *      Author: jroberto
 */

#include "API_lcd.h"
#include "API_i2c.h"

// Static function declarations
static void LCD_Delay(uint32_t lcdDelay);
static void LCD_Control(uint8_t value);
static void LCD_8bits(uint8_t value, _Bool type);
static void LCD_4bits(uint8_t value, _Bool type);

// Initial LCD commands
static const uint8_t LCD_INIT_CMD[] = {
    _4BIT_MODE, DISPLAY_CONTROL, RETURN_HOME, ENTRY_MODE + AUTOINCREMENT, DISPLAY_CONTROL + DISPLAY_ON, CLR_LCD
};

// Initialize the LCD
_Bool LCD_Init(void){

    LCD_Delay(20); // Initial delay
    LCD_4bits(COMANDO_INI1, CONTROL); // Initialize LCD in 4-bit mode
    LCD_Delay(10); // Delay
    LCD_4bits(COMANDO_INI1, CONTROL); // Initialize LCD in 4-bit mode
    LCD_Delay(1); // Delay
    LCD_4bits(COMANDO_INI1, CONTROL); // Initialize LCD in 4-bit mode
    LCD_4bits(COMANDO_INI2, CONTROL); // Initialize LCD in 4-bit mode
    // Send initialization commands to the LCD
    for (uint8_t i = 0; i < sizeof(LCD_INIT_CMD); i++)
        LCD_Control(LCD_INIT_CMD[i]);
    LCD_Delay(2); // Delay
    return LCD_OK; // Return status
}

// Static function for delay
static void LCD_Delay(uint32_t lcdDelay) {
    HAL_Delay(lcdDelay);
}

// Static function to send control commands to the LCD
static void LCD_Control(uint8_t value) {
    LCD_8bits(value, CONTROL);
}

// Function to send data to the LCD
void LCD_Data(uint8_t data) {
    LCD_8bits(data, DATOS);
}

// Function to send ASCII data to the LCD
void LCD_ASCII_Data(uint8_t data) {
    LCD_8bits(data + '0', DATOS);
}

// Function to send data in BSD format to the LCD
void LCD_BSD_Data(uint8_t data){

    LCD_ASCII_Data((((data) & 0xf0) >> 4)); // Send upper 4 bits
    LCD_ASCII_Data(((data) & 0x0f)); // Send lower 4 bits
}

// Function to send 8 bits to the LCD
void LCD_8bits(uint8_t value, _Bool type) {
    LCD_4bits(value & HIGH_NIBBLE, type); // Send higher 4 bits
    LCD_4bits(value << LOW_NIBBLE, type); // Send lower 4 bits
}

// Static function to send 4 bits to the LCD
static void LCD_4bits(uint8_t value, _Bool type) {

    LCD_Write_Byte(value + type + EN + BL); // Send data with control bits
    LCD_Delay(1); // Delay
    LCD_Write_Byte(value + type + BL); // Send data with control bits
    LCD_Delay(1); // Delay
}

// Function to print a string to the LCD
void LCD_Print(uint8_t *text) {
    while (*text)
        LCD_Data(*text++); // Send each character to the LCD
}

// Function to clear the LCD
void LCD_Clear(void) {
    LCD_Control(CLR_LCD); // Send clear command
    LCD_Delay(2); // Delay
}

// Function to set the cursor position to the upper row
void LCD_POS_CHAR_H(uint8_t posH) {
    LCD_Control(posH | FirstRow); // Set cursor position to upper row
}

// Function to set the cursor position to the lower row
void LCD_POS_CHAR_L(uint8_t posL) {
    LCD_Control(posL | SecondRow); // Set cursor position to lower row
}

// Function to turn off the cursor
void LCD_CursorOFF(void) {
    LCD_Control(DISPLAY_CONTROL + DISPLAY_ON); // Turn off cursor
}

// Function to turn on the cursor
void LCD_CursorOn(void) {
    LCD_Control(DISPLAY_CONTROL + CURSOR_ON + DISPLAY_ON + CURSOR_BLINK); // Turn on cursor
}
