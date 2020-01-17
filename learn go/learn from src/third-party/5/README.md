# bouk/monkey

- [Monkey Patching in Go](https://bou.ke/blog/monkey-patching-in-go/)

## what is it

[bouk/monkey](https://github.com/bouk/monkey) provides a monkey patch to replace function in golang.

## how it work

The package replaces the function code in text section.

### objdump

- `go tool compile -S main.go > main.s`
- `go tool compile -l -S main.go > main.s`
- `go tool objdump main.o > main.tmp`
- `go build -o main main.go`
- `go build -gcflags '-N -l' -o main main.go`
- `objdump -d main > main.tmp`

#### reference

- [Go反汇编工具](https://github.com/cch123/asmshare/blob/master/layout.md#go-%E5%8F%8D%E6%B1%87%E7%BC%96%E5%B7%A5%E5%85%B7)
- [Command compile](https://godoc.org/cmd/compile)
- [Passing an optimization flag to a Go compiler?](https://stackoverflow.com/questions/45003259/passing-an-optimization-flag-to-a-go-compiler)

### observation

#### 1

```go
package main

func f() int {
    return 1
}

func main() {
    print(f())
}
```

```
000000000044ea70 <main.f>:
  44ea70:	48 c7 44 24 08 00 00 	movq   $0x0,0x8(%rsp)
  44ea77:	00 00 
  44ea79:	48 c7 44 24 08 01 00 	movq   $0x1,0x8(%rsp)
  44ea80:	00 00 
  44ea82:	c3                   	retq   
  44ea83:	cc                   	int3   
  44ea84:	cc                   	int3   
  44ea85:	cc                   	int3   
  44ea86:	cc                   	int3   
  44ea87:	cc                   	int3   
  44ea88:	cc                   	int3   
  44ea89:	cc                   	int3   
  44ea8a:	cc                   	int3   
  44ea8b:	cc                   	int3   
  44ea8c:	cc                   	int3   
  44ea8d:	cc                   	int3   
  44ea8e:	cc                   	int3   
  44ea8f:	cc                   	int3   

000000000044ea90 <main.main>:
  44ea90:	64 48 8b 0c 25 f8 ff 	mov    %fs:0xfffffffffffffff8,%rcx
  44ea97:	ff ff 
  44ea99:	48 3b 61 10          	cmp    0x10(%rcx),%rsp
  44ea9d:	76 3e                	jbe    44eadd <main.main+0x4d>
  44ea9f:	48 83 ec 18          	sub    $0x18,%rsp
  44eaa3:	48 89 6c 24 10       	mov    %rbp,0x10(%rsp)
  44eaa8:	48 8d 6c 24 10       	lea    0x10(%rsp),%rbp
  44eaad:	e8 be ff ff ff       	callq  44ea70 <main.f>
  44eab2:	48 8b 04 24          	mov    (%rsp),%rax
  44eab6:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  44eabb:	e8 00 41 fd ff       	callq  422bc0 <runtime.printlock>
  44eac0:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  44eac5:	48 89 04 24          	mov    %rax,(%rsp)
  44eac9:	e8 62 48 fd ff       	callq  423330 <runtime.printint>
  44eace:	e8 6d 41 fd ff       	callq  422c40 <runtime.printunlock>
  44ead3:	48 8b 6c 24 10       	mov    0x10(%rsp),%rbp
  44ead8:	48 83 c4 18          	add    $0x18,%rsp
  44eadc:	c3                   	retq   
  44eadd:	e8 0e 83 ff ff       	callq  446df0 <runtime.morestack_noctxt>
  44eae2:	eb ac                	jmp    44ea90 <main.main>
  44eae4:	cc                   	int3   
  44eae5:	cc                   	int3   
  44eae6:	cc                   	int3   
  44eae7:	cc                   	int3   
  44eae8:	cc                   	int3   
  44eae9:	cc                   	int3   
  44eaea:	cc                   	int3   
  44eaeb:	cc                   	int3   
  44eaec:	cc                   	int3   
  44eaed:	cc                   	int3   
  44eaee:	cc                   	int3   
  44eaef:	cc                   	int3   
```

#### 2

```go
package main

import (
  "fmt"
  "unsafe"
)

func a() int { 
    return 1 
}

func main() {
    f := a
    fmt.Printf("0x%x\n", *(*uintptr)(unsafe.Pointer(&f)))  // 0x4bcdc0
}
```

```
0000000000486540 <main.a>:
  486540:	48 c7 44 24 08 00 00 	movq   $0x0,0x8(%rsp)
  486547:	00 00 
  486549:	48 c7 44 24 08 01 00 	movq   $0x1,0x8(%rsp)
  486550:	00 00 
  486552:	c3                   	retq   
  486553:	cc                   	int3   
  486554:	cc                   	int3   
  486555:	cc                   	int3   
  486556:	cc                   	int3   
  486557:	cc                   	int3   
  486558:	cc                   	int3   
  486559:	cc                   	int3   
  48655a:	cc                   	int3   
  48655b:	cc                   	int3   
  48655c:	cc                   	int3   
  48655d:	cc                   	int3   
  48655e:	cc                   	int3   
  48655f:	cc                   	int3   

0000000000486560 <main.main>:
  486560:	64 48 8b 0c 25 f8 ff 	mov    %fs:0xfffffffffffffff8,%rcx
  486567:	ff ff 
  486569:	48 8d 44 24 f0       	lea    -0x10(%rsp),%rax
  48656e:	48 3b 41 10          	cmp    0x10(%rcx),%rax
  486572:	0f 86 f8 00 00 00    	jbe    486670 <main.main+0x110>
  486578:	48 81 ec 90 00 00 00 	sub    $0x90,%rsp
  48657f:	48 89 ac 24 88 00 00 	mov    %rbp,0x88(%rsp)
  486586:	00 
  486587:	48 8d ac 24 88 00 00 	lea    0x88(%rsp),%rbp
  48658e:	00 
  48658f:	48 8d 05 2a 68 03 00 	lea    0x3682a(%rip),%rax        # 4bcdc0 <go.func.*+0x75>
  486596:	48 89 44 24 40       	mov    %rax,0x40(%rsp)
  48659b:	0f 57 c0             	xorps  %xmm0,%xmm0
  48659e:	0f 11 44 24 60       	movups %xmm0,0x60(%rsp)
  4865a3:	48 8d 44 24 60       	lea    0x60(%rsp),%rax
  4865a8:	48 89 44 24 48       	mov    %rax,0x48(%rsp)
  4865ad:	48 8d 44 24 40       	lea    0x40(%rsp),%rax
  4865b2:	84 00                	test   %al,(%rax)
  4865b4:	48 8b 44 24 40       	mov    0x40(%rsp),%rax
  4865b9:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  4865be:	48 8d 05 db 04 01 00 	lea    0x104db(%rip),%rax        # 496aa0 <type.*+0xfaa0>
  4865c5:	48 89 04 24          	mov    %rax,(%rsp)
  4865c9:	e8 82 22 f8 ff       	callq  408850 <runtime.convT2E64>
  4865ce:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  4865d3:	48 8b 4c 24 10       	mov    0x10(%rsp),%rcx
  4865d8:	48 89 4c 24 50       	mov    %rcx,0x50(%rsp)
  4865dd:	48 89 44 24 58       	mov    %rax,0x58(%rsp)
  4865e2:	48 8b 54 24 48       	mov    0x48(%rsp),%rdx
  4865e7:	84 02                	test   %al,(%rdx)
  4865e9:	48 89 0a             	mov    %rcx,(%rdx)
  4865ec:	48 8d 7a 08          	lea    0x8(%rdx),%rdi
  4865f0:	83 3d b9 3a 0e 00 00 	cmpl   $0x0,0xe3ab9(%rip)        # 56a0b0 <runtime.writeBarrier>
  4865f7:	74 02                	je     4865fb <main.main+0x9b>
  4865f9:	eb 6e                	jmp    486669 <main.main+0x109>
  4865fb:	48 89 42 08          	mov    %rax,0x8(%rdx)
  4865ff:	eb 00                	jmp    486601 <main.main+0xa1>
  486601:	48 8b 44 24 48       	mov    0x48(%rsp),%rax
  486606:	84 00                	test   %al,(%rax)
  486608:	eb 00                	jmp    48660a <main.main+0xaa>
  48660a:	48 89 44 24 70       	mov    %rax,0x70(%rsp)
  48660f:	48 c7 44 24 78 01 00 	movq   $0x1,0x78(%rsp)
  486616:	00 00 
  486618:	48 c7 84 24 80 00 00 	movq   $0x1,0x80(%rsp)
  48661f:	00 01 00 00 00 
  486624:	48 8d 05 47 f9 02 00 	lea    0x2f947(%rip),%rax        # 4b5f72 <go.string.*+0x252>
  48662b:	48 89 04 24          	mov    %rax,(%rsp)
  48662f:	48 c7 44 24 08 05 00 	movq   $0x5,0x8(%rsp)
  486636:	00 00 
  486638:	48 8b 44 24 70       	mov    0x70(%rsp),%rax
  48663d:	48 89 44 24 10       	mov    %rax,0x10(%rsp)
  486642:	48 c7 44 24 18 01 00 	movq   $0x1,0x18(%rsp)
  486649:	00 00 
  48664b:	48 c7 44 24 20 01 00 	movq   $0x1,0x20(%rsp)
  486652:	00 00 
  486654:	e8 07 7e ff ff       	callq  47e460 <fmt.Printf>
  486659:	48 8b ac 24 88 00 00 	mov    0x88(%rsp),%rbp
  486660:	00 
  486661:	48 81 c4 90 00 00 00 	add    $0x90,%rsp
  486668:	c3                   	retq   
  486669:	e8 22 a2 fc ff       	callq  450890 <runtime.gcWriteBarrier>
  48666e:	eb 91                	jmp    486601 <main.main+0xa1>
  486670:	e8 0b 84 fc ff       	callq  44ea80 <runtime.morestack_noctxt>
  486675:	e9 e6 fe ff ff       	jmpq   486560 <main.main>
  48667a:	cc                   	int3   
  48667b:	cc                   	int3   
  48667c:	cc                   	int3   
  48667d:	cc                   	int3   
  48667e:	cc                   	int3   
  48667f:	cc                   	int3   
```

- `0x4bcdc0` is an address that points to the address of funtion

#### 3

```go
package main
 
import (
    "fmt"
    "unsafe"
)
 
func a() int { 
    return 1 
}
 
func main() {
    f := a
    fmt.Printf("0x%x\n", **(**uintptr)(unsafe.Pointer(&f)))  // 0x486540
}
```

```
0000000000486540 <main.a>:
  486540:	48 c7 44 24 08 00 00 	movq   $0x0,0x8(%rsp)
  486547:	00 00 
  486549:	48 c7 44 24 08 01 00 	movq   $0x1,0x8(%rsp)
  486550:	00 00 
  486552:	c3                   	retq   
  486553:	cc                   	int3   
  486554:	cc                   	int3   
  486555:	cc                   	int3   
  486556:	cc                   	int3   
  486557:	cc                   	int3   
  486558:	cc                   	int3   
  486559:	cc                   	int3   
  48655a:	cc                   	int3   
  48655b:	cc                   	int3   
  48655c:	cc                   	int3   
  48655d:	cc                   	int3   
  48655e:	cc                   	int3   
  48655f:	cc                   	int3   

0000000000486560 <main.main>:
  486560:	64 48 8b 0c 25 f8 ff 	mov    %fs:0xfffffffffffffff8,%rcx
  486567:	ff ff 
  486569:	48 8d 44 24 f0       	lea    -0x10(%rsp),%rax
  48656e:	48 3b 41 10          	cmp    0x10(%rcx),%rax
  486572:	0f 86 fd 00 00 00    	jbe    486675 <main.main+0x115>
  486578:	48 81 ec 90 00 00 00 	sub    $0x90,%rsp
  48657f:	48 89 ac 24 88 00 00 	mov    %rbp,0x88(%rsp)
  486586:	00 
  486587:	48 8d ac 24 88 00 00 	lea    0x88(%rsp),%rbp
  48658e:	00 
  48658f:	48 8d 05 2a 68 03 00 	lea    0x3682a(%rip),%rax        # 4bcdc0 <go.func.*+0x75>
  486596:	48 89 44 24 40       	mov    %rax,0x40(%rsp)
  48659b:	0f 57 c0             	xorps  %xmm0,%xmm0
  48659e:	0f 11 44 24 60       	movups %xmm0,0x60(%rsp)
  4865a3:	48 8d 44 24 60       	lea    0x60(%rsp),%rax
  4865a8:	48 89 44 24 48       	mov    %rax,0x48(%rsp)
  4865ad:	48 8b 44 24 40       	mov    0x40(%rsp),%rax
  4865b2:	84 00                	test   %al,(%rax)
  4865b4:	48 8d 4c 24 40       	lea    0x40(%rsp),%rcx
  4865b9:	84 01                	test   %al,(%rcx)
  4865bb:	48 8b 00             	mov    (%rax),%rax
  4865be:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  4865c3:	48 8d 05 d6 04 01 00 	lea    0x104d6(%rip),%rax        # 496aa0 <type.*+0xfaa0>
  4865ca:	48 89 04 24          	mov    %rax,(%rsp)
  4865ce:	e8 7d 22 f8 ff       	callq  408850 <runtime.convT2E64>
  4865d3:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  4865d8:	48 8b 4c 24 10       	mov    0x10(%rsp),%rcx
  4865dd:	48 89 4c 24 50       	mov    %rcx,0x50(%rsp)
  4865e2:	48 89 44 24 58       	mov    %rax,0x58(%rsp)
  4865e7:	48 8b 54 24 48       	mov    0x48(%rsp),%rdx
  4865ec:	84 02                	test   %al,(%rdx)
  4865ee:	48 89 0a             	mov    %rcx,(%rdx)
  4865f1:	48 8d 7a 08          	lea    0x8(%rdx),%rdi
  4865f5:	83 3d b4 3a 0e 00 00 	cmpl   $0x0,0xe3ab4(%rip)        # 56a0b0 <runtime.writeBarrier>
  4865fc:	74 02                	je     486600 <main.main+0xa0>
  4865fe:	eb 6e                	jmp    48666e <main.main+0x10e>
  486600:	48 89 42 08          	mov    %rax,0x8(%rdx)
  486604:	eb 00                	jmp    486606 <main.main+0xa6>
  486606:	48 8b 44 24 48       	mov    0x48(%rsp),%rax
  48660b:	84 00                	test   %al,(%rax)
  48660d:	eb 00                	jmp    48660f <main.main+0xaf>
  48660f:	48 89 44 24 70       	mov    %rax,0x70(%rsp)
  486614:	48 c7 44 24 78 01 00 	movq   $0x1,0x78(%rsp)
  48661b:	00 00 
  48661d:	48 c7 84 24 80 00 00 	movq   $0x1,0x80(%rsp)
  486624:	00 01 00 00 00 
  486629:	48 8d 05 42 f9 02 00 	lea    0x2f942(%rip),%rax        # 4b5f72 <go.string.*+0x252>
  486630:	48 89 04 24          	mov    %rax,(%rsp)
  486634:	48 c7 44 24 08 05 00 	movq   $0x5,0x8(%rsp)
  48663b:	00 00 
  48663d:	48 8b 44 24 70       	mov    0x70(%rsp),%rax
  486642:	48 89 44 24 10       	mov    %rax,0x10(%rsp)
  486647:	48 c7 44 24 18 01 00 	movq   $0x1,0x18(%rsp)
  48664e:	00 00 
  486650:	48 c7 44 24 20 01 00 	movq   $0x1,0x20(%rsp)
  486657:	00 00 
  486659:	e8 02 7e ff ff       	callq  47e460 <fmt.Printf>
  48665e:	48 8b ac 24 88 00 00 	mov    0x88(%rsp),%rbp
  486665:	00 
  486666:	48 81 c4 90 00 00 00 	add    $0x90,%rsp
  48666d:	c3                   	retq   
  48666e:	e8 1d a2 fc ff       	callq  450890 <runtime.gcWriteBarrier>
  486673:	eb 91                	jmp    486606 <main.main+0xa6>
  486675:	e8 06 84 fc ff       	callq  44ea80 <runtime.morestack_noctxt>
  48667a:	e9 e1 fe ff ff       	jmpq   486560 <main.main>
  48667f:	cc                   	int3   
```

- `0x486540` is an address that points to the function

## advices

- I don't recommend to use this `bouk/monkey` package because it is unsafe.
- The idea, behind the go version monkey patch, also can be applied to the c version. 