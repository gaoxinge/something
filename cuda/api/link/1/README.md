- [Cuda C - Linker error - undefined reference](https://stackoverflow.com/questions/13553015/cuda-c-linker-error-undefined-reference)
- [错误：undefined reference to `__gxx_personality_v0' .](https://blog.csdn.net/tsaiyong_ahnselina/article/details/21198779)

```
> nvcc -o my_cuda.o -c my_cuda.cu
> gcc -I /usc/local/cuda/include -o main.o -c main.c
> gcc -L /usr/local/cuda/lib64 -o main main.o my_cuda.o -lcuda -lcudart -lstdc++
> ./main
```