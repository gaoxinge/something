package main

import (
	"fmt"
	"reflect"
)

type A struct {
	name string
}

func main() {
	x := A{"gaoxinge"}

	// law1
	a := reflect.TypeOf(x)
	b := reflect.ValueOf(x)

	fmt.Println(a, a.Kind(), a.Kind() == reflect.Struct)

	fmt.Println(b.Type())
	fmt.Println(b, b.Kind(), b.Kind() == reflect.Struct)

	// law2
	fmt.Println(b.Interface())

	// law3
	y := 3.4
	v := reflect.ValueOf(y)
	fmt.Println(v.CanSet())

	y = 3.4
	p := reflect.ValueOf(&y)
	fmt.Println(p.CanSet())

	y = 3.4
	p = reflect.ValueOf(&y)
	v = p.Elem()
	fmt.Println(v.CanSet())
	v.SetFloat(7.1)
	fmt.Println(y)
}
