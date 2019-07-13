# hpc

## HPC Carpentry

- [HPC Carpentry](https://github.com/hpc-carpentry)

## A Beginner’s Guide to High–Performance Computing

- [A Beginner’s Guide to High–Performance Computing](http://www.shodor.org/media/content/petascale/materials/UPModules/beginnersGuideHPC/moduleDocument_pdf.pdf)

## parallelism

- [Data parallelism](https://en.wikipedia.org/wiki/Data_parallelism)
- [Task parallelism](https://en.wikipedia.org/wiki/Task_parallelism)

## mpi

- [windows下利用Mingw和msmpi编译运行mpi并行程序](https://blog.csdn.net/xenonhu/article/details/78196443)
- [MinGW coding under Windows(C, C++, OpenMP, MPI)](https://www.math.ucla.edu/~wotaoyin/windows_coding.html)

### run

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