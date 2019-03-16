// assignment ( var1 = var2 ) and function ( f(var) ) 
// in go are copy operations.
// if you want to make two variables share memory,
// or pass variable by reference, then you should
// use the pointer.

package main

import "fmt"

type A struct {
    i *int
    j int
}

func (a A) String() string {
    return fmt.Sprintf("A{*i=%d, *j=%d}", *(a.i), a.j)
}

func main() {
    // slice: slice2 is the copy of the slice1, 
    // but they share the same array by pointer
    slice1 := []int{1, 2, 3}
    slice2 := slice1
    slice2[0] = 0
    fmt.Println(slice1, slice2) // [0, 2, 3] [0, 2, 3]
    
    // map: map2 is the copy of the map1,
    // but they share the same entry array by pointer
    map1 := map[string]int{"a": 1, "b": 2, "c": 3}
    map2 := map1
    map2["a"] = 0
    fmt.Println(map1, map2) // map[a:0, b:2, c:3] map[a:0, b:2, c:3]
    
    // A: a2 is the copy of the a1,
    // and they share the int pointed by i, 
    // but they don't share the j
    i, j := 1, 1
    a1 := A{&i, j}
    a2 := a1
    *(a2.i), a2.j = 0, 0
    fmt.Println(a1, a2) // A{*i=0, j=1} A{*i=0, j=0}
}