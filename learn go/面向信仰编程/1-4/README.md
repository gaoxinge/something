# 中间代码生成

## 流程

- [ssa初始化](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/main.go#L696-L699)
- [ast处理](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/main.go#L707-L718)
- [ast到ssa](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/main.go#L724)

## ssa初始化

- [initssaconfig](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/ssa.go#L39)

## ast处理

- [funccompile](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/pgen.go#L197)
- [walk](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/walk.go#L20)
- [make](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/builtin/runtime.go#L117-L151)

## ast到ssa

- [compileFunctions](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/pgen.go#L337)
- [compileSSA](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/pgen.go#L297)