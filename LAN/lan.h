#pragma once

#include <string.h>
#include "enc28j60.h"
#include "counter.h"

/*
 * Options
 */

#define WITH_ICMP
// #define WITH_DHCP
#define WITH_UDP
#define WITH_TCP

/*
 * Config
 */

#define MAC_ADDR				{0x00,0x13,0x37,0x01,0x23,0x55}

#ifndef WITH_DHCP
#	define IP_ADDR				inet_addr(192,168,1,3)
#	define IP_SUBNET_MASK		inet_addr(255,255,255,0)
#	define IP_DEFAULT_GATEWAY	inet_addr(192,168,1,1)
#endif

#define ARP_CACHE_SIZE			3

#define IP_PACKET_TTL			64

#define TCP_MAX_CONNECTIONS		2
#define TCP_WINDOW_SIZE			65535
#define TCP_TIMEOUT				10 //s
#define TCP_SYN_MSS				448


/*
 * BE conversion
 */

#define htons(a)			((((a)>>8)&0xff)|(((a)<<8)&0xff00))
#define ntohs(a)			htons(a)

#define htonl(a)			( (((a)>>24)&0xff) | (((a)>>8)&0xff00) |\
								(((a)<<8)&0xff0000) | (((a)<<24)&0xff000000) )
#define ntohl(a)			htonl(a)

#define inet_addr(a,b,c,d)	( ((uint32_t)a) | ((uint32_t)b << 8) |\
								((uint32_t)c << 16) | ((uint32_t)d << 24) )

/*
 * Ethernet
 */

#define ETH_TYPE_ARP		htons(0x0806)
#define ETH_TYPE_IP			htons(0x0800)
#pragma pack(push, 1)
typedef struct eth_frame {
	uint8_t to_addr[6];
	uint8_t from_addr[6];
	uint16_t type;
	uint8_t data[];
} eth_frame_t;
#pragma pack(pop)

/*
 * ARP
 */

#define ARP_HW_TYPE_ETH		htons(0x0001)
#define ARP_PROTO_TYPE_IP	htons(0x0800)

#define ARP_TYPE_REQUEST	htons(1)
#define ARP_TYPE_RESPONSE	htons(2)


#pragma pack(push, 1)
typedef struct arp_message {
	uint16_t hw_type;
	uint16_t proto_type;
	uint8_t hw_addr_len;
	uint8_t proto_addr_len;
	uint16_t type;
	uint8_t mac_addr_from[6];
	uint32_t ip_addr_from;
//	uint8_t ip_addr_from2[3];
	uint8_t mac_addr_to[6];
	uint32_t ip_addr_to;
//	uint8_t ip_addr_to2[3];
} arp_message_t;
#pragma pack(pop)

typedef struct arp_cache_entry {
	uint32_t ip_addr;
	uint8_t mac_addr[6];
} arp_cache_entry_t;

/*
 * IP
 */

#define IP_PROTOCOL_ICMP	1
#define IP_PROTOCOL_TCP		6
#define IP_PROTOCOL_UDP		17

#pragma pack(push, 1)
typedef struct ip_packet {
	uint8_t ver_head_len;
	uint8_t tos;
	uint16_t total_len;
	uint16_t fragment_id;
	uint16_t flags_framgent_offset;
	uint8_t ttl;
	uint8_t protocol;
	uint16_t cksum;
	uint32_t from_addr;
	uint32_t to_addr;
	uint8_t data[];
} ip_packet_t;
#pragma pack(pop)


/*
 * ICMP
 */

#define ICMP_TYPE_ECHO_RQ	8
#define ICMP_TYPE_ECHO_RPLY	0

#pragma pack(push, 1)
typedef struct icmp_echo_packet {
	uint8_t type;
	uint8_t code;
	uint16_t cksum;
	uint16_t id;
	uint16_t seq;
	uint8_t data[];
} icmp_echo_packet_t;
#pragma pack(pop)


/*
 * UDP
 */

#pragma pack(push, 1)
typedef struct udp_packet {
	uint16_t from_port;
	uint16_t to_port;
	uint16_t len;
	uint16_t cksum;
	uint8_t data[];
} udp_packet_t;
#pragma pack(pop)


/*
 * TCP
 */

#define TCP_FLAG_URG		0x20
#define TCP_FLAG_ACK		0x10
#define TCP_FLAG_PSH		0x08
#define TCP_FLAG_RST		0x04
#define TCP_FLAG_SYN		0x02
#define TCP_FLAG_FIN		0x01

#pragma pack(push, 1)
typedef struct tcp_packet {
	uint16_t from_port;
	uint16_t to_port;
	uint32_t seq_num;
	uint32_t ack_num;
	uint8_t data_offset;
	uint8_t flags;
	uint16_t window;
	uint16_t cksum;
	uint16_t urgent_ptr;
	uint8_t data[];
} tcp_packet_t;
#pragma pack(pop)

#define tcp_head_size(tcp)	(((tcp)->data_offset & 0xf0) >> 2)
#define tcp_get_data(tcp)	((uint8_t*)(tcp) + tcp_head_size(tcp))

typedef enum tcp_status_code {
	TCP_CLOSED,
	TCP_SYN_SENT,
	TCP_SYN_RECEIVED,
	TCP_ESTABLISHED,
	TCP_FIN_WAIT
} tcp_status_code_t;

#pragma pack(push, 1)
typedef struct tcp_state {
	tcp_status_code_t status;
	uint16_t rx_time;
	uint16_t remote_port;
	uint16_t local_port;
	uint32_t remote_addr;
} tcp_state_t;
#pragma pack(pop)


/*
 * DHCP
 */

#define DHCP_SERVER_PORT		htons(67)
#define DHCP_CLIENT_PORT		htons(68)

#define DHCP_OP_REQUEST			1
#define DHCP_OP_REPLY			2

#define DHCP_HW_ADDR_TYPE_ETH	1

#define DHCP_FLAG_BROADCAST		htons(0x8000)

#define DHCP_MAGIC_COOKIE		htonl(0x63825363)

#pragma pack(push, 1)
typedef struct dhcp_message {
	uint8_t operation;
	uint8_t hw_addr_type;
	uint8_t hw_addr_len;
	uint8_t unused1;
	uint32_t transaction_id;
	uint16_t second_count;
	uint16_t flags;
	uint32_t client_addr;
	uint32_t offered_addr;
	uint32_t server_addr;
	uint32_t unused2;
	uint8_t hw_addr[16];
	uint8_t unused3[192];
	uint32_t magic_cookie;
	uint8_t options[];
} dhcp_message_t;
#pragma pack(pop)

#define DHCP_CODE_PAD			0
#define DHCP_CODE_END			255
#define DHCP_CODE_SUBNETMASK	1
#define DHCP_CODE_GATEWAY		3
#define DHCP_CODE_REQUESTEDADDR	50
#define DHCP_CODE_LEASETIME		51
#define DHCP_CODE_MESSAGETYPE	53
#define DHCP_CODE_DHCPSERVER	54
#define DHCP_CODE_RENEWTIME		58
#define DHCP_CODE_REBINDTIME	59

#pragma pack(push, 1)
typedef struct dhcp_option {
	uint8_t code;
	uint8_t len;
	uint8_t data[];
} dhcp_option_t;
#pragma pack(pop)

#define DHCP_MESSAGE_DISCOVER	1
#define DHCP_MESSAGE_OFFER		2
#define DHCP_MESSAGE_REQUEST	3
#define DHCP_MESSAGE_DECLINE	4
#define DHCP_MESSAGE_ACK		5
#define DHCP_MESSAGE_NAK		6
#define DHCP_MESSAGE_RELEASE	7
#define DHCP_MESSAGE_INFORM		8

#pragma pack(push, 1)
typedef enum dhcp_status_code {
	DHCP_INIT,
	DHCP_ASSIGNED,
	DHCP_WAITING_OFFER,
	DHCP_WAITING_ACK
} dhcp_status_code_t;
#pragma pack(pop)

/*
 * LAN
 */

extern uint8_t net_buf[];

void lan_init();
void lan_poll();
uint8_t lan_up();

void udp_packet(eth_frame_t *frame, uint16_t len);
uint8_t udp_send(eth_frame_t *frame, uint16_t len);
void udp_reply(eth_frame_t *frame, uint16_t len);

uint8_t tcp_listen(uint8_t id, eth_frame_t *frame);
void tcp_opened(uint8_t id, eth_frame_t *frame);
void tcp_closed(uint8_t id, uint8_t reset);
void tcp_data(uint8_t id, eth_frame_t *frame, uint16_t len, uint8_t closing);

uint8_t tcp_open(uint32_t addr, uint16_t port, uint16_t local_port);
void tcp_send(uint8_t id, eth_frame_t *frame, uint16_t len, uint8_t close);
