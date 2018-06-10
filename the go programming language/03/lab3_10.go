package main

import (
    "fmt"
    "bytes"
)

func main() {
    fmt.Printf(comma("12345"))
}

func comma(s string) string {
    var buf bytes.Buffer
    for i, _ := range(s) {
        buf.WriteString(s[i:i+1])
        tmp := len(s) - i - 1
        if tmp != 0 && tmp % 3 == 0 {
            buf.WriteString(",")
        }
    }
    return buf.String()
}