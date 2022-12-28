## cpp

### asm

One can use 

1. [compiler explorer](https://godbolt.org/) with `-O3`
2. `g++ -O3 -S -fverbose-asm main.c -o main.s` 

to generate asm.

### example

- [1](./cpp/1)
- [2](./cpp/2)

## rust

### llvm

One can use

1. `cargo rustc -- --emit=llvm-ir`, and `cat target/debug/deps/{project_name}-{hash}.ll`
2. [pacak/cargo-show-asm](https://github.com/pacak/cargo-show-asm)

### asm

One can use 

1. [compiler explorer](https://godbolt.org/) with `-C opt-level=3`
2. `cargo rustc -- --emit=asm`, and `cat target/debug/deps/{project_name}-{hash}.s`
3. [pacak/cargo-show-asm](https://github.com/pacak/cargo-show-asm)

to generate asm.
