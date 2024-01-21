#include "Python.h"

static PyObject *hello_world(PyObject *self, PyObject *args) {
    return Py_BuildValue("s", "hello, world!");
}

static PyMethodDef module_functions[] = {
    { "hello_world", hello_world, METH_VARARGS, "Say hello." },
    { NULL }
};

void initext1() {
    Py_InitModule3("ext1", module_functions, "A minimal module.");
}
