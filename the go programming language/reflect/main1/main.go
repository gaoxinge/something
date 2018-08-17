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

func main() {
    t := Student{"gaoxinge"}
    
    var t1 fmt.Stringer
    t1 = t
    
    var t2 interface{}
    t2 = t1
    
    
    fmt.Println(reflect.TypeOf(t), reflect.TypeOf(t1), reflect.TypeOf(t2))  // Student
    fmt.Println(f(t), f(t1), f(t2)) // 1, 1, 1
    fmt.Println(g(t), g(t1), g(t2)) // 1, 1, 1
    fmt.Println(h(t), h(t1), h(t2)) // 1, 1, 1
}

func f(x interface{}) int {
    switch x.(type) {
        case Student:
            return 1
        default:
            return -1
    }
}

func g(x interface{}) int {
    switch x.(type) {
        case fmt.Stringer:
            return 1
        default:
            return -1
    }
}

func h(x interface{}) int {
    switch x.(type) {
        case fmt.Stringer:
            return 1
        default:
            return -1
    }
}
