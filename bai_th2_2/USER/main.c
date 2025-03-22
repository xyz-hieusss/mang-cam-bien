#include "stm32f10x.h"          // Thu vi?n cho STM32F103
#include "stm32f10x_i2c.h"      // Thu vi?n cho I2C
#include "stm32f10x_gpio.h"     // Thu vi?n cho GPIO
#include "stm32f10x_rcc.h"      // Thu vi?n cho RCC
#include "stm32f10x_usart.h"    // Thu vi?n cho USART
#include "stdio.h"

#define BH1750_ADDRESS (0x23 << 1) // Ð?a ch? c?a BH1750 (7-bit d?a ch?)

// Khai báo các hàm I2C
void I2C_Start(I2C_TypeDef* I2Cx);
void I2C_Stop(I2C_TypeDef* I2Cx);
void I2C_SendDeviceAddress(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction);
void I2C_SendByte(I2C_TypeDef* I2Cx, uint8_t data);
uint8_t I2C_ReceiveByte(I2C_TypeDef* I2Cx);

// C?u hình I2C
void I2C_Config(void) {
    // Kích ho?t clock cho I2C1
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    // Kích ho?t clock cho GPIOB
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // C?u hình chân PB6 (SCL) và PB7 (SDA)
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; // Open Drain
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // C?u hình I2C
    I2C_InitTypeDef I2C_InitStruct;
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;																			//che do giao tiep I2C chuan
    I2C_InitStruct.I2C_ClockSpeed = 100000; // 100 kHz	
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;															// chu ky tin hieu la 50%
    I2C_InitStruct.I2C_OwnAddress1 = 0x00; 																			// tbi nay dong vai tro la master					
    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;																		//cho phep ACK xac nhan sau moi byte dc truyen hoac nhan
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

    // G?i hàm kh?i t?o I2C
    I2C_Init(I2C1, &I2C_InitStruct);
    I2C_Cmd(I2C1, ENABLE); // B?t I2C1
}

// C?u hình USART
void USART_Config(void) {
    // Kích ho?t clock cho USART1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // Kích ho?t clock cho GPIOA

    // C?u hình chân PA9 (TX) và PA10 (RX)
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // Alternate Function Push-Pull
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // C?u hình USART
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 9600; // T?c d? baud
    USART_InitStruct.USART_WordLength = USART_WordLength_8b; // 8 bit
    USART_InitStruct.USART_StopBits = USART_StopBits_1; // 1 stop bit
    USART_InitStruct.USART_Parity = USART_Parity_No; // Không có parity
    USART_InitStruct.USART_Mode = USART_Mode_Tx; // Ch? truy?n
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // Không ki?m soát dòng

    // G?i hàm kh?i t?o USART
    USART_Init(USART1, &USART_InitStruct);
    USART_Cmd(USART1, ENABLE); // B?t USART1
}

// G?i ký t? qua UART
void USART_SendChar(char c) {
    while (!(USART1->SR & USART_SR_TXE)); // Ch? cho d?n khi TXE (Transmit Data Register Empty) = 1
    USART_SendData(USART1, c); // G?i ký t?
}

// G?i chu?i qua UART
void USART_SendString(char* str) {
    while (*str) {
        USART_SendChar(*str++);
    }
}

// G?i tín hi?u b?t d?u giao ti?p I2C
void I2C_Start(I2C_TypeDef* I2Cx) {
    I2Cx->CR1 |= I2C_CR1_START; // G?i tín hi?u START
    while (!(I2Cx->SR1 & I2C_SR1_SB)); // Ch? cho d?n khi SB (Start Bit) = 1
}

// G?i d?a ch? I2C
void I2C_SendDeviceAddress(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction) {
    if (direction == 0) { // Transmitter
        address &= ~0x01; // Clear LSB for write
    } else { // Receiver
        address |= 0x01; // Set LSB for read
    }
    I2Cx->DR = address; // G?i d?a ch?
    while (!(I2Cx->SR1 & I2C_SR1_ADDR)); // Ch? cho d?n khi ADDR (Address Sent) = 1
    (void)I2Cx->SR2; // Ð?c SR2 d? xóa c? ADDR
}

// G?i d? li?u qua I2C
void I2C_SendByte(I2C_TypeDef* I2Cx, uint8_t data) {
    I2Cx->DR = data; // G?i d? li?u
    while (!(I2Cx->SR1 & I2C_SR1_TXE)); // Ch? cho d?n khi TXE = 1
}

// Nh?n d? li?u qua I2C
uint8_t I2C_ReceiveByte(I2C_TypeDef* I2Cx) {
    while (!(I2Cx->SR1 & I2C_SR1_RXNE)); // Ch? cho d?n khi RXNE (Receive Buffer Not Empty) = 1
    return I2Cx->DR; // Tr? v? d? li?u nh?n du?c
}

// G?i tín hi?u STOP
void I2C_Stop(I2C_TypeDef* I2Cx) {
    I2Cx->CR1 |= I2C_CR1_STOP; // G?i tín hi?u STOP
}

// Ð?c giá tr? ánh sáng t? BH1750
uint16_t BH1750_ReadLight(void) {
    uint8_t data[2];
    I2C_Start(I2C1);
    I2C_SendDeviceAddress(I2C1, BH1750_ADDRESS, 0); // G?i d?a ch? trong ch? d? truy?n
    I2C_SendByte(I2C1, 0x10); // G?i l?nh b?t d?u do
    I2C_Stop(I2C1);

    // Ch? 180ms d? do
    for (volatile int i = 0; i < 180000; i++);

    I2C_Start(I2C1);
    I2C_SendDeviceAddress(I2C1, BH1750_ADDRESS, 1); // G?i d?a ch? trong ch? d? nh?n
    data[0] = I2C_ReceiveByte(I2C1);
    data[1] = I2C_ReceiveByte(I2C1); // Nh?n giá tr? ánh sáng
    I2C_Stop(I2C1);

    // Chuy?n d?i d? li?u thành giá tr? ánh sáng
    return (data[0] << 8) | data[1];
}

int main(void) {
    // C?u hình I2C và USART
    I2C_Config();
    USART_Config();

    while (1) {
        // Ð?c giá tr? ánh sáng t? BH1750
        uint16_t lightValue = BH1750_ReadLight();

        // Chuy?n d?i giá tr? thành chu?i d? g?i qua UART
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "Light: %d lux\r\n", lightValue);
        USART_SendString(buffer);

        // Thêm d? tr? tru?c l?n d?c ti?p theo
        for (volatile int i = 0; i < 1000000; i++);
    }
}
