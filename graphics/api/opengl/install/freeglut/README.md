# freeglut

## mingw + binary

### prerequisite

- check `opengl32.dll` and `glu32.dll` in `C:/Windows/System32`
- install `msys2`

### hello world

```
$ pacman -S mingw-w64-x86_64-freeglut
$ git clone https://github.com/TransmissionZero/Hello-GLUT.git
$ cd Hello-GLUT/
$ cd HelloGLUT/
$ gcc -o main HelloGLUT.c Callbacks.c -lopengl32 -lglu32 -lfreeglut
$ ./main
```

### reference

- [Using GCC (MinGW) to compile OpenGL on Windows](https://stackoverflow.com/questions/2568067/using-gcc-mingw-to-compile-opengl-on-windows)

