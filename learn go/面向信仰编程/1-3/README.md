# 类型检查

## 流程

[Main](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/main.go#L533-L560) ---> [typecheck](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/typecheck.go#L295) ---> [typecheck1](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/typecheck.go#L322)


## typecheck1

- [OTARRAY](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/typecheck.go#L403-L456)
- [OTMAP](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/typecheck.go#L458-L478)
- [OTCHAN](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/typecheck.go#L480-L494)
- [OMAKE](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/typecheck.go#L1665-L1774)
  - [TSLICE](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/typecheck.go#L1690-L1723)
  - [TMAP](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/typecheck.go#L1725-L1743)
  - [TCHAN](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/typecheck.go#L1745-L1774)
- [ONEW](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/typecheck.go#L1776-L1799)

## 设置类型

在完成类型推到后，一般会通过

- [setTypeNode](https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/typecheck.go#L3926-L3931)
- `n.Type = ...`

对Node设置类型