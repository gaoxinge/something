# the go programming language

- [01](https://github.com/gaoxinge/something/tree/master/the%20go%20programming%20language/01)
- [02](https://github.com/gaoxinge/something/tree/master/the%20go%20programming%20language/02)
- [03](https://github.com/gaoxinge/something/tree/master/the%20go%20programming%20language/03)
- [04](https://github.com/gaoxinge/something/tree/master/the%20go%20programming%20language/04)

## fmt

- [Golang学习-fmt包](http://www.cnblogs.com/golove/p/3286303.html)

## int to string

```go
package main

import (
    "fmt"
    "bytes"
    "strconv"
)

func main() {
    // integer to string
    i := 123
    
    s1 := strconv.FormatUint(uint64(i), 10)
    s2 := strconv.FormatInt(int64(i), 10)
    s3 := fmt.Sprintf("%d", i)
    
    var buf bytes.Buffer
    fmt.Fprintf(&buf, "%d", i)
    s4 := buf.String()
    
    fmt.Println(i, s1, s2, s3, s4);
}
```

## string to int

```go
package main

import (
    "fmt"
    "strconv"
)

func main() {
    // string to integer
    s := "123"
    x, _ := strconv.Atoi(s)
    y, _ := strconv.ParseInt(s, 10, 32)
    fmt.Println(s, x, y)
}
```

## array vs slice

```go
package main

import "fmt"

func main() {
    p := [...]int{1, 2, 3}
    fmt.Printf("%T\n", p)
    fmt.Println(p)
    
    q := []int{1, 2, 3}
    fmt.Printf("%T\n", q)
    fmt.Println(q)
}
```

```go
package main

import "fmt"

func main() {
    p := [...]int{1, 2, 3}
    fmt.Printf("%T\n", p)
    fmt.Println(p)
    
    reverse_array(p)
    fmt.Printf("%T\n", p)
    fmt.Println(p)
    
    reverse_ptr(&p)
    fmt.Printf("%T\n", p)
    fmt.Println(p)
    
    reverse_slice(p[:])
    fmt.Printf("%T\n", p)
    fmt.Println(p)
}

func reverse_array(array [3]int) {
    for i, j := 0, len(array)-1; i < j; i, j = i+1, j-1 {
        array[i], array[j] = array[j], array[i]
    }
}

func reverse_ptr(ptr *[3]int) {
    for i, j := 0, len(*ptr)-1; i < j; i, j = i+1, j-1 {
        ptr[i], ptr[j] = ptr[j], ptr[i]
    } 
}

func reverse_slice(s []int) {
    for i, j := 0, len(s)-1; i < j; i, j = i+1, j-1 {
        s[i], s[j] = s[j], s[i]
    }
}
```