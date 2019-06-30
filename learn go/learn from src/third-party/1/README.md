# smasher164/mem

## what is it

`smasher164/mem` provides `mem.Alloc` and `mem.Free` to simulate `malloc` and `free` in C. And its source codes' structure is 

- map_unix.go
- map_windows.go
- mem.go
- mem_test.go

The first three is included in the package `mem`, and the last one is included in the package `mem_test`. 

## how it work

### conditional build

`map_unix.go` and `map_windows.go` wrap the interface of `mmap` and `munmap` respectively. So the build depends on the os platform, and we can use `conditional build` to handle this.

- examples
  - [os]()
  - [debug]()
- reference
  - [Can i have custom build flags like os/arch comment directives](https://stackoverflow.com/questions/47253852/can-i-have-custom-build-flags-like-os-arch-comment-directives)
  - [C-style conditional compilation in golang](https://stackoverflow.com/questions/38950909/c-style-conditional-compilation-in-golang)
  - [Golang conditional compilation](https://stackoverflow.com/questions/10646531/golang-conditional-compilation)
  
  
### golang.org/x/sys

[golang.org/x/sys](https://github.com/golang/sys) provides the low-level interactions with the operating system. And

- `map_unix.go` uses the package `golang.org/x/sys/unix`
- `map_windows.go` uses the package `golang.org/x/sys/windows`

## advices

I don't recommend to use this `smasher164/mem` package because

- Don't use `golang.org/x/sys` to interact with the operating system directly.
- Because GO has GC, don't manage memory by yourself.