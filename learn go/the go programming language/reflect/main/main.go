package main

import (
    "fmt"
    "reflect"
)

type Student struct {
    name string
}

// both Student, *Student have this method
// you can call
// Student.String() and (*Stuedent).String()
func (this Student) String() string {
    return "I'm " + this.name
}

type Teacher struct {
    name string 
}

// only *Teacher have this method
// you can call
// (*Teacher).String()
// also you can call
// Teacher.String()
// because compile will convert it to
// (&Teacher).String()
func (this *Teacher) String() string {
    return "I'm " + this.name
}

func main() {
    gaoxinge1 := &Student{"gaoxinge"}     // stringer, *Student
    fmt.Println(gaoxinge1)                // I'm gaoxinge
    
    gaoxinge2 := Student{"gaoxinge"}      // stringer, Student
    fmt.Println(gaoxinge2)                // I'm gaoxinge
    
    gaoxinge3 := &Teacher{"gaoxinge"}     // stringer, *Teacher
    fmt.Println(gaoxinge3)                // I'm gaoxinge
    
    gaoxinge4 := Teacher{"gaoxinge"}      // not stringer, Teacher
    fmt.Println(gaoxinge4)                // {gaoxinge}, strange enough
    fmt.Println(gaoxinge4.String())       // I'm gaoxinge
    fmt.Println(&gaoxinge4)               // I'm gaoxinge
    
    
    /*
       variable           = type + value
       interface variable = interface type + interface value
       interface value    = variable type  + variable value
     */
    
    
    var gaoxinge5 interface{}
    gaoxinge5 = Teacher{"gaoxinge"}        // not stringer, Teacher
    // fmt.Println(gaoxinge5.String())     // error, not stringer 
    
    var gaoxinge6 interface{}
    gaoxinge6 = &Teacher{"gaoxinge"}       // stringer
    // fmt.Println(gaoxinge6.String())     // error, not stringer
    
    t1 := reflect.TypeOf(gaoxinge1)
    t2 := reflect.TypeOf(gaoxinge2)
    t3 := reflect.TypeOf(gaoxinge3)
    t4 := reflect.TypeOf(gaoxinge4)
    t5 := reflect.TypeOf(gaoxinge5)
    fmt.Println(t1, t2, t3, t4, t5)
    
    
    fmt.Println(f(gaoxinge1), f(gaoxinge2), f(gaoxinge3), f(gaoxinge4), f(gaoxinge5), f(gaoxinge6))  // 1 1 1 -1 -1 1
    fmt.Println(g(gaoxinge1), g(gaoxinge2), g(gaoxinge3), g(gaoxinge4), g(gaoxinge5), g(gaoxinge6))  // -1 1 -1 -1 -1 -1
    fmt.Println(h(gaoxinge1), h(gaoxinge2), h(gaoxinge3), h(gaoxinge4), h(gaoxinge5), h(gaoxinge6))  // 1 -1 -1 -1 -1 -1
    fmt.Println(u(gaoxinge1), u(gaoxinge2), u(gaoxinge3), u(gaoxinge4), u(gaoxinge5), u(gaoxinge6))  // -1 -1 -1 1 1 -1
    fmt.Println(v(gaoxinge1), v(gaoxinge2), v(gaoxinge3), v(gaoxinge4), v(gaoxinge5), v(gaoxinge6))  // -1 -1 1 -1 -1 1
}

func f(x interface{}) int {
    switch x.(type) {
        case fmt.Stringer:
            return 1
        default:
            return -1
    }
}

func g(x interface{}) int {
    switch x.(type) {
        case Student:
            return 1
        default:
            return -1
    }
}

func h(x interface{}) int {
    switch x.(type) {
        case *Student:
            return 1
        default:
            return -1
    }
}

func u(x interface{}) int {
    switch x.(type) {
        case Teacher:
            return 1
        default:
            return -1
    }
}

func v(x interface{}) int {
    switch x.(type) {
        case *Teacher:
            return 1
        default:
            return -1
    }
}