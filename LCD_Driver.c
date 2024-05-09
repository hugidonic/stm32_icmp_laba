#include "LCD_Driver.h"
#include "stm_lib/inc/stm32f10x_gpio.h"
#include "stm_lib/inc/stm32f10x_rcc.h"
#include "delay.h"

void LcdSendNibble(unsigned char data)		//Запись одной тетрады в ЖКИ
{
	pLCD_CLR_RW();				//Установить признак записи в ЖКИ
	if (data & (1 << 7)) pLCD_SET_D7()	else pLCD_CLR_D7();
	if (data & (1 << 6)) pLCD_SET_D6()	else pLCD_CLR_D6();
	if (data & (1 << 5)) pLCD_SET_D5()	else pLCD_CLR_D5();
	if (data & (1 << 4)) pLCD_SET_D4()	else pLCD_CLR_D4();
	pLCD_SET_E();					//Включить стробирующий вывод порта
	_delay_us(40);					//Задержка в 4 мкс
	pLCD_CLR_E();					//Выключить стробирующий вывод порта
	pLCD_SET_RW();				//Убрать признак записи в ЖКИ
	_delay_us(80);					//Задержка в 40 мкс
}

void LcdSendByte(char data)			//Запись байта данных в ЖКИ
{
	pLCD_SET_RS();				//Установить признак передачи данных
	LcdSendNibble(data & 0xF0);		//Вывести старшую тетраду
	LcdSendNibble((data & 0x0F) << 4);	//Вывести младшую тетраду
}

void LcdSendCommand(char data)			//Запись команды в ЖКИ
{
	pLCD_CLR_RS();				//Установить признак передачи команды
	LcdSendNibble(data & 0xF0);		//Вывести старшую тетраду
	LcdSendNibble((data & 0x0F) << 4);	//Вывести младшую тетраду
}

void LcdSendString(char* String, unsigned char length)	//Вывод строки String длиной length
{
	for(unsigned char i=0; i<length; i++)	//Выводим "length" байт в ЖКИ
		LcdSendByte(String[i]);
}

void LcdClear(void)				//Процедура очистки ЖКИ
{
	LcdSendCommand(0x01);			//Послать команду
	_delay_us(1500);			//Задержка в 1500 мкс
}

void LcdGotoXY(unsigned char X, unsigned char Y)//Установка курсора в заданную позицию
{
	unsigned char Temp = 0;			//Временная переменная
	switch(Y)				//В зависимости от вертикальной координаты
	{
		case 0: Temp = 0x00; break;	//Координата начала первой строчки
		case 1: Temp = 0x40; break;	//Координата начала второй строчки
		case 2: Temp = 0x10; break;	//Координата начала третьей строчки
		case 3: Temp = 0x50; break;	//Координита начала четвертой строчки
	}
	Temp += X;				//Прибавить горизонтальную координату
	Temp |= 0b10000000;			//Установить старший бит команды - признак
	LcdSendCommand(Temp);			//команды для установки адреса DDRAM
}

void LcdEnableCursor(void)
{
	LcdSendCommand(0b00001111);
}

void LcdDisableCursor(void)
{
	LcdSendCommand(0b00001100);
}

void LcdInit(void)				//Инициализация ЖКИ
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

 	GPIO_InitStructure.GPIO_Pin = pLCD_port_E | pLCD_port_RW | pLCD_port_RS | pLCD_port_D4 | pLCD_port_D5 | pLCD_port_D6 | pLCD_port_D7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(pLCD_port, &GPIO_InitStructure);

	pLCD_CLR_RW();
	pLCD_CLR_E();
	pLCD_CLR_RS();
	pLCD_CLR_D4();
	pLCD_CLR_D5();
	pLCD_CLR_D6();
	pLCD_CLR_D7();

	LcdSendNibble(0x30);			//Послать тетраду 0b0011
	_delay_us(80);				//Задержка 80 мкс
	LcdSendNibble(0x30);			//Послать тетраду 0b0011
	_delay_us(80);				//Задержка 80 мкс
	LcdSendNibble(0x30);			//Послать тетраду 0b0011
	_delay_us(80);				//Задержка 80 мкс
	LcdSendNibble(0x20);			//Послать тетраду 0b0010
	_delay_us(80);				//Задержка 80 мкс
	LcdSendCommand(0x28);			//Установка 4-разрядного обмена
	_delay_us(80);				//Задержка 80 мкс
	LcdSendCommand(0x0C);			//Включить дисплей. Курсор выключен
	_delay_us(80);				//Задержка 80 мкс
	LcdSendCommand(0x04);			//Курсор сдвигается вправо. Запрет сдвига дисплея.
	_delay_us(80);				//Задержка 80 мкс
	LcdSendCommand(0x01);			//Очистка дисплея
	_delay_us(2000);			//Задержка 2 мс
	LcdDefineChars();
}

const char UserDefinedChars [USER_DEFINED_CHARS_COUNT][8]=
{
	{0b00000100,	//	*....
	 0b00000100,	//	**...
	 0b00001110,	//	**...
	 0b00001110,	//	***..
	 0b00001110,	//	***..
	 0b00011111,	//	****.
	 0b00011111,	//	****.
	 0b00011111}	//	*****
};

void LcdDefineChars(void)
{
	for(unsigned char i = 0; i < USER_DEFINED_CHARS_COUNT; i++)
	{
		LcdSendCommand(0x40 + (i << 3));
		for(unsigned char j = 0; j < 8; j++)
			LcdSendByte(UserDefinedChars[i][j]);
	}
	LcdGotoXY(0,0);
}
