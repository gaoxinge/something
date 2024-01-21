#include "Python.h"
#include <stdio.h>

static PyObject *f(PyObject *self, PyObject *args) {
    char *str;
    if (!PyArg_ParseTuple(args, "s", &str))
        return NULL;
    return Py_BuildValue("s", str);
}

static PyObject *g(PyObject *self, PyObject *args) {
    PyObject *o;
    if (!PyArg_ParseTuple(args, "O", &o))
        return NULL;
    printf("fuck reference count %d ", (int) Py_REFCNT(o));
    Py_INCREF(o);
    printf("fuck reference count %d\n", (int) Py_REFCNT(o));
    return o;
}

// wrong
static PyObject *h(PyObject *self, PyObject *args) {
    PyObject *o;
    if (!PyArg_ParseTuple(args, "O", &o))
        return NULL;
    printf("fuck reference count %d\n", (int) Py_REFCNT(o));
    return o;
}

static PyMethodDef methods[] = {
    {"f", (PyCFunction) f, METH_VARARGS},
    {"g", (PyCFunction) g, METH_VARARGS},
    {"h", (PyCFunction) h, METH_VARARGS},
    {NULL}
};

void initfoo() {
    Py_InitModule("foo", methods);
}