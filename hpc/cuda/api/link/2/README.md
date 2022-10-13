## run

```
> nvcc -o vector.o -c vector.cu
> nvcc -o main.o -c main.c
> nvcc -o main main.o vector.o
> ./main
3
3
3
3
3
3
3
3
3
3
```

```
> nvcc -o vector.o -c vector.cu
> gcc -I /usr/local/cuda/include -o main.o -c main.c
> gcc -L /usr/local/cuda/lib64 -o main main.o vector.o -lcuda -lcudart -lstdc++
> ./main
3
3
3
3
3
3
3
3
3
3
```

## reference

- [Compiling and Linking pure C and CUDA code [warning: implicit declaration of function]](https://stackoverflow.com/questions/30247592/compiling-and-linking-pure-c-and-cuda-code-warning-implicit-declaration-of-fun)

