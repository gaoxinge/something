# 词法和语法分析

## token

- [src/cmd/compile/internal/syntax/tokens.go](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/tokens.go)

## grammar

- [language specification](https://golang.org/ref/spec)

## ast

- [src/cmd/compile/internal/syntax/nodes.go](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/nodes.go)

## 流程

- [Main](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/main.go#L132)调用[parseFiles](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/main.go#L511)
- [parseFiles](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/noder.go#L27)调用[syntax.Parse](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/noder.go#L52)
- [Parse](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/syntax.go#L58)调用[p.fileOrNil](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/syntax.go#L72)

## parser

- [src/cmd/compile/internal/syntax/parser.go](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/parser.go)
- 主要方法
  - [fileOrNil](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/parser.go#L352)
    - [Package](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/parser.go#L360)
    - [importDecl](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/parser.go#L373)
    - [constDecl](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/parser.go#L382)
    - [typeDecl](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/parser.go#L386)
    - [varDecl](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/parser.go#L390)
    - [funcDecl](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/parser.go#L394)
  - [funcDeclOrNil](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/parser.go#L591)
    - [name](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/parser.go#L618)
    - [funcType](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/parser.go#L619)
    - [funcDeclOrNil](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/parser.go#L621)
- 辅助方法
  - [got](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/parser.go#L158)
  - [want](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/parser.go#L166)
  - [appendGroup](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/parser.go#L469)

## scanner

- [src/cmd/compile/internal/syntax/scanner.go](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/scanner.go)
- 主要方法
  - [next](https://github.com/golang/go/blob/master/src/cmd/compile/internal/syntax/scanner.go#L83)