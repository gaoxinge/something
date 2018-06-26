package main

import (
    "fmt"
    "crypto/sha256"
)

var pc [256]byte

func init() {
    for i := range pc {
        pc[i] = pc[i/2] + byte(i&1)
    }
}

func diff_sha(b1 []byte, b2 []byte) int {
    c1 := sha256.Sum256(b1)
    c2 := sha256.Sum256(b2)
    
    count := 0
    for i := 0; i < 32; i++ {
        count += int(pc[c1[i] ^ c2[i]])
    }
    return count
}

func main() {
    fmt.Println(diff_sha([]byte("x"), []byte("X")));
}