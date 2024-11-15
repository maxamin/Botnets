    if err != nil || cmd == "TOOLS" || cmd == "tools" {
            this.conn.Write([]byte("\033[2J\033[1H")) //display main header
            this.conn.Write([]byte("\033[01;31m╔══════════════════════════════════╗\x1b[0m\r\n"))
			this.conn.Write([]byte("\033[01;31m║ -ping \x1b[90m- \x1b[0mPing an IPv4             \033[01;31m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\033[01;31m║ -iplookup \x1b[90m- \x1b[0mLookup IPv4          \033[01;31m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\033[01;31m║ -portscan \x1b[90m- \x1b[0mPortscan IPv4        \033[01;31m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\033[01;31m║ -resolve \x1b[90m- \x1b[0mResolve a URL         \033[01;31m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\033[01;31m║ -reversedns \x1b[90m- \x1b[0mFind DNS of an IPv4\033[01;31m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\033[01;31m║ -asnlookup \x1b[90m- \x1b[0mFind ASN of an IPv4 \033[01;31m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\033[01;31m║ -traceroute \x1b[90m- \x1b[0mTraceroute On IPv4 \033[01;31m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\033[01;31m║ -subnetcalc \x1b[90m- \x1b[0mCalculate A Subnet \033[01;31m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\033[01;31m║ -whois \x1b[90m- \x1b[0mWHOIS Search            \033[01;31m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\033[01;31m║ -zonetransfer \x1b[90m- \x1b[0mShows ZT         \033[01;31m║\x1b[0m\r\n"))
			this.conn.Write([]byte("\033[01;31m╚══════════════════════════════════╝\x1b[0m\r\n"))
            continue
        }

            if err != nil || cmd == "-IPLOOKUP" || cmd == "-iplookup" {
            this.conn.Write([]byte("\x1b[1;33mIPv4\033[01;31m: \x1b[0m"))
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
            this.conn.Write([]byte("\x1b[1;33mResults\033[01;31m: \r\n\033[01;31m" + locformatted + "\x1b[0m\r\n"))
        }

        if err != nil || cmd == "-PORTSCAN" || cmd == "-portscan" {                  
            this.conn.Write([]byte("\x1b[1;33mIPv4\033[01;31m: \x1b[0m"))
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
            this.conn.Write([]byte("\x1b[1;33mResults\033[01;31m: \r\n\033[01;31m" + locformatted + "\x1b[0m\r\n"))
        }

            if err != nil || cmd == "-WHOIS" || cmd == "-whois" {
            this.conn.Write([]byte("\x1b[1;33mIPv4\033[01;31m: \x1b[0m"))
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
            this.conn.Write([]byte("\x1b[1;33mResults\033[01;31m: \r\n\033[01;31m" + locformatted + "\x1b[0m\r\n"))
        }

            if err != nil || cmd == "-PING" || cmd == "-ping" {
            this.conn.Write([]byte("\x1b[1;33mIPv4\033[01;31m: \x1b[0m"))
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
            this.conn.Write([]byte("\x1b[1;33mResponse\033[01;31m: \r\n\033[01;31m" + locformatted + "\x1b[0m\r\n"))
        }

        if err != nil || cmd == "-traceroute" || cmd == "-TRACEROUTE" {                  
            this.conn.Write([]byte("\x1b[1;33mIPv4\033[01;31m: \x1b[0m"))
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
            this.conn.Write([]byte("\x1b[1;33mResults\033[01;31m: \r\n\033[01;31m" + locformatted + "\x1b[0m\r\n"))
        }

        if err != nil || cmd == "-resolve" || cmd == "-RESOLVE" {                  
            this.conn.Write([]byte("\x1b[1;33mURL (Without www.)\033[01;31m: \x1b[0m"))
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
            this.conn.Write([]byte("\x1b[1;33mResult\033[01;31m: \r\n\033[01;31m" + locformatted + "\x1b[0m\r\n"))
        }

            if err != nil || cmd == "-reversedns" || cmd == "-REVERSEDNS" {
            this.conn.Write([]byte("\x1b[1;33mIPv4\033[01;31m: \x1b[0m"))
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
            this.conn.Write([]byte("\x1b[1;33mResult\033[01;31m: \r\n\033[01;31m" + locformatted + "\x1b[0m\r\n"))
        }

            if err != nil || cmd == "-asnlookup" || cmd == "-asnlookup" {
            this.conn.Write([]byte("\x1b[1;33mIPv4\033[01;31m: \x1b[0m"))
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
            this.conn.Write([]byte("\x1b[1;33mResult\033[01;31m: \r\n\033[01;31m" + locformatted + "\x1b[0m\r\n"))
        }

            if err != nil || cmd == "-subnetcalc" || cmd == "-SUBNETCALC" {
            this.conn.Write([]byte("\x1b[1;33mIPv4\033[01;31m: \x1b[0m"))
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
            this.conn.Write([]byte("\x1b[1;33mResult\033[01;31m: \r\n\033[01;31m" + locformatted + "\x1b[0m\r\n"))
        }

            if err != nil || cmd == "-zonetransfer" || cmd == "-ZONETRANSFER" {
            this.conn.Write([]byte("\x1b[1;33mIPv4 Or Website (Without www.)\033[01;31m: \x1b[0m"))
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
            this.conn.Write([]byte("\x1b[1;33mResult\033[01;31m: \r\n\033[01;31m" + locformatted + "\x1b[0m\r\n"))
        }