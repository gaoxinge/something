# the go programming language

- [01](https://github.com/gaoxinge/something/tree/master/the%20go%20programming%20language/01)
- [02](https://github.com/gaoxinge/something/tree/master/the%20go%20programming%20language/02)
- [03](https://github.com/gaoxinge/something/tree/master/the%20go%20programming%20language/03)
- [04](https://github.com/gaoxinge/something/tree/master/the%20go%20programming%20language/04)
- [06](https://github.com/gaoxinge/something/tree/master/the%20go%20programming%20language/06)
- [07](https://github.com/gaoxinge/something/tree/master/the%20go%20programming%20language/07)

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

## print array and slice

```go
package main

import "fmt"

func main() {
    p := [...]int{1, 2, 3}
    fmt.Printf("%T\n%q\n%v\n", p, p, p)
    fmt.Println(p)
    
    q := []int{1, 2, 3}
    fmt.Printf("%T\n%q\n%v\n", q, q, q)
    fmt.Println(q)
}
```

## slice

```go
package main

import "fmt"

func main() {
    x := []int{1, 2, 3}
    
    y := make([]int, 3, 3)
    copy(y, x)
    y[0] = 2
    
    fmt.Println(x)  // [1, 2, 3]
    fmt.Println(y)  // [2, 2, 3]
    
    var a, b []int
    b = append(a, 1)
    a = b
    b = append(a, 2)
    a = b
    b = append(a, 3)
    a = b
    b = append(a, 4)
    a = b
    
    b = append(a, 5)
    b[0] = 0
    fmt.Println(a)  // [1, 2, 3, 4]
    fmt.Println(b)  // [0, 2, 3, 4, 5]
    
    
    var u, v [] int
    v = append(u, 1)
    v[0] = 0
    fmt.Println(u)  // []
    fmt.Println(v)  // [0]
}
```

## struct and interface

```go
type person struct {
    name string
    age int
}

type geometry struct {
    area() float64
    perim() float64
}
```

- [Go by Example: Structs](https://gobyexample.com/structs)
- [Go by Example: Interfaces](https://gobyexample.com/interfaces)

## struct

```go
package main

import (
    "time"
    "fmt"
)


type Employee struct {
    ID        int
    Name      string
    Address   string
    DoB       time.Time
    Position  string
    Salary    int
    ManagerID int
}

var employees = map[int]Employee{} 

func EmployeeByID(id int) Employee {
    return employees[id]
}

func main() {
    var employee1 Employee
    employee1.ID = 1
    employee1.ManagerID = 0
    employees[employee1.ID] = employee1
    
    var employee2 Employee
    employee2.ID = 2
    employee2.ManagerID = 1
    employees[employee1.ID] = employee1
    
    // struct is not a reference type
    // EmployeeByID(1).Salary = 2000
    
    // employee is a copy of employee1
    // not a reference
    var employee = EmployeeByID(1)
    employee.Salary = 2000
    fmt.Println(employee1)
    fmt.Println(employee)
}
```

```go
package main

import (
    "time"
    "fmt"
)


type Employee struct {
    ID        int
    Name      string
    Address   string
    DoB       time.Time
    Position  string
    Salary    int
    ManagerID int
}

var employees = map[int]Employee{} 

func EmployeeByID(id int) *Employee {
    return &employees[id]  // error: element of map is not a variable
}

func main() {
    var employee1 Employee
    employee1.ID = 1
    employee1.ManagerID = 0
    employees[employee1.ID] = employee1
    
    var employee2 Employee
    employee2.ID = 2
    employee2.ManagerID = 1
    employees[employee1.ID] = employee1
    
    fmt.Println(EmployeeByID(1))
}
```

```go
package main

import (
    "time"
    "fmt"
)


type Employee struct {
    ID        int
    Name      string
    Address   string
    DoB       time.Time
    Position  string
    Salary    int
    ManagerID int
}

var employees = map[int]Employee{} 

func EmployeeByID(id int) *Employee {
    var employee = employees[id]  // a copy of struct
    return &employee
}

func main() {
    var employee1 Employee
    employee1.ID = 1
    employee1.ManagerID = 0
    employees[employee1.ID] = employee1
    
    var employee2 Employee
    employee2.ID = 2
    employee2.ManagerID = 1
    employees[employee1.ID] = employee1
    
    var employee = EmployeeByID(1)
    employee.Salary = 2000
    fmt.Println(employee1);
    fmt.Println(employee)
}
```

```go
package main

import (
    "time"
    "fmt"
)


type Employee struct {
    ID        int
    Name      string
    Address   string
    DoB       time.Time
    Position  string
    Salary    int
    ManagerID int
}

var employees = map[int]*Employee{} 

func EmployeeByID(id int) *Employee {
    return employees[id]
}

func main() {
    var employee1 Employee
    employee1.ID = 1
    employee1.ManagerID = 0
    employees[employee1.ID] = &employee1
    
    var employee2 Employee
    employee2.ID = 2
    employee2.ManagerID = 1
    employees[employee1.ID] = &employee1
    
    var employee = EmployeeByID(1)
    employee.Salary = 2000
    fmt.Println(employee1)
    fmt.Println(employee)
}
```

- [golang学习笔记之引用类型与值类型](https://blog.csdn.net/u010278923/article/details/69056018)
- [深入学习golang(4)—new与make](https://www.cnblogs.com/hustcat/p/4004889.html)

## method

```go
package main

import (
    "math"
    "fmt"
)

type Point struct{X, Y float64}

func Distance(p, q Point) float64 {
    return math.Hypot(q.X-p.X, q.Y-p.Y)
}

// error: there is conflict between nonpointer and pointer
func (p Point) Distance(q Point) float64 {
    return math.Hypot(q.X-p.X, q.Y-p.Y)
}

func (p *Point) Distance(q Point) float64 {
    return math.Hypot(q.X-p.X, q.Y-p.Y)
}

func main() {
    p := Point{1, 2}
    q := Point{4, 6}
    fmt.Println(Distance(p, q))
    fmt.Println(p.Distance(q))
}
```

## sort

```go
package main

import (
    "sort"
    "fmt"
)

func main() {
    a := []int{3, 2, 1}
    sort.Ints(a)
    fmt.Println(a)
    
    // error
    // a1 := [...]int{3, 2, 1}
    // sort.Ints(a1)
    // fmt.Println(a1)
    
    b := []string{"3", "2", "1"}
    sort.Strings(b)
    fmt.Println(b)
    
    // error
    // b1 := [...]string{"3", "2", "1"}
    // sort.Strings(b1)
    // fmt.Println(b1)
}
```