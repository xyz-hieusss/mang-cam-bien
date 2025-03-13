#ifndef USART1_H
#define USART1_H

#include "stm32f10x.h"
#include <stdio.h>

void USART1_Init(uint32_t baudrate);
void USART1_SendChar(char c);
void USART1_SendString(char *str);
void USART1_SendNumber(uint8_t num);

#endif