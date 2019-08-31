```
> nvcc -o cuda_math.o -c cuda_math.cu
> gcc -I /usr/local/cuda/include -o main.o -c main.c
> gcc -L /usr/local/cuda/lib64 -o main main.o cuda_math.o -lcuda -lcudart -lstdc++
> ./main
2.000000
```