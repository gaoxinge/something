package main

import (
	"reflect"
	"fmt"
)

type T struct {
	A int
	B string
}

func main() {
	t := T{23, "skidoo"}
	s := reflect.ValueOf(&t).Elem()
	typeOfT := s.Type()
	for i := 0; i < s.NumField(); i++ {
		f := s.Field(i)
		g := typeOfT.Field(i)
		fmt.Printf("%d: %s %s = %v\n", i, g.Name, f.Type(), f.Interface())
	}

	fmt.Println("old:", t)
	s.Field(0).SetInt(77)
	s.Field(1).SetString("Sunset Strip")
	fmt.Println("new:", t)
}