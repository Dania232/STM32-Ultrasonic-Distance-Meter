#include "MyLCDcode.h"

#define LCD_DELAY_MS(ms) HAL_Delay(ms)

static void MyLCDcode_WriteNibble(uint8_t nibble, uint8_t rs) {
    HAL_GPIO_WritePin(DISP_RS_GPIO_Port, DISP_RS_Pin, rs ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DISP_RW_GPIO_Port, DISP_RW_Pin, GPIO_PIN_RESET); // RW = 0 (write)
    
    HAL_GPIO_WritePin(DISP_DB4_GPIO_Port, DISP_DB4_Pin, (nibble & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DISP_DB5_GPIO_Port, DISP_DB5_Pin, (nibble & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DISP_DB6_GPIO_Port, DISP_DB6_Pin, (nibble & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DISP_DB7_GPIO_Port, DISP_DB7_Pin, (nibble & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    
    HAL_GPIO_WritePin(DISP_ENA_GPIO_Port, DISP_ENA_Pin, GPIO_PIN_SET);
    LCD_DELAY_MS(1);
    HAL_GPIO_WritePin(DISP_ENA_GPIO_Port, DISP_ENA_Pin, GPIO_PIN_RESET);
    LCD_DELAY_MS(1);
}

static void MyLCDcode_Send(uint8_t value, uint8_t rs) {
    MyLCDcode_WriteNibble(value >> 4, rs); 
    MyLCDcode_WriteNibble(value & 0x0F, rs); 
}

void MyLCDcode_Init(void) {
    LCD_DELAY_MS(40); 
    
    MyLCDcode_WriteNibble(0x03, 0); 
    LCD_DELAY_MS(5);
    MyLCDcode_WriteNibble(0x03, 0); 
    LCD_DELAY_MS(5);
    MyLCDcode_WriteNibble(0x03, 0); 
    LCD_DELAY_MS(1);
    MyLCDcode_WriteNibble(0x02, 0); 

    MyLCDcode_SendCommand(0x28); 
    MyLCDcode_SendCommand(0x0C); 
    MyLCDcode_SendCommand(0x06); 
    MyLCDcode_SendCommand(0x01); 
    LCD_DELAY_MS(2);
}

void MyLCDcode_SendCommand(uint8_t cmd) {
    MyLCDcode_Send(cmd, 0);
}

void MyLCDcode_SendData(uint8_t data) {
    MyLCDcode_Send(data, 1);
}

void MyLCDcode_Print(const char *str) {
    while (*str) {
        MyLCDcode_SendData(*str++);
    }
}

void MyLCDcode_SetCursor(uint8_t row, uint8_t col) {
    uint8_t address = (row == 0) ? col : col + 0x40;
    MyLCDcode_SendCommand(0x80 | address);
}