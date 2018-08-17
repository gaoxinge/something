package main

import (
    "fmt"
    "reflect"
)

type Student struct {
    name string
}

func (this Student) String() string {
    return this.name
}

// https://stackoverflow.com/questions/18306151/in-go-which-value-s-kind-is-reflect-interface
func main() {
    t := Student{"gaoxinge"}
    
    var t1 fmt.Stringer
    t1 = t
    
    var t2 interface{}
    t2 = t1
    
    fmt.Println(reflect.TypeOf(t), reflect.TypeOf(t1), reflect.TypeOf(t2))
    
    a := reflect.ValueOf(t)
    b := reflect.ValueOf(t1)
    c := reflect.ValueOf(t2)
    
    fmt.Println(a, a.Type(), a.Kind())
    fmt.Println(b, b.Type(), b.Kind())
    fmt.Println(c, c.Type(), c.Kind())
}