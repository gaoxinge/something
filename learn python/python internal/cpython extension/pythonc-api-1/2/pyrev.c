#include <stdlib.h>
#include <string.h>
#include "Python.h"

static PyObject *pyrev(PyObject *self, PyObject *args) {
    char *str1;
    
    if (!PyArg_ParseTuple(args, "s", &str1)) {
        return NULL;
    }
    
    size_t len = strlen(str1);
    char *str2 = (char *) malloc((len + 1) * sizeof(char));
    
    for (size_t i = 0; i < len; i++)
        str2[i] = str1[len - 1 - i];
    str2[len] = '\0';
    
    return Py_BuildValue("s", str2);
}

static PyMethodDef methods[] = {
    {"pyrev", pyrev, METH_VARARGS, NULL},
    {NULL}
};

void initpyrev() {
    Py_InitModule3("pyrev", methods, "Reverse the string!");
}