#include "timer2.h"

void timer2_Init(void)
{
	TIM_TimeBaseInitTypeDef timerInit;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	timerInit.TIM_CounterMode = TIM_CounterMode_Up;
	timerInit.TIM_Period = 0xFFFF;
	timerInit.TIM_Prescaler = 72 - 1;
	
	TIM_TimeBaseInit(TIM2, &timerInit);
	
	TIM_Cmd(TIM2, ENABLE);
}

void delay_ms(uint32_t t)
{
  while(t)
	{
	  TIM_SetCounter(TIM2, 0);
		while (TIM_GetCounter(TIM2) < 1000) {}
	  --t;
	}
}
