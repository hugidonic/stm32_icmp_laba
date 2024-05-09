#ifndef _WEB_IF_H
#define _WEB_IF_H

#include "lan.h"

void webif_init();
void webif_data(uint8_t id, eth_frame_t *frame, uint16_t len);

#endif /*_WEB_IF_H*/
