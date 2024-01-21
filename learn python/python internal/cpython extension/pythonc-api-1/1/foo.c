#include "Python.h"

static PyObject *foo(PyObject *self, PyObject *args) {
    //Py_RETURN_NONE;
    return Py_None;
}

static PyMethodDef methods[] = {
    { "foo", foo, METH_VARARGS, NULL },
    { NULL },
};

void initfoo() {
    Py_InitModule3("foo", methods, "Extension module example!");
}