package main

import (
    "unsafe"
    "fmt"
)


var x struct {
    a bool
    b int16
    c []int
}

func main() {
    fmt.Println(unsafe.Sizeof(x),   unsafe.Alignof(x))
    fmt.Println(unsafe.Sizeof(x.a), unsafe.Alignof(x.a), unsafe.Offsetof(x.a))
    fmt.Println(unsafe.Sizeof(x.b), unsafe.Alignof(x.b), unsafe.Offsetof(x.b))
    fmt.Println(unsafe.Sizeof(x.c), unsafe.Alignof(x.c), unsafe.Offsetof(x.c))
    
    pb := (*int16) (unsafe.Pointer(
        uintptr(unsafe.Pointer(&x)) + unsafe.Offsetof(x.b)))
    *pb = 42
    fmt.Println(x.b)
}