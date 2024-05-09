#include "LCD_Driver.h"
#include "LedsAndButtons.h"
#include <stdlib.h>
#include <stdint.h>
#include "stdio.h"
#include "lan.h"
#include "counter.h"
#include "web_if.h"
#include "delay.h"

//void GPIO_Blink(void);

const char Screen_Logo_Image[4][16]=
{ { 0x20, 0x20, 0xFF, 0x00, 0x20, 0x20, 0x20, 0x20, RUS_Y, RUS_ch, 'e', RUS_b, RUS_n, 'a', RUS_ia, 0x20 },
  { 0x20, 0x20, 0x20, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 'T', 'e', 'x', RUS_n, RUS_i, RUS_k, 'a' },
  { 0xFF, 0x20, 0xFF, 0xFF, 0xFF, 0x20, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 },
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x22, RUS_P, 'P', 'O', RUS_F, RUS_I, 0x22 } };

// int prev_button_pressed[3] = { 0 };
// int button_states[3] = { 0 };

void udp_packet(eth_frame_t *frame, uint16_t len) {
	/*ip_packet_t* ip = (void*) frame->data;
	udp_packet_t* udp = (void*) ip->data;
	uint8_t* d = udp->data;

	if(len == 2 && d[0] == 's') {
		for(int i = 0; i < 3; ++i) {
			*d++ = 'b';
			*d++ = '0' + i;
			*d++ = '=';
			*d++ = '0' + button_states[i];
			*d++ = ' ';
		}
		*d++ = '\n';
		udp_reply(frame, d - udp->data);

		return;
	}

	if(len != 4 || d[1] != ' ') {
		return;
	}
	uint8_t color = d[0];
	uint8_t action = d[2];

	uint16_t led_pin;

	switch(color) {
	case 'r' : led_pin = pLed_Red_Pin; break;
	case 'g' : led_pin = pLed_Green_Pin; break;
	case 'b' : led_pin = pLed_Blue_Pin; break;
	case 'y' : led_pin = pLed_Yellow_Pin; break;
	case 'a' : led_pin = pLed_Red_Pin | pLed_Green_Pin | pLed_Blue_Pin | pLed_Yellow_Pin; break;
	default: return;
	}

	if(action == '1') {
		pLed_GPIO->BSRR = led_pin;
	}
	else {
		pLed_GPIO->BRR = led_pin;
	}*/

	/*ip_packet_t* ip = (void*) frame->data;
	udp_packet_t* udp = (void*) ip->data;

	const char* salam = "Salam\n";
	int salam_len = strlen(salam);

	if(len != salam_len || strcmp(salam, udp->data) != 0) {
		return;
	}

	const char* msg = "Uagalaykum Uasalam\n";
	int msg_len = strlen(msg);

	memcpy(udp->data, msg, msg_len);
	udp_reply(frame, msg_len);*/


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

unsigned char image[] = {
		0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52,
		  0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x08, 0x06, 0x00, 0x00, 0x00, 0xc4, 0x0f, 0xbe,
		  0x8b, 0x00, 0x00, 0x00, 0x01, 0x73, 0x52, 0x47, 0x42, 0x00, 0xae, 0xce, 0x1c, 0xe9, 0x00, 0x00,
		  0x00, 0x04, 0x67, 0x41, 0x4d, 0x41, 0x00, 0x00, 0xb1, 0x8f, 0x0b, 0xfc, 0x61, 0x05, 0x00, 0x00,
		  0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x12, 0x74, 0x00, 0x00, 0x12, 0x74, 0x01, 0xde,
		  0x66, 0x1f, 0x78, 0x00, 0x00, 0x00, 0x60, 0x49, 0x44, 0x41, 0x54, 0x28, 0x53, 0x6d, 0x4d, 0xc1,
		  0x11, 0xc0, 0x20, 0x08, 0x63, 0x27, 0x67, 0x71, 0x05, 0xe7, 0x60, 0x0d, 0x57, 0x70, 0x16, 0xbf,
		  0xce, 0x93, 0x86, 0x82, 0x47, 0x6b, 0xeb, 0x5d, 0xce, 0x04, 0x12, 0x22, 0xd0, 0x02, 0x87, 0xc4,
		  0xff, 0xe6, 0x61, 0xb0, 0xc1, 0x69, 0x70, 0x4d, 0x03, 0xc9, 0x9a, 0x68, 0xe0, 0xab, 0xe4, 0x86,
		  0xad, 0xb9, 0xbb, 0x0d, 0x4d, 0x3b, 0x64, 0xf8, 0xc0, 0x52, 0x6d, 0x50, 0xab, 0x07, 0xb2, 0xc2,
		  0x92, 0xc6, 0xeb, 0xa7, 0xe2, 0xd9, 0xbb, 0xcd, 0x39, 0xcb, 0x0b, 0xec, 0xc5, 0xea, 0x01, 0xf2,
		  0xdf, 0x0b, 0xc7, 0x79, 0x68, 0xc1, 0x05, 0x5c, 0xe9, 0xac, 0x33, 0x26, 0xd2, 0xa5, 0x07, 0x00,
		  0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

void tcp_opened(uint8_t id, eth_frame_t *frame)
{
	/*ip_packet_t* ip = (void*) frame->data;
	tcp_packet_t* udp = (void*) ip->data;
	uint8_t* d = udp->data;
	const char* msg =
		    "HTTP/1.0 200 OK\r\n"
		    "Content-Type: text/html; charset=windows-1251\r\n"
		    "Connection: close\r\n"
		    "\r\n"
			"<img src='image.png'>";

	int msg_len = strlen(msg);
	memcpy(d, msg, msg_len);
	tcp_send(id, frame, msg_len, 1);*/
}

void tcp_closed(uint8_t id, uint8_t reset)
{

}

void tcp_data(uint8_t id, eth_frame_t *frame, uint16_t len, uint8_t closing)
{
	/*char Buffer[20];

	LcdGotoXY(0, 0);
	LcdSendString("  TCP packet!   ", 16);
	LcdGotoXY(0, 1);
	LcdSendString("                ", 16);
	sprintf(Buffer, "Len:%03d        ", len);
	LcdGotoXY(0, 2);
	LcdSendString(Buffer, 16);
	LcdGotoXY(0, 3);
	LcdSendString("                ", 16);*/
	//webif_data(id, frame, len);
	/*ip_packet_t* ip = (void*) frame->data;
	tcp_packet_t* udp = (void*) ip->data;
	uint8_t* d = udp->data;
	const char* msg =
			"HTTP/1.0 200 OK"
			"Content-Type: image/png"
			"Content-Length: 203"
			"Connection: close";

	int msg_len = strlen(msg);
	int image_len = sizeof(image);
	memcpy(d, msg, msg_len);
	memcpy(d + msg_len, image, image_len);
	tcp_send(id, frame, msg_len + image_len, 1);*/
}

int main(void)
{
	InitLeds();
	InitButtons();
	_delay_ms(100);

	LcdInit();

	for (unsigned char Y = 0; Y < 4; Y++) {
		LcdGotoXY(0, Y);
		for (unsigned char X = 0; X < 16; X++)
			LcdSendByte((Screen_Logo_Image[Y][X]));
	}

	lan_init();
	counter_init();

	while (1)
	{
		/*int current_button_pressed[3];
		current_button_pressed[0] = ButtonPressed(0); current_button_pressed[1] = ButtonPressed(1); current_button_pressed[2] = ButtonPressed(2);

		for(int i = 0; i < 3; ++i) {
			if(prev_button_pressed[i] == 1 && current_button_pressed[i] == 0)
				button_states[i] = !button_states[i];
		}*/

		lan_poll();

		//for(int i = 0; i < 3; ++i) prev_button_pressed[i] = current_button_pressed[i];
	}

	return 0;
}

