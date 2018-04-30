package main

import (
    "fmt"
    "os"
    "strconv"
)

func main() {
    for temp, arg:= range os.Args[1:] {
        fmt.Println(strconv.Itoa(temp) + " " + arg)
    }
}