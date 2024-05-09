#ifndef _LEDS_AND_BUTTONS_H_
#define _LEDS_AND_BUTTONS_H_

#include "stm_lib/inc/stm32f10x_gpio.h"

#define		pLed_GPIO				(GPIOC)
#define		pLed_Green_Pin			(GPIO_Pin_3)
#define		pLed_Red_Pin			(GPIO_Pin_2)
#define		pLed_Yellow_Pin			(GPIO_Pin_0)
#define		pLed_Blue_Pin			(GPIO_Pin_1)

#define		pButtons_GPIO			(GPIOC)
#define		pButton_0_Pin			(GPIO_Pin_6)
#define		pButton_1_Pin			(GPIO_Pin_7)
#define		pButton_2_Pin			(GPIO_Pin_8)

#define		ButtonPressed(Number)		((pButtons_GPIO->IDR & pButton_##Number##_Pin) == 0)
#define		ButtonReleased(Number)		((pButtons_GPIO->IDR & pButton_##Number##_Pin) != 0)

#define		LedEnable(Color)		do {pLed_GPIO->BSRR = pLed_##Color##_Pin;} while(0)
#define		LedDisable(Color)		do {pLed_GPIO->BRR = pLed_##Color##_Pin;} while(0)
#define		LedToggle(Color)		do {pLed_GPIO->ODR ^= pLed_##Color##_Pin;} while(0)

void InitLeds(void);
void InitButtons(void);

#endif /*_LEDS_AND_BUTTONS_H_*/

