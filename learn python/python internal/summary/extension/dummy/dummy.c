#include "Python.h"

static PyObject *dummy1(PyObject *self, PyObject *args) {
    Py_RETURN_NONE;
}

static PyObject *dummy2(PyObject *self, PyObject *args) {
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef methods[] = {
    {"dummy1", dummy1, METH_NOARGS},
    {"dummy2", dummy2, METH_NOARGS},
    {NULL},
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "dummy",
    NULL,
    -1,
    methods
};

PyMODINIT_FUNC PyInit_dummy(void) {
    return PyModule_Create(&module);
}
