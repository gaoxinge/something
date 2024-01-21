#include <stdio.h>
#include "Python.h"

static PyObject *helloworld1(PyObject *self, PyObject *args) {
    printf("hello world\n");
    Py_RETURN_NONE;
}

static PyObject *helloworld2(PyObject *self, PyObject *args) {
    PyObject *s = PyUnicode_FromString("hello world\n");
    PyObject_Print(s, stdout, 1);
    Py_DECREF(s);
    Py_RETURN_NONE;
}

static PyObject *helloworld3(PyObject *self, PyObject *args) {
    PyObject *s = PyUnicode_FromFormat("%s", "hello world");
    PyObject_Print(s, stdout, 0);
    Py_DECREF(s);
    printf("\n");
    Py_RETURN_NONE;
}

static PyMethodDef methods[] = {
    {"helloworld1", helloworld1, METH_NOARGS},
    {"helloworld2", helloworld2, METH_NOARGS},
    {"helloworld3", helloworld3, METH_NOARGS},
    {NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "helloworld",
    NULL,
    -1,
    methods
};

PyMODINIT_FUNC PyInit_helloworld(void) {
    return PyModule_Create(&module);
}
