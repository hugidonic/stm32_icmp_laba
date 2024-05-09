#include <stdint.h>
#include "web_if.h"
#include "LCD_Driver.h"
#include "LedsAndButtons.h"
#include "stdio.h"
#include <stdlib.h>

char String[20];

const char webif_404_reply[] = "HTTP/1.0 404 Not Found\r\n"
"Content-Type: text/html; charset=windows-1251\r\n"
"Server: STM32F100\r\n"
"\r\n"
"<pre>Page not found\r\n\r\n"
"<a href='/'>Home page</a></pre>\r\n";

const char webif_200_header[] = "HTTP/1.0 200 OK\r\n"
"Content-Type: text/html; charset=windows-1251\r\n"
"Server: STM32F100\r\n"
"\r\n";

uint8_t led_brightness;

void fill_buf(char **buf, const char *str)
{
	while (*str)
		*((*buf)++) = *(str++);
}

void webif_init()
{
}

void webif_data(uint8_t id, eth_frame_t *frame, uint16_t len)
{
	ip_packet_t *ip = (void*) (frame->data);
	tcp_packet_t *tcp = (void*) (ip->data);
	char *req = (void*) tcp_get_data(tcp);
	char *buf = (void*) (tcp->data), *buf_ptr = buf;
	char *url, *p, *params, *name, *value;
	char str[16];
	int val;

	if (!len) return;

	if ((memcmp(req, "GET ", 4) == 0) && ((p = strchr(req + 4, ' ')) != 0))
	{
		url = req + 4;
		*p = 0;

		if ((params = strchr(url, '?'))) *(params++) = 0;

		if (strcmp(url, "/") == 0)
		{
			while (params)
			{
				if ((p = strchr(params, '&'))) *(p++) = 0;

				name = params;
				if ((value = strchr(name, '='))) *(value++) = 0;

				if ((strcmp(name, "pwm") == 0) && value)
				{
					val = atoi(value);
					if (val < 0) val = 0;
					if (val > 255) val = 255;

					led_brightness = val;
					if (led_brightness & (1 << 0))
						LedEnable(Yellow);
					else
						LedDisable(Yellow);
					if (led_brightness & (1 << 1))
						LedEnable(Blue);
					else
						LedDisable(Blue);
					if (led_brightness & (1 << 2))
						LedEnable(Red);
					else
						LedDisable(Red);
					if (led_brightness & (1 << 3))
						LedEnable(Green);
					else
						LedDisable(Green);
				}

				params = p;
			}

			sprintf(str, "%d\r\n", led_brightness);

			fill_buf(&buf_ptr, webif_200_header);
			fill_buf(&buf_ptr, "<title>STM32F100 test server</title>");

			fill_buf(&buf_ptr, "<body bgcolor = \"#fff0cc\" text = \"#000000\"> <h1 align=\"center\"> Led control</h1>");
			fill_buf(&buf_ptr, "<h2 align=\"center\">");
			fill_buf(&buf_ptr, "Value: ");
			fill_buf(&buf_ptr, str);
			fill_buf(&buf_ptr, ". <a href='/edit'>Change</a>");
			fill_buf(&buf_ptr, "</h2>");
			fill_buf(&buf_ptr, "</body>");
		}

		else if (strcmp(url, "/edit") == 0)
		{
			sprintf(str, "%d", led_brightness);

			fill_buf(&buf_ptr, webif_200_header);
			fill_buf(&buf_ptr, "<title>STM32F100 change value</title>");
			fill_buf(&buf_ptr, "<pre>");
			fill_buf(&buf_ptr, "<form action='/' method='GET'>\r\n");
			fill_buf(&buf_ptr, "<body bgcolor = \"#fff0cc\" text = \"#000000\">");
			fill_buf(&buf_ptr, "<h1 align=\"center\">Enter value (0..255):\r\n</h1>");
			fill_buf(&buf_ptr, "<input type='text' align=\"middle\" name='pwm' size='2' value='");
			fill_buf(&buf_ptr, str);
			fill_buf(&buf_ptr, "'>  ");
			fill_buf(&buf_ptr, "<input type='submit' value='OK'>\r\n");
			fill_buf(&buf_ptr, "</form>");
			fill_buf(&buf_ptr, "</pre>");
		}

		else
		{
			fill_buf(&buf_ptr, webif_404_reply);
		}
	}

	tcp_send(id, frame, buf_ptr - buf, 1);
}
