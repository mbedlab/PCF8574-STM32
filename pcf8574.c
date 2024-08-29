/*
 * pcf8574.c
 *
 *  Created on: Aug 26, 2024
 *      Author: Alixahedi
 */
#include "pcf8574.h"
#include "pcf8574_config.h"
#include "i2c.h"

uint8_t  PCF_read8()
{
    uint8_t value;
    HAL_I2C_Master_Receive(&_PCF8574_I2C, _PCF8574_SLAVE_READ_ADDRESS, &value, 1, 100);
     return value;
}

void PCF_write8(uint8_t value)
{
    HAL_I2C_Master_Transmit(&_PCF8574_I2C, _PCF8574_SLAVE_WRITE_ADDRESS, &value, 1, 100);
}

uint8_t  PCF_ReadPin(uint8_t pin)
{
    uint8_t value;
    value = PCF_read8();
    return (value & (1 << pin)) > 0;
}

void PCF_WritePin(uint8_t pin, uint8_t value)
{
    uint8_t readValue;
    readValue = PCF_read8();
      if (value == 0)
      {
          readValue &= ~(1 << pin);
      }
      else
      {
          readValue |= (1 << pin);
      }
      PCF_write8(readValue);
}

void PCF_TogglePin(uint8_t pin)
{
    uint8_t mask = (1 << pin);
    uint8_t readValue = PCF_read8();
    readValue ^= mask;
    PCF_write8(readValue);
}
