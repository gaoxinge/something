package main

import (
    "fmt"
    "sort"
    "strings"
)

func main() {
    fmt.Println(compare("123", "321"))
    fmt.Println(compare("123", "1234"))
}

func compare(s1 string, s2 string) bool {
    b1 := strings.Split(s1, "")
    b2 := strings.Split(s2, "")
    sort.Strings(b1)
    sort.Strings(b2)
    return strings.Join(b1, "") == strings.Join(b2, "")
}