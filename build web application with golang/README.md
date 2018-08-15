# build web application with golang

## reference

- [build-web-application-with-golang](https://github.com/astaxie/build-web-application-with-golang/blob/master/zh/preface.md)

## 1.1

```
set GOROOT = D:\Go\
set GOPATH = D:\GoPath\
set PATH   =  %PATH%;%GOROOT%\bin;%GOPATH%\bin
```

## 2.2

```
var i int

var i int = 1
var i     = 1
    i    := 1
```

- number: 0 default
  - `int`
  - `int8`
  - `int16`
  - `int32`: `rune`
  - `int64`
  - `uint`
  - `uint8`: `byte`
  - `uint16`
  - `uint32`
  - `uint64`
  - `float32`
  - `float64`: default
  - `complex128`
- boolean: false default
  - `bool`
- string

```go
package main

import "fmt"

func main() {
    s := "中国"
    a := []byte(s)
    b := []rune(s)
    fmt.Println(a)
    fmt.Println(b)
}
```

- array

```
var a [10]int
a := [10]int{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
a := [...]int{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
```

- slice: reference type
  - pointer point to array
  - len
  - cap

```
var a []int
a := []int{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
a := make([]int, 10)
```

```go
package main

import "fmt"

func main() {
    var a []int                     // uninitialize, nil slice,   nil
    var b []int = []int{}           // initialize,   empty slice, zero
    var c []int = make([]int, 0)    // initialize,   empty slice, zero
    fmt.Println(a, len(a), a == nil)
    fmt.Println(b, len(b), b == nil)
    fmt.Println(c, len(c), c == nil)
}
```

- map

```
var a map[string]int
a := map[string]int{}
a := make(map[string]int)
```

```go
package main

import "fmt"

func main() {
    var a map[string]int                        // uninitialize, nil map,   nil
    var b map[string]int = map[string]int{}     // initialize,   empty slice, zero
    var c map[string]int = make(map[string]int) // initialize,   empty slice, zero
    // a["one"] = 1                             // panic
    b["one"] = 1
    c["one"] = 1
    fmt.Println(a, len(a), a == nil)
    fmt.Println(b, len(b), b == nil)
    fmt.Println(c, len(c), c == nil)
}
```

## 2.3

- if
- goto
- for
- switch
- select

### 函数

#### 函数作为值、类型

```go
package main

import "fmt"

func isOdd(integer int) bool {
	if integer%2 == 0 {
		return false
	}
	return true
}

func isEven(integer int) bool {
	if integer%2 == 0 {
		return true
	}
	return false
}

// 声明的函数类型在这个地方当做了一个参数

func filter(slice []int, f func(int) bool) []int {
	var result []int
	for _, value := range slice {
		if f(value) {
			result = append(result, value)
		}
	}
	return result
}

func main(){
	slice := []int {1, 2, 3, 4, 5, 7}
	fmt.Println("slice = ", slice)
	odd := filter(slice, isOdd)    // 函数当做值来传递了
	fmt.Println("Odd elements of slice are: ", odd)
	even := filter(slice, isEven)  // 函数当做值来传递了
	fmt.Println("Even elements of slice are: ", even)
}
```

## 2.4

## struct的匿名字段

```go
package main

import "fmt"

type Human struct {
    name string
    age int
    weight int
}

type Student struct {
    Human
    speciality string
}

func main(){
    // mark := Student{"Mark", 25, 120, "Computer Science"} // error
    mark := Student{Human{"Mark", 25, 120}, "Computer Science"}
    fmt.Println(mark.name)
}
```

```go
package main

import "fmt"

type Skills []string

type Human struct {
    name string
    age int
    weight int
}

type Student struct {
    Human
    Skills
    int
    speciality string
}

func main(){
    // mark := Student{Human: Human{"Mark", 25, 120}, Skills: {"1", "2"}, int: 1, speciality: "Computer Science"} error
    mark := Student{Human: Human{"Mark", 25, 120}, Skills: []string{"1", "2"}, int: 1, speciality: "Computer Science"}
    fmt.Println(mark.name)
    fmt.Println(mark.Skills)
    fmt.Println(mark.int)
    fmt.Println(mark.speciality)
}
```

## 2.6

### 空interface

```go
package main

import "fmt"

func main(){
    var a interface{}                  // empty interface, no value, nil
    var b interface{} = 5              // empty interface, value 5
    var c interface{} = "Hello World"  // empty interface, value hello world
    var d interface{} = nil            // empty interface, no value, nil
    fmt.Println(a, a == nil)
    fmt.Println(b, b == nil)
    fmt.Println(c, c == nil)
    fmt.Println(d, d == nil)
}
```

### 反射

```go
package main

import (
    "fmt"
    "reflect"
)

func main(){
    i := 1
    t := reflect.TypeOf(i)
    v := reflect.ValueOf(i)
    fmt.Println(t, v)
    
    var a interface{} = "hello world"
    t = reflect.TypeOf(a)
    v = reflect.ValueOf(a)
    fmt.Println(t, v)
    
    var x float64 = 3.4
    v = reflect.ValueOf(x)
    fmt.Println("type:", v.Type())
    fmt.Println("kind i float64:", v.Kind() == reflect.Float64)
    fmt.Println("value:", v.Float())
    p := reflect.ValueOf(&x)
    v = p.Elem()
    v.SetFloat(7.1)
    fmt.Println(x)
}
```