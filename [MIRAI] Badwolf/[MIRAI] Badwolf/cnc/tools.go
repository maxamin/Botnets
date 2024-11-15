package main

import (
    "fmt"
    "net/http"
	"io/ioutil"
    "strings"
    "encoding/json"
    "log"
    )

func getNMAP(target string) string {
    response, err := http.Get("https://api.hackertarget.com/nmap/?q="+target)
    if err != nil {
        fmt.Printf("%s", err)
    } else {
        defer response.Body.Close()
        contents, err := ioutil.ReadAll(response.Body)
        if err != nil {
            fmt.Printf("%s", err)
        }
		
		responseString := string(contents)
		responseFormated := strings.Replace(responseString, "\n", "\r\n\033[1;92m", -1)
        return responseFormated
	}
	
	return ""
}

type geo struct {
    IP string `json:"ip"`
    ISP string `json:"isp"`
    ORG string `json:"org"`
    HOSTNAME string `json:hostname`
    COUNTRY string `json:country_name`
    CONTINENT_CODE string `"json:continent_code"`
    ASN string `"json:asn"`
}

func getGEO(target string) string{
    response, err := http.Get("https://json.geoiplookup.io/"+target)
    if err != nil{
        fmt.Printf("%s", err)
    }else{
        defer response.Body.Close()
        contents, err := ioutil.ReadAll(response.Body)
        if err != nil {
            fmt.Printf("%s", err)
        }

        jsonOut := geo{}
        jsonErr := json.Unmarshal(contents, &jsonOut)
        if jsonErr != nil {
            log.Fatal(jsonErr)
        }
        return "\033[1;92mIP : "+jsonOut.IP+"\r\n\033[1;92mISP : "+jsonOut.ISP+"\r\n\033[1;92mORG : "+jsonOut.ORG+"\r\n\033[1;92mHostname : "+jsonOut.HOSTNAME+"\r\n\033[1;92mCountry : "+jsonOut.COUNTRY+"\r\n\033[1;92mContinent :"+jsonOut.CONTINENT_CODE+"\r\n\033[1;92mASN : "+jsonOut.ASN+"\r\n\033[0;91m"
    }
    return ""
}