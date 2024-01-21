# numpy

## code structure

- [include/numpy](https://github.com/numpy/numpy/tree/master/numpy/core/include/numpy)
- [src](https://github.com/numpy/numpy/tree/master/numpy/core/src)

## np.ndarray

### PyArrayObject

- [PyArray_Type](https://github.com/numpy/numpy/blob/master/numpy/core/src/multiarray/arrayobject.c#L1780)

```c
typedef struct tagPyArrayObject_fields {
    PyObject_HEAD
    char *data;
    int nd;
    npy_intp *dimensions;
    npy_intp *strides;
    PyArray_Descr *descr;
} PyArrayObject_fields;

typedef PyArrayObject_fields PyArrayObject;
```

```c
// wrap data
typedef struct {
    PyObject_HEAD
    PyObject *base;
    void *ptr;
    npy_intp len;
    int flags;
} PyArray_Chunk;
```

```c
// wrap dimensions and strides
typedef struct {
    npy_intp *ptr;
    int len;
} PyArray_Dims;
```

```c
typedef struct _PyArray_Descr {
    PyObject_HEAD
    PyTypeObject *typeobj;
    char kind;
    char type;
    char byteorder;
    char flags;
    int type_num;
    int elsize;
    int alignment;
    struct _arr_descr *subarray;
    PyObject *fields;
    PyObject *names;
    PyArray_ArrFuncs *f;
    PyObject *metadata;
    NpyAuxData *c_metadata;
    npy_hash_t hash;
} PyArray_Descr;
```

### np.array

- [_array_fromobject](https://github.com/numpy/numpy/blob/master/numpy/core/src/multiarray/multiarraymodule.c#L1575)
- [PyArray_CheckFromAny](https://github.com/numpy/numpy/blob/master/numpy/core/src/multiarray/ctors.c#L1974)
- [PyArray_FromAny](https://github.com/numpy/numpy/blob/master/numpy/core/src/multiarray/ctors.c#L1793)
- [PyArray_NewFromDescr](https://github.com/numpy/numpy/blob/master/numpy/core/src/multiarray/ctors.c#L1162)
- [PyArray_NewFromDescrAndBase](https://github.com/numpy/numpy/blob/master/numpy/core/src/multiarray/ctors.c#L1176)
- [PyArray_NewFromDescr_int](https://github.com/numpy/numpy/blob/master/numpy/core/src/multiarray/ctors.c#L909)

### _array_fill_strides

- [_array_fill_strides](https://github.com/numpy/numpy/blob/master/numpy/core/src/multiarray/ctors.c#L4011)

```c
NPY_NO_EXPORT void
_array_fill_strides(npy_intp *strides, npy_intp *dims, int nd, size_t itemsize,
                    int inflag, int *objflags)
{
    int i;

    /* Only make Fortran strides if not contiguous as well */
    if ((inflag & (NPY_ARRAY_F_CONTIGUOUS|NPY_ARRAY_C_CONTIGUOUS)) ==
                                            NPY_ARRAY_F_CONTIGUOUS) {
        // omit
    }
    else {
        for (i = nd - 1; i >= 0; i--) {
            strides[i] = itemsize;
            if (dims[i]) {
                itemsize *= dims[i];
            }
        }
    }
    return;
}
```

## architecture

### blas and lapack

- [Why BLAS Matters](http://markus-beuckelmann.de/blog/boosting-numpy-blas.html)
- [Benchmark OpenBLAS, Intel MKL vs ATLAS](https://github.com/tmolteno/necpp/issues/18)

```
sklearn ---> numpy / scipy ---> blas / lapack ---> openmp / opencl ---> os / hardware
```

### build from backend

- [Building from source](https://numpy.org/devdocs/user/building.html)
- [Compiling numpy with OpenBLAS integration](https://stackoverflow.com/questions/11443302/compiling-numpy-with-openblas-integration)
- [Building NumPy and SciPy with Intel MKL](https://www.elliottforney.com/blog/npspmkl/)
- [Installing Numpy and OpenBLAS](https://hunseblog.wordpress.com/2014/09/15/installing-numpy-and-openblas/)

### opencl

- [xianyi/clOpenBLAS](https://github.com/xianyi/clOpenBLAS)

### cuda

- [cupy/cupy](https://github.com/cupy/cupy)

### tensor

- [tensorly/tensorly](https://github.com/tensorly/tensorly)
- [mnick/scikit-tensor](https://github.com/mnick/scikit-tensor)

### other

- [scikit-learn/scikit-learn](https://github.com/scikit-learn/scikit-learn)
- [sympy/sympy](https://github.com/sympy/sympy)