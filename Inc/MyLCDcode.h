#ifndef MYLCDCODE_H
#define MYLCDCODE_H

#include "gpio.h"
#include "stm32f4xx_hal.h"

void MyLCDcode_Init(void);
void MyLCDcode_SendCommand(uint8_t cmd);
void MyLCDcode_SendData(uint8_t data);
void MyLCDcode_Print(const char *str);
void MyLCDcode_SetCursor(uint8_t row, uint8_t col);

#endif