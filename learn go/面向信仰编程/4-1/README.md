# for 和 range

## 永不停止的循环

```go
func main() {
    arr := []int{1, 2, 3}
    for _, v := range arr {
        arr = append(arr, v)
    }
    fmt.Println(arr)
}

$ go run main.go
1 2 3 1 2 3
```

- 循环会先去计算arr的长度，根据长度确认循环的次数

## 神奇的指针

```go
func main() {
    arr := []int{1, 2, 3}
    newArr := []*int{}
    for _, v := range arr {
        newArr = append(newArr, &v)
    }
    for _, v := range newArr {
        fmt.Println(*v)
    }
}

$ go run main.go
3 3 3
```

- 循环的变量是arr中元素的拷贝

## 遍历清空数组

```go
func main() {
    arr := []int{1, 2, 3}
    for i, _ := range arr {
        arr[i] = 0
    }
}
```

- [How to use the copy function](https://yourbasic.org/golang/copy-explained/)
- [Is there analog of memset in go?](https://stackoverflow.com/questions/30614165/is-there-analog-of-memset-in-go)