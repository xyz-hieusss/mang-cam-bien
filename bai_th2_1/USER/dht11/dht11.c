#include "dht11.h"
#include "timer2.h"

void DHT11(void)
{
	  GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		delay_ms(20);
		GPIO_SetBits(GPIOB, GPIO_Pin_6);
	
  /* doi chan PB6 len cao */
		TIM_SetCounter(TIM2, 0);
		while (TIM_GetCounter(TIM2) < 10) {
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)) {
				break;
			}
		}
		u16Tim = TIM_GetCounter(TIM2);
		if (u16Tim >= 10) {
			 
		}
		
		/* doi chan PB6 xuong thap */
		TIM_SetCounter(TIM2, 0);
		while (TIM_GetCounter(TIM2) < 45) {
			if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)) {
				break;
			}
		}
		u16Tim = TIM_GetCounter(TIM2);
		if ((u16Tim >= 45) || (u16Tim <= 5)) {
			 
		}
		
		/* doi chan PB6 len cao */
		TIM_SetCounter(TIM2, 0);
		while (TIM_GetCounter(TIM2) < 90) {
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)) {
				break;
			}
		}
		u16Tim = TIM_GetCounter(TIM2);
		if ((u16Tim >= 90) || (u16Tim <= 70)) {
			 
		}
		
		/* doi chan PB6 xuong thap */
		TIM_SetCounter(TIM2, 0);
		while (TIM_GetCounter(TIM2) < 95) {
			if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)) {
				break;
			}
		}
		u16Tim = TIM_GetCounter(TIM2);
		if ((u16Tim >= 95) || (u16Tim <= 75)) {
			 
		}
		
		/* nhan byte so 1 */
		for (i = 0; i < 8; ++i) {
			/* doi chan PB6 len cao */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 65) {
				if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 65) || (u16Tim <= 45)) {
				 
			}
			
			/* doi chan PB6 xuong thap */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 80) {
				if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 80) || (u16Tim <= 10)) {
				 
			}
			u8Buff[0] <<= 1;
			if (u16Tim > 45) {
				/* nhan duoc bit 1 */
				u8Buff[0] |= 1;
			} else {
				/* nhan duoc bit 0 */
				u8Buff[0] &= ~1;
			}
		}
		
		/* nhan byte so 2 */
		for (i = 0; i < 8; ++i) {
			/* doi chan PB6 len cao */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 65) {
				if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 65) || (u16Tim <= 45)) {
				 
			}
			
			/* doi chan PB6 xuong thap */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 80) {
				if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 80) || (u16Tim <= 10)) {
				 
			}
			u8Buff[1] <<= 1;
			if (u16Tim > 45) {
				/* nhan duoc bit 1 */
				u8Buff[1] |= 1;
			} else {
				/* nhan duoc bit 0 */
				u8Buff[1] &= ~1;
			}
		}
		
		/* nhan byte so 3 */
		for (i = 0; i < 8; ++i) {
			/* doi chan PB6 len cao */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 65) {
				if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 65) || (u16Tim <= 45)) {
				 
			}
			
			/* doi chan PB6 xuong thap */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 80) {
				if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 80) || (u16Tim <= 10)) {
			 
			}
			u8Buff[2] <<= 1;
			if (u16Tim > 45) {
				/* nhan duoc bit 1 */
				u8Buff[2] |= 1;
			} else {
				/* nhan duoc bit 0 */
				u8Buff[2] &= ~1;
			}
		}
		
		/* nhan byte so 4 */
		for (i = 0; i < 8; ++i) {
			/* doi chan PB6 len cao */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 65) {
				if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 65) || (u16Tim <= 45)) {
				
			}
			
			/* doi chan PB6 xuong thap */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 80) {
				if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 80) || (u16Tim <= 10)) {
				 
			}
			u8Buff[3] <<= 1;
			if (u16Tim > 45) {
				/* nhan duoc bit 1 */
				u8Buff[3] |= 1;
			} else {
				/* nhan duoc bit 0 */
				u8Buff[3] &= ~1;
			}
		}
		
		/* nhan byte so 5 */
		for (i = 0; i < 8; ++i) {
			/* doi chan PB6 len cao */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 65) {
				if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 65) || (u16Tim <= 45)) {

			}
			
			/* doi chan PB6 xuong thap */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 80) {
				if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 80) || (u16Tim <= 10)) {
				 
			}
			
			u8Buff[4] <<= 1;
			
			if (u16Tim > 45) {
				/* nhan duoc bit 1 */
				u8Buff[4] |= 1;
			} else {
				/* nhan duoc bit 0 */
				u8Buff[4] &= ~1;
			}
		}
		
		u8CheckSum = u8Buff[0] + u8Buff[1] + u8Buff[2] + u8Buff[3];
		if (u8CheckSum != u8Buff[4]) {
			while (1) {
			}
		}
}

void send(uint8_t u8Data)
{
	uint8_t i;
	for (i = 0; i < 8; ++i) {
		if (u8Data & 0x80) {
			GPIO_SetBits(GPIOA, GPIO_Pin_0);
			delay_ms(4);
			GPIO_ResetBits(GPIOA, GPIO_Pin_0);
			delay_ms(1);
		} else {
			GPIO_SetBits(GPIOA, GPIO_Pin_0);
			delay_ms(1);
			GPIO_ResetBits(GPIOA, GPIO_Pin_0);
			delay_ms(4);
		}
		u8Data <<= 1;
	}
}

void ReadData(void)
{
    /* gui do am */
		send(u8Buff[0]);
		
		delay_ms(20);
		
		/* gui nhiet do */
		send(u8Buff[2]);
}
