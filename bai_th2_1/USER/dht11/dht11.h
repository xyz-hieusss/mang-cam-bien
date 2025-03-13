#ifndef _dht11_h_
#define _dht11_h_

#include "stm32f10x.h"

static uint16_t u16Tim;
static uint8_t u8Buff[5];
static uint8_t u8CheckSum;
static uint8_t i;

void DHT11(void);
void send(uint8_t u8Data);
void ReadData(void);

#endif
