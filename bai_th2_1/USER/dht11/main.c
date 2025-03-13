#include "stm32f10x.h"                  
#include "timer2.h"
#include "dht11.h"
//#include "usart1.h"


void GPIO_Init_PB6(void)
{
  GPIO_InitTypeDef gpioInit;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	gpioInit.GPIO_Mode = GPIO_Mode_Out_OD;
	gpioInit.GPIO_Pin = GPIO_Pin_6;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpioInit);
}


void USART1_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
  GPIO_InitTypeDef GPIO_InitStruct;
  
  // PA9 - TX (Output - Alternate function push-pull)
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  // PA10 - RX (Input floating)
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  USART_InitTypeDef USART_InitStruct;
  USART_InitStruct.USART_BaudRate = 9600;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

  USART_Init(USART1, &USART_InitStruct);
  USART_Cmd(USART1, ENABLE);
}

void USART1_SendChar(char c)
{
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
  USART_SendData(USART1, c);
}

void USART1_SendString(char *s)
{
  while (*s)
  {
    USART1_SendChar(*s++);
  }
}
uint8_t DHT11_Buffer[5];  
int main()
{
	timer2_Init();
	GPIO_Init_PB6();
	USART1_Init();
	
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
	
	while(1)
	{
		DHT11();
		ReadData();  

    // G?i thông tin qua UART
    char buffer[50];
    sprintf(buffer, "Nhiet do: %d°C, Do am: %d%%\r\n", DHT11_Buffer[2], DHT11_Buffer[0]);
    USART1_SendString(buffer);

	  GPIOC->ODR |= (1 << 13);
		delay_ms(100);
		GPIOC->ODR &= ~(1 << 13);
		delay_ms(200);
	}
}