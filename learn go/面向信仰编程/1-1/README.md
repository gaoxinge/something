# 概述

## [src/cmd/compile/main.go](https://github.com/golang/go/blob/master/src/cmd/compile/main.go)

- 注册机器码生成的格式（https://github.com/golang/go/blob/581526ce963f54b01eef95d2a76ecb6fc08ed91c/src/cmd/compile/main.go#L24-L37）
- 编译器入口，主要调用[internal.gc.Main](https://github.com/golang/go/blob/master/src/cmd/compile/main.go#L51)

## [src/cmd/compile/internal](https://github.com/golang/go/tree/master/src/cmd/compile/internal)

- 包含机器码的格式
  - amd64
  - arm
  - arm64
  - mips
  - mips64
  - ppc64
  - s390x
  - wasm
  - x86
- 其他
  - gc
  - ssa
  - syntax
  - test
  - types  

## [src/cmd/compile/internal/gc/main.go](https://github.com/golang/go/blob/master/src/cmd/compile/main.go)

- [parseFiles](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/main.go#L511)：进行词法分析和语法分析得到AST
- [Phase 1: const, type, and names and types of funcs.](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/main.go#L523)
- [Phase 2: Variable assignments.](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/main.go#L540)
- [Phase 3: Type check function bodies.](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/main.go#L552)
- [Phase 4: Decide how to capture closed variables.](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/main.go#L583)
- [Phase 5: Inlining](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/main.go#L583)
- [Phase 6: Escape analysis.](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/main.go#L634)
- [Phase 7: Transform closure bodies to properly reference captured variables.](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/main.go#L653)
- [Phase 8: Compile top level functions.](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/main.go#L675)
- [Phase 9: Check external declarations.](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/main.go#L710)