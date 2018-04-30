package main

import (
    "fmt"
    "os"
    "strings"
    "time"
)

func f1() {
    start := time.Now()
    var s, sep string
    for i := 1; i < len(os.Args); i++ {
        s += sep + os.Args[i]
        sep = " "
    }
    fmt.Println(s)
	secs := time.Since(start).Seconds()
	fmt.Println("elapsed: ", secs)
}

func f2() {
    start := time.Now()
    s, sep := "", ""
    for _, arg := range os.Args[1:] {
        s += sep + arg
        sep = " "
    }
	fmt.Println(s)
    secs := time.Since(start).Seconds()
	fmt.Println("elapsed: ", secs)
}

func f3() {
    start := time.Now()
    fmt.Println(strings.Join(os.Args[1:], " "))
    secs := time.Since(start).Seconds()
	fmt.Println("elapsed: ", secs)
}

func main() {
    f1()
    f2()
    f3()
}