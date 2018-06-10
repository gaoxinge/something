# the go programming language

- [01](https://github.com/gaoxinge/something/tree/master/the%20go%20programming%20language/01)
- [02](https://github.com/gaoxinge/something/tree/master/the%20go%20programming%20language/02)

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
