#include "Python.h"
#include <stdio.h>

// wrong
static PyObject *f1(PyObject *self, PyObject *args) {
    printf("%s\n", PyString_AsString(args));
    Py_RETURN_NONE;
}

static PyObject *f2(PyObject *self, PyObject *args) {
    PyObject *o;
    if (!PyArg_ParseTuple(args, "O", &o)) return NULL;
    printf("%s\n", PyString_AsString(o));
    Py_RETURN_NONE;
}

// wrong
static PyObject *g1(PyObject *self, PyObject *args) {
    printf("%s\n", PyString_AsString(args + 1));
    Py_RETURN_NONE;
}

static PyObject *g2(PyObject *self, PyObject *args) {
    PyObject *o;
    if (!PyArg_ParseTuple(args, "|O", &o)) return NULL;
    printf("%s\n", PyString_AsString(o));
    Py_RETURN_NONE;
}

static PyMethodDef methods[] = {
    {"f1", (PyCFunction) f1, METH_VARARGS},
    {"f2", (PyCFunction) f2, METH_VARARGS},
    {"g1", (PyCFunction) g1, METH_VARARGS},
    {"g2", (PyCFunction) g2, METH_VARARGS},
    {NULL}
};

void initfoo() {
    Py_InitModule("foo", methods);
}