#include "LCD_Driver.h"
#include "stm_lib/inc/stm32f10x_gpio.h"
#include "stm_lib/inc/stm32f10x_rcc.h"
#include "delay.h"

void LcdSendNibble(unsigned char data)		//������ ����� ������� � ���
{
	pLCD_CLR_RW();				//���������� ������� ������ � ���
	if (data & (1 << 7)) pLCD_SET_D7()	else pLCD_CLR_D7();
	if (data & (1 << 6)) pLCD_SET_D6()	else pLCD_CLR_D6();
	if (data & (1 << 5)) pLCD_SET_D5()	else pLCD_CLR_D5();
	if (data & (1 << 4)) pLCD_SET_D4()	else pLCD_CLR_D4();
	pLCD_SET_E();					//�������� ������������ ����� �����
	_delay_us(40);					//�������� � 4 ���
	pLCD_CLR_E();					//��������� ������������ ����� �����
	pLCD_SET_RW();				//������ ������� ������ � ���
	_delay_us(80);					//�������� � 40 ���
}

void LcdSendByte(char data)			//������ ����� ������ � ���
{
	pLCD_SET_RS();				//���������� ������� �������� ������
	LcdSendNibble(data & 0xF0);		//������� ������� �������
	LcdSendNibble((data & 0x0F) << 4);	//������� ������� �������
}

void LcdSendCommand(char data)			//������ ������� � ���
{
	pLCD_CLR_RS();				//���������� ������� �������� �������
	LcdSendNibble(data & 0xF0);		//������� ������� �������
	LcdSendNibble((data & 0x0F) << 4);	//������� ������� �������
}

void LcdSendString(char* String, unsigned char length)	//����� ������ String ������ length
{
	for(unsigned char i=0; i<length; i++)	//������� "length" ���� � ���
		LcdSendByte(String[i]);
}

void LcdClear(void)				//��������� ������� ���
{
	LcdSendCommand(0x01);			//������� �������
	_delay_us(1500);			//�������� � 1500 ���
}

void LcdGotoXY(unsigned char X, unsigned char Y)//��������� ������� � �������� �������
{
	unsigned char Temp = 0;			//��������� ����������
	switch(Y)				//� ����������� �� ������������ ����������
	{
		case 0: Temp = 0x00; break;	//���������� ������ ������ �������
		case 1: Temp = 0x40; break;	//���������� ������ ������ �������
		case 2: Temp = 0x10; break;	//���������� ������ ������� �������
		case 3: Temp = 0x50; break;	//���������� ������ ��������� �������
	}
	Temp += X;				//��������� �������������� ����������
	Temp |= 0b10000000;			//���������� ������� ��� ������� - �������
	LcdSendCommand(Temp);			//������� ��� ��������� ������ DDRAM
}

void LcdEnableCursor(void)
{
	LcdSendCommand(0b00001111);
}

void LcdDisableCursor(void)
{
	LcdSendCommand(0b00001100);
}

void LcdInit(void)				//������������� ���
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

	LcdSendNibble(0x30);			//������� ������� 0b0011
	_delay_us(80);				//�������� 80 ���
	LcdSendNibble(0x30);			//������� ������� 0b0011
	_delay_us(80);				//�������� 80 ���
	LcdSendNibble(0x30);			//������� ������� 0b0011
	_delay_us(80);				//�������� 80 ���
	LcdSendNibble(0x20);			//������� ������� 0b0010
	_delay_us(80);				//�������� 80 ���
	LcdSendCommand(0x28);			//��������� 4-���������� ������
	_delay_us(80);				//�������� 80 ���
	LcdSendCommand(0x0C);			//�������� �������. ������ ��������
	_delay_us(80);				//�������� 80 ���
	LcdSendCommand(0x04);			//������ ���������� ������. ������ ������ �������.
	_delay_us(80);				//�������� 80 ���
	LcdSendCommand(0x01);			//������� �������
	_delay_us(2000);			//�������� 2 ��
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
