# go internal

## interview

- [golang 面试题](https://zhuanlan.zhihu.com/p/26972862)
- [golang面试笔试题(第二版)](https://zhuanlan.zhihu.com/p/35058068)
- [Golang面试题解析](https://blog.csdn.net/weiyuefei/article/details/77963810)

## style guide

- [x] [uber-go/guide](https://github.com/uber-go/guide/blob/master/style.md)
- [x] [golang-standards/project-layout](https://github.com/golang-standards/project-layout)

## compile

- [x] [Go程序是怎样跑起来的](https://zhuanlan.zhihu.com/p/71993748)
- [x] [Go compiler internals: adding a new statement to Go - Part 1](https://eli.thegreenplace.net/2019/go-compiler-internals-adding-a-new-statement-to-go-part-1/)
- [x] [Go compiler internals: adding a new statement to Go - Part 2](https://eli.thegreenplace.net/2019/go-compiler-internals-adding-a-new-statement-to-go-part-2/)

## generic

- [Go2GenericsFeedback](https://github.com/golang/go/wiki/Go2GenericsFeedback)
- [cosmos72/gomacro](https://github.com/cosmos72/gomacro)

## reflect

### method

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

### interface

- formula

```
variable           = type + value
interface variable = interface type + interface value
interface value    = variable type  + variable value 
```

- non nil interface: var ---> interface ---> interface ---> interface ---> ...

```
interface.(type)     = var type
_ = interface.(type) = var
```

- nil interface: nil ---> interface ---> interface ---> interface ---> ...

```
interface.(type)     = nil
_ = interface.(type) = nil
```

- [x] [Interfaces in Go (part I)](https://medium.com/golangspec/interfaces-in-go-part-i-4ae53a97479c)
- [x] [Interfaces in Go (part II)](https://medium.com/golangspec/interfaces-in-go-part-ii-d5057ffdb0a6)

### reflect

- [x] [Learning to Use Go Reflection](https://medium.com/capital-one-developers/learning-to-use-go-reflection-822a0aed74b7)
- [x] [Learning to Use Go Reflection — Part 2](https://medium.com/capital-one-developers/learning-to-use-go-reflection-part-2-c91657395066)
- [x] [The Laws of Reflection](https://blog.golang.org/laws-of-reflection)
- [x] [Reflection in Golang](http://blog.ralch.com/tutorial/golang-reflection/)

## runtime

- [runtime.go](https://github.com/golang/go/blob/master/src/runtime/runtime.go)
- [runtime1.go](https://github.com/golang/go/blob/master/src/runtime/runtime1.go)
- [runtime2.go](https://github.com/golang/go/blob/master/src/runtime/runtime2.go)

## goroutine

- [x] [Golang的goroutine是如何实现的？](https://www.zhihu.com/question/20862617)
- [x] [Head First of Golang Scheduler](https://zhuanlan.zhihu.com/p/42057783)
- [x] [How Stacks are Handled in Go](https://blog.cloudflare.com/how-stacks-are-handled-in-go/)
- [x] [深入理解Golang Channel](https://zhuanlan.zhihu.com/p/27917262)
- [x] [doc: define how sync/atomic interacts with memory model](https://github.com/golang/go/issues/5045)
- [x] [Do atomic operations in golang establish a happen-before relation?](https://stackoverflow.com/questions/42231153/do-atomic-operations-in-golang-establish-a-happen-before-relation)
- [x] [The Go Memory Model](https://golang.org/ref/mem)
- [x] [GoLang内存模型](https://zhuanlan.zhihu.com/p/58164064)
- [x] [Go’s Memory Model](http://nil.csail.mit.edu/6.824/2016/notes/gomem.pdf)
- [x] [system-pclub/go-concurrency-bugs](https://github.com/system-pclub/go-concurrency-bugs)

### term

- green thread: corresponding to compiler, not os
- light weight threads: corresponding to user space, not core space

### conclusion

- don't consider how go compiler transfer go program to exe
- don't consider how go compiler implement bootstrap
- big picture1: m-p-g model
  - m: thread
  - p: scheduler
  - g: goroutine
  - local queue for scheduler + work stealing
  - global queue for scheduler + work sharing

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

## memory management

- [x] [图解TCMalloc](https://zhuanlan.zhihu.com/p/29216091)
- [x] [Memory Management in Go](https://dougrichardson.org/2016/01/23/go-memory-allocations.html)
- [x] [Are all the variables in Go allocated on heap?](https://stackoverflow.com/questions/31786937/are-all-the-variables-in-go-allocated-on-heap)
- [x] [Stack vs heap allocation of structs in Go, and how they relate to garbage collection](https://stackoverflow.com/questions/10866195/stack-vs-heap-allocation-of-structs-in-go-and-how-they-relate-to-garbage-collec)
- [x] [Go的变量到底在堆还是栈中分配](http://www.zenlife.tk/go-allocated-on-heap-or-stack.md)

### term

- stack
- heap
- escape analysis
- garbage collector

### conclusion

- `new` often allocates objects on heap, but not always
- if function return a local variable, compiler will allocate the local variable on the stask and caller will get a copy of the return value
- if function return a pointer to a local variable, compiler will allocate the local variable on the heap and caller will get the copy of the pointer
- `slice`, `map`, `channel`
  - `make`: may be better than `new`
  - pass by reference
  - allocate on the stack or on the heap

## defer, panic, recover

### compile

- defer: deferproc
- return: deferreturn
- panic: gopanic
- recover: gorecover

### runtime

- [panic.go](https://github.com/golang/go/blob/master/src/runtime/panic.go)

## other

- empty value: `var x type`，`new`
- nonempty value: `make`