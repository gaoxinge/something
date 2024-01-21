# reference counting

## 引用

- `Py_INCREF`
- `Py_XINCREF`
- `Py_DECREF`
- `Py_XDECREF`

## new reference

### 调用者

#### 1

- 传入参数`a`，直到函数返回，函数`f`对`a`的引用权都不会改变
- 函数`f`对返回结果`b`拥有引用权

```c
PyObject *f(PyObject *a) {
    PyObject *b = g(a);
    // ...
}
```

#### 2

- 函数`f`对`new`的返回结果`a`拥有引用权
- 传入参数`a`，直到函数返回，函数`f`对`a`的引用权都不会改变
- 函数`f`对`g`返回结果`b`拥有引用权

```c
Pyobject *f() {
    PyObject *a = new();
    PyObject *b = g(a);
    // ...
}
```

### 被调用者

#### 1

- 使用或者解析参数中的`PyObject`，并没有拥有这个对象的引用
- 如果要获取这个参数中的`PyObject`的引用，需要使用`Py_INCREF`
- 直接返回这个参数中的`PyObject`

```c
PyObject *f(PyObject *a) {
    return a;
}
```

#### 2

- 通过调用函数返回的`PyObject`，拥有这个对象的引用
- 如果没有不返回这个`PyObject`，需要调用`Py_DECREF`

```c
PyObject *f() {
    PyObject *a = new();
    Py_DECREF(a);
    Py_RETURN_NONE;
}
```

#### 3

- 通过调用函数返回的`PyObject`，拥有这个对象的引用
- 直接返回这个`PyObject`，把这个对象的引用权交给了调用者

```c
PyObject *f() {
    PyObject *a = new();
    return a;
}
```

## stolen reference

- `PyTuple_SetItem`
- `PyList_SetItem`

## borrowed reference

- `PyTuple_GetItem`
- `PyList_GetItem`
- `PyList_GET_ITEM`
- `PyList_SET_ITEM`
- `PyDict_GetItem`
- `PyDict_GetItemString`
- `PyErr_Occurred`
- `PyFile_Name`
- `PyImport_GetModuleDict`
- `PyModule_GetDict`
- `PyImport_AddModule`
- `PyObject_Init`
- `Py_InitModule`
- `Py_InitModule3`
- `PySequence_Fast_GET_ITEM`
- `Py_InitModule4`