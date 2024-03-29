# gcc

## gcc

### prerequisite

- check `OpenCL.dll` in `C:/Windows/System32`
- install msys2

### hello world

```
$ pacman -S mingw-w64-x86_64-opencl-headers
$ git clone https://github.com/arkanis/minimal-opencl-on-windows.git
$ cd minimal-opencl-on-windows
$ gcc -o main main.c /c/Windows/System32/OpenCL.dll
$ ./main
in:  Khoor#Zruog$
out: Hello World!
```

### caution

- Because `clCreateCommandQueue` is deprecated, compiler will raise a warning. And you can solve this by the [answer](https://stackoverflow.com/a/28500846/5772365).
- Becase `kernel cannot be called 'main'`, running `main.exe` will fail. And you can solve this by renaming the name.

## cmake

### install

```
$ cmake -B build/ -G "MinGW Makefiles"
$ cmake --build build/
$ ./build/main.exe
in:  Khoor#Zruog$
out: Hello World!
```
