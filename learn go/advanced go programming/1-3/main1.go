package main

import "fmt"

func main() {
	a := "世界abc"

	for i, c := range a {
		fmt.Println(i, c)
	}
	fmt.Println()

	for i, c := range []rune(a) {
		fmt.Println(i, c)
	}
	fmt.Println()

	for i, c := range []byte(a) {
		fmt.Println(i, c)
	}
	fmt.Println()

	for i := 0; i < len(a); i++ {
		fmt.Println(i, a[i])
	}
}