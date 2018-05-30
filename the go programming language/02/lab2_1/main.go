package main

import (
    "fmt"
    "./tempconv"
)

func main() {
    fmt.Printf("Brrr! %v\n", tempconv.AbsoluteZeroC)
    fmt.Println(tempconv.CToF(tempconv.BoilingC))
    fmt.Println(tempconv.CToK(tempconv.FreezingC))
}