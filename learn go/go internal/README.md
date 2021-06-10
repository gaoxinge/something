# go internal

## compile

- [Go程序是怎样跑起来的](https://zhuanlan.zhihu.com/p/71993748)
- [Go compiler internals: adding a new statement to Go - Part 1](https://eli.thegreenplace.net/2019/go-compiler-internals-adding-a-new-statement-to-go-part-1/)
- [Go compiler internals: adding a new statement to Go - Part 2](https://eli.thegreenplace.net/2019/go-compiler-internals-adding-a-new-statement-to-go-part-2/)

## plan9

```shell
go tool compile -S main.go
go tool compile -S -N -l main.go
go tool objdump main.o
```

```shell
go build main.go
go build -gcflags '-N -l' main.go
objdump -d main.exe
```

## runtime

- [runtime.go](https://github.com/golang/go/blob/master/src/runtime/runtime.go)
- [runtime1.go](https://github.com/golang/go/blob/master/src/runtime/runtime1.go)
- [runtime2.go](https://github.com/golang/go/blob/master/src/runtime/runtime2.go)

## memory management

### term

- stack: native stack, can expanse and shrink
- heap: native heap
- escape analysis: compiler decide whether a variable, like on stack, should allocate on heap
- garbage collect

### escaple analysis

- small object allocate on stack, big object allocate on heap
- non pointer object allocate on stack, pointer object allocate on heap
  - `&int`, `&struct{}`: better than `new`
  - `new`
- `slice`, `map`, `channel`
  - `make`: better than `new`
  - by reference
- life cycle
  - if function return non pointer object, compiler allocate it on the callee stack, and caller get a copy of it on the caller stack
  - if function return pointer object, compiler allocate it's real object on the heap, and caller get a copy of it on the caller stack

### reference

- [图解TCMalloc](https://zhuanlan.zhihu.com/p/29216091)
- [Memory Management in Go](https://dougrichardson.org/2016/01/23/go-memory-allocations.html)
- [Are all the variables in Go allocated on heap?](https://stackoverflow.com/questions/31786937/are-all-the-variables-in-go-allocated-on-heap)
- [Stack vs heap allocation of structs in Go, and how they relate to garbage collection](https://stackoverflow.com/questions/10866195/stack-vs-heap-allocation-of-structs-in-go-and-how-they-relate-to-garbage-collec)
- [Go的变量到底在堆还是栈中分配](http://www.zenlife.tk/go-allocated-on-heap-or-stack.md)

## garbage collect

### term

- 引用计数
- 可达性分析
  - 三色标记法（golang）

### reference

- [垃圾回收概念](https://zhuanlan.zhihu.com/p/297177002)
- [Golang垃圾回收 屏障技术](https://zhuanlan.zhihu.com/p/74853110)
- [Golang 垃圾回收](https://zhuanlan.zhihu.com/p/255199380)

## goroutine

### GMP model

- g: goroutine
- m: thread
- p: scheduler
  - local queue + work stealing (golang)
  - global queue + work sharing

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

### memory model

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

### golang协程和java线程的区别

- 内存区域不同
  - golang协程运行在native stack上
  - java线程运行在java stack（native heap）上
- 调度不同
  - golang协程调度基于GMP模型。使用time.Sleep或socket产生io阻塞时，对应的goroutine会被挂起，线程就可以去调度其他goroutine了。 
  - java线程调度基于操作系统对线程的调度。对标golang，java中相同的概念是reactor pattern，对应的是nio + thread/netty。
- 线程同步/内存模型略有不同
  - golang
    - channel
    - 锁和信号量
    - waitgroup
    - atomic
    - select
  - java
    - 锁和信号量
    - join
    - atomic

### golang协程和python协程的区别

- 有栈/无栈的不同
  - golang是有栈协程
  - python是无栈协程

### reference

- [Golang的goroutine是如何实现的？](https://www.zhihu.com/question/20862617)
- [Head First of Golang Scheduler](https://zhuanlan.zhihu.com/p/42057783)
- [How Stacks are Handled in Go](https://blog.cloudflare.com/how-stacks-are-handled-in-go/)
- [深入理解Golang Channel](https://zhuanlan.zhihu.com/p/27917262)
- [doc: define how sync/atomic interacts with memory model](https://github.com/golang/go/issues/5045)
- [Do atomic operations in golang establish a happen-before relation?](https://stackoverflow.com/questions/42231153/do-atomic-operations-in-golang-establish-a-happen-before-relation)
- [The Go Memory Model](https://golang.org/ref/mem)
- [GoLang内存模型](https://zhuanlan.zhihu.com/p/58164064)
- [Go’s Memory Model](http://nil.csail.mit.edu/6.824/2016/notes/gomem.pdf)
- [system-pclub/go-concurrency-bugs](https://github.com/system-pclub/go-concurrency-bugs)

## defer, panic, recover

### compile

- defer: deferproc
- return: deferreturn
- panic: gopanic
- recover: gorecover

### runtime

- [panic.go](https://github.com/golang/go/blob/master/src/runtime/panic.go)

### conclusion

```
goroutine
 |
 V
f1 -> defer1 -> defer in defer1 -> defer in defer in defer1
 |
 V
f2
 |
 V
f3
```

- 所有操作都在同一个goroutine中
- f1，f2，f3是函数的调用链
- defer1，defer in defer1，defer in defer in defer2是defer链
- 如果f3中发生了panic
  - 如果defer1中有recover，那么可以cover住
  - 如果defer1中没有recover，那么不可以cover住

## other

- empty value: `var x type`，`new`
- nonempty value: `make`

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

## style guide

- [uber-go/guide](https://github.com/uber-go/guide/blob/master/style.md)
- [golang-standards/project-layout](https://github.com/golang-standards/project-layout)

## interview

- [golang 面试题](https://zhuanlan.zhihu.com/p/26972862)
- [golang面试笔试题(第二版)](https://zhuanlan.zhihu.com/p/35058068)
- [Golang面试题解析](https://blog.csdn.net/weiyuefei/article/details/77963810)
- [Go语言面试精选](https://www.zhihu.com/column/c_1347495366519119872)

## internal datatype

### map

- [深度解密Go语言之 map](https://zhuanlan.zhihu.com/p/66676224)
- [直观、可视化的理解Golang Map](https://zhuanlan.zhihu.com/p/137382646)

