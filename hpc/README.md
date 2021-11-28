# hpc

- [simd](./simd)

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

## mpi / openmp

- [windows下利用Mingw和msmpi编译运行mpi并行程序](https://blog.csdn.net/xenonhu/article/details/78196443)
- [MinGW coding under Windows(C, C++, OpenMP, MPI)](https://www.math.ucla.edu/~wotaoyin/windows_coding.html)

### run mpi

```c
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "mpi.h"

int main(int argc, char **argv) {
    int myid, numprocs, namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Get_processor_name(processor_name, &namelen);
    printf("Hello World! Process %d of %d on %s\n", myid, numprocs, processor_name);
    MPI_Finalize();
}
```

```
$ gcc -o hello hello.c -l msmpi -L "/d/Microsoft SDKs/MPI/Lib/x64" -I "/d/Microsoft SDKs/MPI/Include"
$ mpiexec -n 4 hello
```

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
