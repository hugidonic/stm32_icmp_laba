#ifndef _LCD_DRIVER_INCLUDED
#define	_LCD_DRIVER_INCLUDED

#define USER_DEFINED_CHARS_COUNT (1)

#define 	pLCD_port 		(GPIOA)

#define		pLCD_port_RS	(GPIO_Pin_0)
#define		pLCD_port_RW	(GPIO_Pin_1)
#define		pLCD_port_E		(GPIO_Pin_2)
#define		pLCD_port_D4	(GPIO_Pin_4)
#define		pLCD_port_D5	(GPIO_Pin_5)
#define		pLCD_port_D6	(GPIO_Pin_6)
#define		pLCD_port_D7	(GPIO_Pin_7)

#define pLCD_SET_E()	{pLCD_port->BSRR = pLCD_port_E;}		//���������� ��� E
#define pLCD_CLR_E()	{pLCD_port->BRR = pLCD_port_E;}			//�������� ��� E
#define pLCD_SET_RW()	{pLCD_port->BSRR = pLCD_port_RW;}		//���������� ��� R/W
#define pLCD_CLR_RW()	{pLCD_port->BRR = pLCD_port_RW;}		//�������� ��� R/W
#define pLCD_SET_RS()	{pLCD_port->BSRR = pLCD_port_RS;}		//���������� ��� RS
#define pLCD_CLR_RS()	{pLCD_port->BRR = pLCD_port_RS;}		//�������� ��� RS
#define pLCD_SET_D4()	{pLCD_port->BSRR = pLCD_port_D4;}
#define pLCD_CLR_D4()	{pLCD_port->BRR = pLCD_port_D4;}
#define pLCD_SET_D5()	{pLCD_port->BSRR = pLCD_port_D5;}
#define pLCD_CLR_D5()	{pLCD_port->BRR = pLCD_port_D5;}
#define pLCD_SET_D6()	{pLCD_port->BSRR = pLCD_port_D6;}
#define pLCD_CLR_D6()	{pLCD_port->BRR = pLCD_port_D6;}
#define pLCD_SET_D7()	{pLCD_port->BSRR = pLCD_port_D7;}
#define pLCD_CLR_D7()	{pLCD_port->BRR = pLCD_port_D7;}

//#define USER_DEFINED_CHARS_COUNT_LCD 4



#define		RUS_B	(0xA0)		// �
#define		RUS_G	(0xA1)		// �
#define		RUS_IE	(0xA2)		// �
#define		RUS_GE	(0xA3)		// �
#define		RUS_Z	(0xA4)		// �
#define		RUS_I	(0xA5)		// �
#define		RUS_II	(0xA6)		// �
#define		RUS_L	(0xA7)		// �
#define		RUS_P	(0xA8)		// �
#define		RUS_Y	(0xA9)		// �
#define		RUS_F	(0xAA)		// �
#define		RUS_CH	(0xAB)		// �
#define		RUS_SH	(0xAC)		// �
#define		RUS_TVZ	(0xAD)		// �
#define		RUS_bI	(0xAE)		// �
#define		RUS_EE	(0xAF)		// �
#define		RUS_U	(0xB0)		// �
#define		RUS_IA	(0xB1)		// �
#define		RUS_b	(0xB2)		// �
#define		RUS_v	(0xB3)		// �
#define		RUS_g	(0xB4)		// �
#define		RUS_ie	(0xB5)		// �
#define		RUS_ge	(0xB6)		// �
#define		RUS_z	(0xB7)		// �
#define		RUS_i	(0xB8)		// �
#define		RUS_ii	(0xB9)		// �
#define		RUS_k	(0xBA)		// �
#define		RUS_l	(0xBB)		// �
#define		RUS_m	(0xBC)		// �
#define		RUS_n	(0xBD)		// �
#define		RUS_p	(0xBE)		// �
#define		RUS_t	(0xBF)		// �
#define		RUS_ch	(0xC0)		// �
#define		RUS_sh	(0xC1)		// �
#define		RUS_tvz	(0xC2)		// �
#define		RUS_bi	(0xC3)		// �
#define		RUS_mz	(0xC4)		// �
#define		RUS_ee	(0xC5)		// �
#define		RUS_u	(0xC6)		// �
#define		RUS_ia	(0xC7)		// �
#define		RUS_D	(0xE0)		// �
#define		RUS_TC	(0xE1)		// �
#define		RUS_SHC	(0xE2)		// �
#define		RUS_d	(0xE3)		// �
#define		RUS_f	(0xE4)		// �
#define		RUS_tc	(0xE5)		// �
#define		RUS_shc	(0xE6)		// �

void LcdSendNibble(unsigned char data);		//������ ����� ������� � ���

void LcdSendByte(char data);			//������ ����� ������ � ���

void LcdSendCommand(char data);			//������ ������� � ���

void LcdSendString(char* String, unsigned char length);	//����� ������ String ������ length

void LcdClear(void);				//��������� ������� ���

void LcdGotoXY(unsigned char X, unsigned char Y);//��������� ������� � �������� �������

void LcdInit(void);				//������������� ���

void LcdEnableCursor(void);
void LcdDefineChars(void);

void LcdDisableCursor(void);
#endif /*_LCD_DRIVER_INCLUDED */
