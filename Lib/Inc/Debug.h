#ifndef IMU_H
#define IMU_H
#include "main.h"

extern uint8_t sofa_data[15];
void UART_Printf(UART_HandleTypeDef *huart,const char *format, ...);
//void UART_Printf(const char *format, ...);
float parse_float_from_uart(const uint8_t* data, uint16_t length);
#endif
