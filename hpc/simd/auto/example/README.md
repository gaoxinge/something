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

## example

- [1](./rust/1)
- [2](./rust/2)

### reference

- [Mir optimization pass that implements auto-vectorization](https://internals.rust-lang.org/t/mir-optimization-pass-that-implements-auto-vectorization/16360/11)
- [Taking Advantage of Auto-Vectorization in Rust](https://www.nickwilcox.com/blog/autovec/)
- [Auto-Vectorization for Newer Instruction Sets in Rust](https://www.nickwilcox.com/blog/autovec2/)
