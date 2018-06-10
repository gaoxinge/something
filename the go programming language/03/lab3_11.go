package main

import (
    "fmt"
    "strings"
)

func main() {
    fmt.Printf(comma("-123457890.0123456789"))
}

func comma(s string) string {
    left_index := 0
    if s[0] == '+' || s[0] == '-' {
        left_index = 1
    }
    
    right_index := strings.Index(s, ".")
    if right_index == -1 {
        right_index = len(s)
    }
    
    return s[:left_index] + 
           integer_comma(s[left_index:right_index]) + 
           s[right_index:]
}

func integer_comma(s string) string {
    n := len(s)
    if n <= 3 {
        return s
    }
    return integer_comma(s[:n-3]) + "," + s[n-3:]
}