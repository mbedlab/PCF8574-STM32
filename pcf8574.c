/*
 * pcf8574.c
 *
 *  Created on: Aug 26, 2024
 *      Author: Alixahedi
 */

#include "pcf8574.h"


void PCF8574_Init(PCF8574_HandleTypeDef *pcf8574, I2C_HandleTypeDef *hi2c, uint8_t a0, uint8_t a1, uint8_t a2) {
    pcf8574->hi2c = hi2c;
    pcf8574->address = PCF8574_ADDRESS_BASE | (a0 << 1) | (a1 << 2) | (a2 << 3);
    pcf8574->portState = 0x00;
    PCF8574_WritePort(pcf8574, pcf8574->portState);
}


void PCF8574_WritePin(PCF8574_HandleTypeDef *pcf8574, uint8_t pin, GPIO_PinState state) {
    if (state == GPIO_PIN_RESET) {
        pcf8574->portState &= ~(1 << pin);
    } else {
        pcf8574->portState |= (1 << pin);
    }
    PCF8574_WritePort(pcf8574, pcf8574->portState);
}


GPIO_PinState PCF8574_ReadPin(PCF8574_HandleTypeDef *pcf8574, uint8_t pin) {
    PCF8574_ReadPort(pcf8574);
    return (pcf8574->portState & (1 << pin)) ? GPIO_PIN_SET : GPIO_PIN_RESET;
}


void PCF8574_TogglePin(PCF8574_HandleTypeDef *pcf8574, uint8_t pin) {
    pcf8574->portState ^= (1 << pin);
    PCF8574_WritePort(pcf8574, pcf8574->portState);
}

// نوشتن وضعیت کلی پورت به PCF8574
void PCF8574_WritePort(PCF8574_HandleTypeDef *pcf8574, uint8_t value) {
	pcf8574->portState = value;
    HAL_I2C_Master_Transmit(pcf8574->hi2c, pcf8574->address, &(pcf8574->portState), 1, HAL_MAX_DELAY);
}

// خواندن وضعیت کلی پورت از PCF8574
uint8_t PCF8574_ReadPort(PCF8574_HandleTypeDef *pcf8574) {
    HAL_I2C_Master_Receive(pcf8574->hi2c, pcf8574->address, &(pcf8574->portState), 1, HAL_MAX_DELAY);
    return pcf8574->portState;
}
