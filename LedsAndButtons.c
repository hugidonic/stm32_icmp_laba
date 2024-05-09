#include <stdint.h>
#include "stm_lib/inc/stm32f10x_gpio.h"
#include "stm_lib/inc/stm32f10x_rcc.h"
#include "LedsAndButtons.h"

void InitLeds(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = pLed_Green_Pin | pLed_Red_Pin | pLed_Yellow_Pin | pLed_Blue_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(pLed_GPIO, &GPIO_InitStructure);
}

void InitButtons(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = pButton_0_Pin | pButton_1_Pin | pButton_2_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(pButtons_GPIO, &GPIO_InitStructure);
}
