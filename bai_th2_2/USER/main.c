#include "defines.h"

//#define BH1750_ADDR  0x46 // Ð?a ch? I2C c?a BH1750 (Ch? d? m?c d?nh)
//#define BH1750_POWER_ON  0x01
//#define BH1750_RESET     0x07
//#define BH1750_ONE_H_MODE  0x10

//#define I2C_TIMEOUT 10000
uint32_t ticks;

void UART1_Init(void);
void UART1_SendChar(char c);
void UART1_SendString(char *str);
void I2C1_config(void);
void I2C1_write(uint8_t HW_address, uint8_t sub, uint8_t data);
void I2C1_read_buf(uint8_t HW_address, uint8_t sub, uint8_t *p_buf, uint8_t buf_size);
void BH1750_Init (void);
float BH1750_Readlux(void);

void I2C1_config()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    I2C_InitTypeDef I2C_InitStructure;
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOB, &GPIO_InitStructure); // S?a GPIO -> GPIOB
    
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 100000;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_OwnAddress1 = 0x0B;
    
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);
}

void I2C1_write(uint8_t HW_address, uint8_t sub, uint8_t data)
{
    
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) && ticks) {ticks --;}
		if(ticks == 0) return;
			ticks = I2C_TIMEOUT;
			
    I2C_Send7bitAddress(I2C1, HW_address, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) && ticks) {ticks--;}
		if (ticks == 0) return;
			ticks = I2C_TIMEOUT;
			
    if (sub != 0xFF)
    {
        I2C_SendData(I2C1, sub);
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) && ticks) {ticks--;}
				if(ticks ==0) return;
					ticks= I2C_TIMEOUT;
					
    }

    I2C_SendData(I2C1, data);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) && ticks) {ticks--;}
		if(ticks==0) return;
			ticks = I2C_TIMEOUT;
		
    I2C_GenerateSTOP(I2C1, ENABLE);
		
		while((I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)) && ticks) {ticks--;}
		if (ticks == 0) return;
		 ticks = I2C_TIMEOUT;
}

void I2C1_read_buf(uint8_t HW_address, uint8_t sub, uint8_t *p_buf, uint8_t buf_size)
{
   
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) && ticks) {ticks--;}

    I2C_Send7bitAddress(I2C1, HW_address, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) && ticks) {ticks--;}

    if (sub != 0xFF)
    {
        I2C_SendData(I2C1, sub);
        while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));
    }

    I2C_GenerateSTART(I2C1, ENABLE);
    while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)));

    I2C_Send7bitAddress(I2C1, HW_address, I2C_Direction_Receiver);
    while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)));

    for(uint8_t i = 0; i < buf_size; i++)
    {
        while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)));
        p_buf[i] = I2C_ReceiveData(I2C1);
    }
		I2C_AcknowledgeConfig(I2C1,DISABLE);
		I2C_NACKPositionConfig(I2C1,I2C_NACKPosition_Current);
		
    I2C_GenerateSTOP(I2C1, ENABLE);
		while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
}

void BH1750_Init (void)
{
	I2C1_write(BH1750_ADDR, 0xFF, BH1750_POWER_ON);
}


float BH1750_ReadLux(void)
{
    uint8_t tmp8[2];
    I2C1_read_buf(BH1750_ADDR, BH1750_ONE_H_MODE, tmp8, 2);
    return (float)((tmp8[0] << 8) | tmp8[1]) / 1.2;
}

void UART1_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 9600;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStruct);
    USART_Cmd(USART1, ENABLE);
}

void UART1_SendChar(char c)
{
    while (!(USART1->SR & USART_SR_TXE)) {}
    USART1->DR = c;
}

void UART1_SendString(char *str)
{
    while (*str)
    {
        UART1_SendChar(*str++);
    }
}

int main(void)
{
    I2C1_config();
    UART1_Init();
		BH1750_Init();
    while (1)
    {
        float lux = BH1750_ReadLux();
        char buffer[20];
        sprintf(buffer, "Lux: %.2f\r\n", lux);
        UART1_SendString(buffer);
			
        for (volatile uint32_t i = 0; i < 2000000; i++);
    }
}
