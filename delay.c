#include "delay.h"

//for 8 MHz freq. 4 m. cycles for incrementing, comparing abd branch
//for 8 MHz added 4 nop.

void _delay_us(unsigned long us)
{
	for (unsigned long i = 0; i < (us); i++)
	{
		__asm("nop");
		__asm("nop");
		__asm("nop");
		__asm("nop");
		__asm("nop");
		__asm("nop");
		__asm("nop");
		__asm("nop");
		__asm("nop");
		__asm("nop");
		__asm("nop");
		__asm("nop");
		__asm("nop");
		__asm("nop");
		__asm("nop");
		__asm("nop");
	}
}

void _delay_ms(unsigned long ms)
{
	for (unsigned long i = 0; i < ms; i++)
		_delay_us(1000);
}
