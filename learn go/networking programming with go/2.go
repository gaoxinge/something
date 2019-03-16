package main

import (
    "net"
    "os"
    "fmt"
)

func main() {
    if len(os.Args) != 2 {
        fmt.Fprintf(os.Stderr, "Usage: %s ip-addr\n", os.Args[0])
        os.Exit(1)
    }
    
    name := os.Args[1]
    addr := net.ParseIP(name)
    if addr == nil {
        fmt.Println("Invalid address")
        os.Exit(1)
    }
    
    mask := addr.DefaultMask()
    network := addr.Mask(mask)
    ones, bits := mask.Size()
    fmt.Println(
        " Address is ",            addr.String(),
        "\nDefalt mask length is ", bits,
        "\nLeading ones count is ", ones,
        "\nMask is (hex) ",         mask.String(),
        "\nNetwork is ",            network.String())
    os.Exit(0)
}