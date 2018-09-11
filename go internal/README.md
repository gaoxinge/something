## go internal

### interview

- [golang 面试题](https://zhuanlan.zhihu.com/p/26972862)
- [golang面试笔试题(第二版)](https://zhuanlan.zhihu.com/p/35058068)
- [Golang面试题解析](https://blog.csdn.net/weiyuefei/article/details/77963810)

### reflect

#### method

```go
package main

import "fmt"

type ChangeObject interface {
	Change(string)
}

type Student struct {
	name string
}

func (this Student) Change(name string) {
	fmt.Println(this)
	this.name = name
}

func main() {
	a := Student{"gaoxinge"}
	a.Change("123")  // {gaoxinge}
	fmt.Println(a)   // {gaoxinge}

	b := &Student{"gaoxinge"}
	b.Change("123")  // {gaoxinge}
	fmt.Println(b)   // &{gaoxinge}

	var c ChangeObject
	c = a
	fmt.Println(c)   // {gaoxinge}
	c = b
	fmt.Println(c)   // &{gaoxinge}
}
```

- `Student` can call `Change` directly
- `&Student` call `Change` by `*&Student.Change`
- both `Student` and `&Student` have `Change` method
- both `Student` and `&Student` are `ChangeObject`

```go
package main

import "fmt"

type Change2Object interface {
	Change2(string)
}

type Student struct {
	name string
}

func (this *Student) Change2(name string) {
	fmt.Println(this)
	this.name = name
}

func main() {
	a := Student{"gaoxinge"}
	a.Change2("123")  // &{gaoxinge}
	fmt.Println(a)    // {123}

	b := &Student{"gaoxinge"}
	b.Change2("123")  // {gaoxinge}
	fmt.Println(b)    // &{123}

	var c Change2Object
	// compile error
	// c = a
	// fmt.Println(c)
	c = b
	fmt.Println(c)    // &{123}
}
```

- `Student` call `Change2` by `&Student.Change`
- `*Student` call `Change2` directly
- only `*Student` has `Change2` method
- only `*Student` is `Change2Object`

#### interface

- formula

```
variable           = type + value
interface variable = interface type + interface value
interface value    = variable type  + variable value 
```

- nonempty interface: var ---> interface ---> interface ---> interface ---> ...

```
interface.(type)     = var type
_ = interface.(type) = var
```

- empty interface: nil ---> interface ---> interface ---> interface ---> ...

```
interface.(type)     = nil
_ = interface.(type) = nil
```

#### refelct

- [x] [The Laws of Reflection](https://blog.golang.org/laws-of-reflection)

### goroutine

- [x] [Golang的goroutine是如何实现的？](https://www.zhihu.com/question/20862617)
- [x] [Head First of Golang Scheduler](https://zhuanlan.zhihu.com/p/42057783)
- [x] [How Stacks are Handled in Go](https://blog.cloudflare.com/how-stacks-are-handled-in-go/)
- [x] [深入理解Golang Channel](https://zhuanlan.zhihu.com/p/27917262)

#### term

- green thread: corresponding to compiler, not os
- light weight threads: corresponding to user space, not core space

#### conclusion

- don't consider how go compiler transfer go program to exe
- don't consider how go comiler implement bootstrap
- big picture1: m-p-g model

```
 m                  m
 |                  |
 v                  v
 p ---> g           p ---> g
 |      |           |      |
 v      v           v      v
 g      g           g      g
        |                  |
        v                  v
        g                  g
```

- big picture2: memory model

```
                         -------------------
                         |process1|process2|
-------------------      -------------------
| gorout | gorout |      | gorout | gorout |
| stack1 | stack2 |      | stack1 | stack2 |
-------------------      -------------------
| gorout | gorout |      | gorout | gorout |
| stack3 | stack4 |      | stack3 | stack4 |
-------------------      -------------------
|     heap        |      |     heap        |
-------------------      -------------------
```

- go vs python
  - go
    - go func(), and start by compiler
    - io
    - system call
    - infinite loop
  - python
    - add func() into loop, and start by loop.run()
    - yield
    - yield sleep
    - yield io

### memory management

- [x] [图解TCMalloc](https://zhuanlan.zhihu.com/p/29216091)
- [x] [Memory Management in Go](https://dougrichardson.org/2016/01/23/go-memory-allocations.html)
- [x] [Are all the variables in Go allocated on heap?](https://stackoverflow.com/questions/31786937/are-all-the-variables-in-go-allocated-on-heap)
- [x] [Stack vs heap allocation of structs in Go, and how they relate to garbage collection](https://stackoverflow.com/questions/10866195/stack-vs-heap-allocation-of-structs-in-go-and-how-they-relate-to-garbage-collec)
- [x] [Go的变量到底在堆还是栈中分配](http://www.zenlife.tk/go-allocated-on-heap-or-stack.md)

#### term

- stack
- heap
- escape analysis
- garbage collector

#### conclusion

- `new` often allocates objects on heap, but not always
- if function return a local variable, compiler will allocate the local variable on the stask and caller will get a copy of the return value
- if function return a pointer to a local variable, compiler will allocate the local variable on the heap and caller will get the copy of the pointer
- `slice`, `map`, `channel`
  - `make`: may be better than `new`
  - pass by reference
  - allocate on the stack or on the heap