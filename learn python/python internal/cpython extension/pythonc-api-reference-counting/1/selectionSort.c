#include "Python.h"


static PyObject *py_selectionSort(PyObject *self, PyObject *args) {
    PyObject *list;
    
    if (!PyArg_ParseTuple(args, "O", &list)) {
        return NULL;
    }
    
    PyObject *list_item;
    Py_ssize_t i, len = PyList_Size(list);
    long *list_array = malloc(len * sizeof(long));
    
    for (i = 0; i < len; i++) {
        list_item = PyList_GetItem(list, i);
        list_array[i] = PyInt_AsLong(list_item);
    }
    
    // omit sort
    
    PyObject *list2 = PyList_New(len);
    for (i = 0; i < len; i++) {
        list_item = PyInt_FromLong(list_array[i]);
        PyList_SetItem(list2, i, list_item);
    }
    
    free(list_array);
    return list2;
}

static PyMethodDef methods[] = {
    {"selectionSort", py_selectionSort, METH_VARARGS, NULL},
    {NULL}
};

void initselectionSort() {
    Py_InitModule3("selectionSort", methods, "Extension module example!");
}