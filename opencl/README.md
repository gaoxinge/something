# opencl

## introduction

### prerequisite

- check `OpenCL.dll` in `C:/Windows/System32`
- install msys2

### hello world

```
> pacman -S mingw-w64-x86_64-opencl-headers
> git clone https://github.com/arkanis/minimal-opencl-on-windows.git
> cd minimal-opencl-on-windows
> gcc -o main main.c /c/Windows/System32/OpenCL.dll
> ./main
in:  Khoor#Zruog$
out: Hello World!
```

### caution

- Because `clCreateCommandQueue` is deprecated, compiler will raise a warning. And you can solve this by the [answer](https://stackoverflow.com/a/28500846/5772365).
- Becase `kernel cannot be called 'main'`, running `main.exe` will fail. And you can solve this by renaming the name.

## A Gentle Introduction to OpenCL

- [1](http://www.drdobbs.com/parallel/a-gentle-introduction-to-opencl/231002854)
- [2](http://www.drdobbs.com/parallel/a-gentle-introduction-to-opencl/231002854?pgno=2)
- [3](http://www.drdobbs.com/parallel/a-gentle-introduction-to-opencl/231002854?pgno=3)

### code

- [add_numbers](https://github.com/gaoxinge/something/tree/master/opencl/A%20Gentle%20Introduction%20to%20OpenCL/add_numbers)

## anteru blog for opencl

- [anteru blog for opencl](https://anteru.net/blog/tags/opencl/)

### code

- [2](https://github.com/gaoxinge/something/tree/master/opencl/anteru%20blog%20for%20opencl/2)

## api

- [api](https://www.khronos.org/registry/OpenCL/)

### code

- [platform](https://github.com/gaoxinge/something/tree/master/opencl/api/platform)
- [device](https://github.com/gaoxinge/something/tree/master/opencl/api/device)
- [context](https://github.com/gaoxinge/something/tree/master/opencl/api/context)

## Hands On OpenCL

- [Hands On OpenCL](http://handsonopencl.github.io/)