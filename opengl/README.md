# opengl

## introduction

### prerequisite

- check `opengl32.dll` and `glu32.dll` in `C:/Windows/System32`
- install msys2

### hello world

```
> pacman -S mingw-w64-x86_64-freeglut
> git clone https://github.com/TransmissionZero/Hello-GLUT.git
> cd Hello-GLUT/
> cd HelloGLUT/
> gcc -o main HelloGLUT.c Callbacks.c -lopengl32 -lglu32 -lfreeglut
> ./main
```

### reference

- [Using GCC (MinGW) to compile OpenGL on Windows](https://stackoverflow.com/questions/2568067/using-gcc-mingw-to-compile-opengl-on-windows)

## OpenGL Programming Guide

- [Chapter 1](https://github.com/gaoxinge/something/tree/master/opengl/OpenGL%20Programming%20Guide/Chapter%201)
- [Chapter 2](https://github.com/gaoxinge/something/tree/master/opengl/OpenGL%20Programming%20Guide/Chapter%202)