package main

import "fmt"

func main() {
	a := [...]int{1, 2, 3}
	b := &a

	fmt.Printf("%T\n", a)
	fmt.Printf("%T\n", b)
}