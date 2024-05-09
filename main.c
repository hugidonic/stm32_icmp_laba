#include <stdint.h>
#include <stdlib.h>

#include "LCD_Driver.h"
#include "LedsAndButtons.h"
#include "counter.h"
#include "delay.h"
#include "lan.h"
#include "stdio.h"
#include "web_if.h"
#include "init_net.h"

void udp_packet(eth_frame_t *frame, uint16_t len) {
  char Buffer[20];

  LcdGotoXY(0, 0);
  LcdSendString("  UDP packet!   ", 16);
  sprintf(Buffer, "Frm:%02X%02X%02X%02X%02X%02X", frame->from_addr[0],
          frame->from_addr[1], frame->from_addr[2], frame->from_addr[3],
          frame->from_addr[4], frame->from_addr[5]);
  LcdGotoXY(0, 1);
  LcdSendString(Buffer, 16);
  sprintf(Buffer, "Len:%03d,Prt:%04d", len,
          (*(frame->data + 23)) + ((*(frame->data + 22)) << 8));
  LcdGotoXY(0, 2);
  LcdSendString(Buffer, 16);
  memset(Buffer, 0x20, 16);
  memcpy(Buffer, frame->data + 28, (len - 1) % 16);
  LcdGotoXY(0, 3);
  LcdSendString(Buffer, 16);
}

uint8_t tcp_listen(uint8_t id, eth_frame_t *frame) {
  ip_packet_t *ip = (void *)(frame->data);
  tcp_packet_t *tcp = (void *)(ip->data);

  if ((tcp->to_port == htons(80)) || (tcp->to_port == htons(44444))) {
    return 1;
  }
  return 0;
}


void tcp_data(uint8_t id, eth_frame_t *frame, uint16_t len, uint8_t closing) {
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

int main(void) {
  InitLeds();
  InitButtons();
  _delay_ms(100);

  LcdInit();


  lan_init();
  network_init();
  counter_init();
  webif_init();

	uint16_t len;
  eth_frame_t *frame = (void *)net_buf;

  while (1) {
		if (lan_up()) {
			LedEnable(Green);
			lan_poll();
		} else {
			LedEnable(Red);
		}
  }

  return 0;
}
