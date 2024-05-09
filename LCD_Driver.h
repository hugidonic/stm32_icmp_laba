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

#define pLCD_SET_E()	{pLCD_port->BSRR = pLCD_port_E;}		//Установить бит E
#define pLCD_CLR_E()	{pLCD_port->BRR = pLCD_port_E;}			//Сбросить бит E
#define pLCD_SET_RW()	{pLCD_port->BSRR = pLCD_port_RW;}		//Установить бит R/W
#define pLCD_CLR_RW()	{pLCD_port->BRR = pLCD_port_RW;}		//Сбросить бит R/W
#define pLCD_SET_RS()	{pLCD_port->BSRR = pLCD_port_RS;}		//Установить бит RS
#define pLCD_CLR_RS()	{pLCD_port->BRR = pLCD_port_RS;}		//Сбросить бит RS
#define pLCD_SET_D4()	{pLCD_port->BSRR = pLCD_port_D4;}
#define pLCD_CLR_D4()	{pLCD_port->BRR = pLCD_port_D4;}
#define pLCD_SET_D5()	{pLCD_port->BSRR = pLCD_port_D5;}
#define pLCD_CLR_D5()	{pLCD_port->BRR = pLCD_port_D5;}
#define pLCD_SET_D6()	{pLCD_port->BSRR = pLCD_port_D6;}
#define pLCD_CLR_D6()	{pLCD_port->BRR = pLCD_port_D6;}
#define pLCD_SET_D7()	{pLCD_port->BSRR = pLCD_port_D7;}
#define pLCD_CLR_D7()	{pLCD_port->BRR = pLCD_port_D7;}

//#define USER_DEFINED_CHARS_COUNT_LCD 4



#define		RUS_B	(0xA0)		// Б
#define		RUS_G	(0xA1)		// Г
#define		RUS_IE	(0xA2)		// Ё
#define		RUS_GE	(0xA3)		// Ж
#define		RUS_Z	(0xA4)		// З
#define		RUS_I	(0xA5)		// И
#define		RUS_II	(0xA6)		// Й
#define		RUS_L	(0xA7)		// Л
#define		RUS_P	(0xA8)		// П
#define		RUS_Y	(0xA9)		// У
#define		RUS_F	(0xAA)		// Ф
#define		RUS_CH	(0xAB)		// Ч
#define		RUS_SH	(0xAC)		// Ш
#define		RUS_TVZ	(0xAD)		// Ъ
#define		RUS_bI	(0xAE)		// Ы
#define		RUS_EE	(0xAF)		// Э
#define		RUS_U	(0xB0)		// Ю
#define		RUS_IA	(0xB1)		// Я
#define		RUS_b	(0xB2)		// б
#define		RUS_v	(0xB3)		// в
#define		RUS_g	(0xB4)		// г
#define		RUS_ie	(0xB5)		// ё
#define		RUS_ge	(0xB6)		// ж
#define		RUS_z	(0xB7)		// з
#define		RUS_i	(0xB8)		// и
#define		RUS_ii	(0xB9)		// й
#define		RUS_k	(0xBA)		// к
#define		RUS_l	(0xBB)		// л
#define		RUS_m	(0xBC)		// м
#define		RUS_n	(0xBD)		// н
#define		RUS_p	(0xBE)		// п
#define		RUS_t	(0xBF)		// т
#define		RUS_ch	(0xC0)		// ч
#define		RUS_sh	(0xC1)		// ш
#define		RUS_tvz	(0xC2)		// ъ
#define		RUS_bi	(0xC3)		// ы
#define		RUS_mz	(0xC4)		// ь
#define		RUS_ee	(0xC5)		// э
#define		RUS_u	(0xC6)		// ю
#define		RUS_ia	(0xC7)		// я
#define		RUS_D	(0xE0)		// Д
#define		RUS_TC	(0xE1)		// Ц
#define		RUS_SHC	(0xE2)		// Щ
#define		RUS_d	(0xE3)		// д
#define		RUS_f	(0xE4)		// ф
#define		RUS_tc	(0xE5)		// ц
#define		RUS_shc	(0xE6)		// щ

void LcdSendNibble(unsigned char data);		//Запись одной тетрады в ЖКИ

void LcdSendByte(char data);			//Запись байта данных в ЖКИ

void LcdSendCommand(char data);			//Запись команды в ЖКИ

void LcdSendString(char* String, unsigned char length);	//Вывод строки String длиной length

void LcdClear(void);				//Процедура очистки ЖКИ

void LcdGotoXY(unsigned char X, unsigned char Y);//Установка курсора в заданную позицию

void LcdInit(void);				//Инициализация ЖКИ

void LcdEnableCursor(void);
void LcdDefineChars(void);

void LcdDisableCursor(void);
#endif /*_LCD_DRIVER_INCLUDED */
