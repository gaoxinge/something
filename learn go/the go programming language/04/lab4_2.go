package main

import (
    "os"
    "fmt"
    "crypto/sha256"
    "crypto/sha512"
)

func main() {
    if len(os.Args) == 1 {
        c1 := sha256.Sum256([]byte("x"))
        c2 := sha256.Sum256([]byte("X"))
        fmt.Printf("%x\n%x\n", c1, c2);
    } else if os.Args[1] == "256" {
        c1 := sha256.Sum256([]byte("x"))
        c2 := sha256.Sum256([]byte("X"))
        fmt.Printf("%x\n%x\n", c1, c2);
    } else if os.Args[1] == "512" {
        c1 := sha512.Sum512([]byte("x"))
        c2 := sha512.Sum512([]byte("X"))
        fmt.Printf("%x\n%x\n", c1, c2);
    }
}