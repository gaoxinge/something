package main

import (
    "net"
    "os"
    "fmt"
    "io/ioutil"
)

func main() {
    if len(os.Args) != 2 {
        os.Exit(1)
    }
    service := os.Args[1]
    
    tcpAddr, err := net.ResolveTCPAddr("tcp", service)
    checkError(err)
    
    conn, err := net.DialTCP("tcp", nil, tcpAddr)
    checkError(err)
    
    _, err = conn.Write([]byte("GET / HTTP/1.1\r\nHost: www.sina.com.cn\r\nConnection: close\r\n\r\n"))
    
    result, err := ioutil.ReadAll(conn)
    checkError(err)
    
    fmt.Println(string(result))
    os.Exit(0)
}

func checkError(err error) {
    if err != nil {
        fmt.Fprintf(os.Stderr, "Fatal error: %s", err.Error())
        os.Exit(1)
    }
}