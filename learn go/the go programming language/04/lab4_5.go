package main

import "fmt"

func main() {
    strings1 := []string{"1", "2", "3"}    
    strings1 = noduplicate(strings1)
    fmt.Printf("%v, %d\n", strings1, len(strings1))
    
    strings2 := []string{"1", "2", "2"}
    strings2 = noduplicate(strings2)
    fmt.Printf("%v, %d\n", strings2, len(strings2))
    
    strings3 := []string{"1", "1", "3"}
    strings3 = noduplicate(strings3)
    fmt.Printf("%v, %d\n", strings3, len(strings3))
}

func noduplicate(strings []string) []string {
    if len(strings) == 0 || len(strings) == 1 {
        return strings
    }
    
    index := 1
    t     := strings[0]
    for i, s := range strings {
        if i == 0 {
            continue
        }
          
        if s != t {
            strings[index] = s
            index++
            t = s
        }
    }
    return strings[:index]
}