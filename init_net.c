#include "init_net.h"

struct netif my_netif;

void network_init(void)
{
    ip4_addr_t ip_addr, net_mask, gw;

    // Инициализация lwIP
    lwip_init();

    // Настройка статического IP-адреса
    IP4_ADDR(&ip_addr, 192, 168, 1, 100);O
    IP4_ADDR(&gw, 192, 168, 1, 1);

    // Настройка сетевого интерфейса
    netif_add(&my_netif, &ip_addr, &net_mask, &gw, NULL, ethernetif_init, ethernet_input);
    netif_set_default(&my_netif);
    netif_set_up(&my_netif);
}
