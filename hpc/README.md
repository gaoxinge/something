# hpc

- [simd](./simd)
- [mpi](./mpi)

## HPC Carpentry

- [HPC Carpentry](https://github.com/hpc-carpentry)

## A Beginner’s Guide to High–Performance Computing

- [A Beginner’s Guide to High–Performance Computing](http://www.shodor.org/media/content/petascale/materials/UPModules/beginnersGuideHPC/moduleDocument_pdf.pdf)

### code

- [A Beginner’s Guide to High–Performance Computing](https://github.com/gaoxinge/something/tree/master/hpc/A%20Beginner%E2%80%99s%20Guide%20to%20High%E2%80%93Performance%20Computing)

## Introduction to High-Performance Scientific Computing

- [Introduction to High-Performance Scientific Computing](http://pages.tacc.utexas.edu/~eijkhout/istc/istc.html)

## 高性能计算从入门到放弃

- [高性能计算从入门到放弃](https://zhuanlan.zhihu.com/c_1058374280076652544)

## 3 数据并行模式

- [3 数据并行模式](https://zhuanlan.zhihu.com/p/81344648)

## parallelism

- [Data parallelism](https://en.wikipedia.org/wiki/Data_parallelism)
- [Task parallelism](https://en.wikipedia.org/wiki/Task_parallelism)

## openmp

- [MinGW coding under Windows(C, C++, OpenMP, MPI)](https://www.math.ucla.edu/~wotaoyin/windows_coding.html)

### run openmp

```c
#include <omp.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
    int nthreads, tid;

#pragma omp parallel private(nthreads, tid) 
    {
        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);

#pragma omp barrier
        if (tid == 0) {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
    }
}
```

```
$ gcc -fopenmp omp_hello.c -o omp_hello
$ ./omp_hello
```

## Intro to MPI Course Overview

- [Intro to MPI Course Overview](https://www.dartmouth.edu/~rc/classes/intro_mpi/index.html)

### code

- [Intro to MPI Course Overview](https://github.com/gaoxinge/something/tree/master/hpc/Intro%20to%20MPI%20Course%20Overview)
