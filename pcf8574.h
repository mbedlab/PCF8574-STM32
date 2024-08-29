/*
 * pcf8574.h
 *
 *  Created on: Aug 26, 2024
 *      Author: Alixahedi
 */

#ifndef INC_PCF8574_H_
#define INC_PCF8574_H_

#include "main.h"

uint8_t  PCF_ReadPin(uint8_t pin);
void PCF_WritePin(uint8_t pin, uint8_t value);
void PCF_TogglePin(uint8_t pin);

#endif /* INC_PCF8574_H_ */
