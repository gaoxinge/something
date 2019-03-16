package main 

import (
    "fmt"
)

type Student struct {
    ID int
    Name string
}

func (this *Student) String() string {
    return fmt.Sprintf("ID: %d, Name: %s", this.ID, this.Name)
}

func main() {
    a := &[3]int{}
    fmt.Println(a)
    
    b := &[]int{}
    fmt.Println(b)
    
    c := &map[int]int{}
    fmt.Println(c)

    student := &Student{ID: 1, Name: "gaoxinge"}
    fmt.Println(student)
}