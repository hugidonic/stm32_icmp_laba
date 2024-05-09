#include "LCD_Driver.h"
#include "LedsAndButtons.h"
#include <stdlib.h>
#include <stdint.h>
#include "stdio.h"
#include "lan.h"
#include "counter.h"
#include "web_if.h"
#include "delay.h"

const char Screen_Logo_Image[4][16]=
{ { 0x20, 0x20, 0x20, 0x00, 0x20, 0x20, 0x20, 0x20, RUS_Y, RUS_ch, 'e', RUS_b, RUS_n, 'a', RUS_ia, 0x20 },
  { 0x20, 0x20, 0x20, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 'T', 'e', 'x', RUS_n, RUS_i, RUS_k, 'a' },
  { 0xFF, 0x20, 0xFF, 0xFF, 0xFF, 0x20, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 },
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x22, RUS_P, 'P', 'O', RUS_F, RUS_I, 0x22 } };

void udp_packet(eth_frame_t *frame, uint16_t len)
{
	char Buffer[20];

	LcdGotoXY(0, 0);
	LcdSendString("  UDP packet!   ", 16);
	sprintf(Buffer, "Frm:%02X%02X%02X%02X%02X%02X", frame->from_addr[0], frame->from_addr[1], frame->from_addr[2], frame->from_addr[3], frame->from_addr[4], frame->from_addr[5]);
	LcdGotoXY(0, 1);
	LcdSendString(Buffer, 16);
	sprintf(Buffer, "Len:%03d,Prt:%04d", len, (*(frame->data + 23)) +  ((*(frame->data + 22)) << 8));
	LcdGotoXY(0, 2);
	LcdSendString(Buffer, 16);
	memset(Buffer, 0x20, 16);
	memcpy(Buffer, frame->data + 28, (len - 1) % 16);
	LcdGotoXY(0, 3);
	LcdSendString(Buffer, 16);
}

uint8_t tcp_listen(uint8_t id, eth_frame_t *frame)
{
	ip_packet_t *ip = (void*) (frame->data);
	tcp_packet_t *tcp = (void*) (ip->data);

	if ((tcp->to_port == htons(80)) || (tcp->to_port == htons(44444)))
	{
		return 1;
	}
	return 0;
}

void tcp_opened(uint8_t id, eth_frame_t *frame)
{
}

void tcp_closed(uint8_t id, uint8_t reset)
{
}

void tcp_data(uint8_t id, eth_frame_t *frame, uint16_t len, uint8_t closing)
{
	char Buffer[20];

	LcdGotoXY(0, 0);
	LcdSendString("  TCP packet!   ", 16);
	LcdGotoXY(0, 1);
	LcdSendString("                ", 16);
	sprintf(Buffer, "Len:%03d        ", len);
	LcdGotoXY(0, 2);
	LcdSendString(Buffer, 16);
	LcdGotoXY(0, 3);
	LcdSendString("                ", 16);
	webif_data(id, frame, len);
}

int main(void)
{
	InitLeds();
	InitButtons();
	_delay_ms(100);

	LcdInit();

	for (unsigned char Y = 0; Y < 4; Y++)
	{
		LcdGotoXY(0, Y);

		for (unsigned char X = 0; X < 16; X++)
			LcdSendByte((Screen_Logo_Image[Y][X]));
	}

	lan_init();
	counter_init();
	webif_init();

	while (1)
	{
		lan_poll();
		if ((ButtonPressed(0)) || (ButtonPressed(1)) || (ButtonPressed(2)))
			LcdClear();
	}

	return 0;
}

