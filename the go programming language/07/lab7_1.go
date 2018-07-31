package main

import (
    "bufio"
    "fmt"
    "strings"
)

type WordCounter int
type LineCounter int


func (c *WordCounter) Write(p []byte) (int, error) {
    s := string(p)
    scanner := bufio.NewScanner(strings.NewReader(s))
    scanner.Split(bufio.ScanWords)
    
    t := 0
    for scanner.Scan() {
        t += 1
    }
    *c += WordCounter(t)
    
    return t, nil
}

func (c *LineCounter) Write(p []byte) (int, error) {
    s := string(p)
    scanner := bufio.NewScanner(strings.NewReader(s))
    scanner.Split(bufio.ScanLines)
    
    t := 0
    for scanner.Scan() {
        t += 1
    }
    *c += LineCounter(t)
    return t, nil 
}

func main() {
    name := "Dolly"

    var c WordCounter
    c.Write([]byte("hello world"))
    fmt.Println(c)
    
    c = 0
    fmt.Fprintf(&c, "hello world %s", name)
    fmt.Println(c)
    
    var l LineCounter
    l.Write([]byte("hello\nworld"))
    fmt.Println(l)
    
    l = 0
    fmt.Fprintf(&l, "hello\nworld\n%s", name)
    fmt.Println(l)
}