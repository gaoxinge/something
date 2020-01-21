# maruel/panicparse

## what is it

[maruel/panicparse](https://github.com/maruel/panicparse) provides pretty print to stack trace for errors.

## how it work

### code structure

- `main.go`: `main`函数调用了`internal.Main`函数
- `internal`
  - `main.go`: `Main`函数调用了`process`函数，`process`函数先调用了`stack.ParseDump`，`stack.Augment`，`stack.Aggregate`，再调用了`writeToConsole`，`writeToHTML`
- `stack`
  - `stack.go`: 数据结构`Goroutine` -> `Signature` -> `Stack` -> `Call` -> `Func` + `Arg`
  - `context.go`: `ParseDump`
  - `source.go`: `Augment`
  - `bucket.go`: `Aggregate`
  
### workflow

- find the source code file
- parse source code file to ast