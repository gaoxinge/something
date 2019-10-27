## 1.3.1 数组

- go的数组和数组指针对应的类型包含了数组的长度，参见[main.go](./main.go)

## 1.3.2 字符串

```go
type StringHeader struct {
    Data uintptr
    Len  int
}
```

- `string`, `[]byte`, `[]rune`的转化，参见[main1.go](./main1.go)

## 1.3.3 切片

```go
type SliceHeader struct {
    Data uintptr
    Len  int
    Cap  int
}
```

- [SliceTricks](https://github.com/golang/go/wiki/SliceTricks)