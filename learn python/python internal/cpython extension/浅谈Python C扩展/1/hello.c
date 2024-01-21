#include "Python.h"

static PyObject *hello1(PyObject *self) {
    return Py_BuildValue("s", "hello world");
}

static PyObject *hello2(PyObject *self, PyObject *args) {
    char *str;
    if (!PyArg_ParseTuple(args, "s", &str))
        return NULL;
    return Py_BuildValue("s", str);
}

static PyObject *hello3(PyObject *self, PyObject *args, PyObject *kwargs) {
    char *str;
    static char *kwlist[] = {"str", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|s", kwlist, &str))
        return NULL;
    return Py_BuildValue("s", str);
}

static PyMethodDef methods[] = {
    {"hello1", (PyCFunction) hello1, METH_NOARGS},
    {"hello2", (PyCFunction) hello2, METH_VARARGS},
    {"hello3", (PyCFunction) hello3, METH_VARARGS | METH_KEYWORDS},
    {NULL}
};

void inithello() {
    Py_InitModule("hello", methods);
    //Py_InitModule3("hello", methods, "doc");
}