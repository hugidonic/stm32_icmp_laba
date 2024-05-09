#include <stdint.h>
#include "stm_lib/inc/stm32f10x_tim.h"
#include "stm_lib/inc/stm32f10x_rcc.h"
#include "stm_lib/inc/misc.h"
#include "counter.h"
#include "LedsAndButtons.h"

uint16_t ms_count;

uint32_t tick_count;
uint32_t second_count;

void TIM4_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

	++ms_count;
	++tick_count;

	if (ms_count == 1000)
	{
		++second_count;
		ms_count = 0;
	}
}

void counter_init()
{
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_DeInit(TIM4);
	TIM_InitStructure.TIM_ClockDivision = 0;
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period = 1000;
	TIM_InitStructure.TIM_Prescaler = 24;
	TIM_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
}
