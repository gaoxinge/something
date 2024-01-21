#include "Python.h"

static PyObject *string_peek(PyObject *self, PyObject *args) {
    const char *pstr;
    int indx;
    
    if (!PyArg_ParseTuple(args, "si:string_peek", &pstr, &indx)) {
        return NULL;
    }
    
    int char_value = pstr[indx];
    return Py_BuildValue("i", char_value);
}

static PyObject *string_peek2(PyObject *self, PyObject *args) {
    const char *pstr;
    int indx;
    
    if (!PyArg_ParseTuple(args, "si:string_peek", &pstr, &indx)) {
        return NULL;
    }
    
    if (indx < 0 || indx >= strlen(pstr)) {
        PyErr_SetString(PyExc_IndexError, "peek index out of range");
        return NULL;
    }
    
    int char_value = pstr[indx];
    return Py_BuildValue("i", char_value);
}

static PyObject *insert_power1(PyObject *self, PyObject *args) {
    PyObject *numbers;
    int n;
    
    if (!PyArg_ParseTuple(args, "Oi", &numbers, &n)) {
        return NULL;
    }
    
    PyObject *powers = Py_BuildValue("(iii)", n, n*n, n*n*n);
    
    if (PySequence_SetItem(numbers, n, powers) < 0) {
        return NULL;
    }
    
    return powers;
}

static PyObject *insert_power2(PyObject *self, PyObject *args) {
    PyObject *numbers;
    int n;
    
    if (!PyArg_ParseTuple(args, "Oi", &numbers, &n)) {
        return NULL;
    }
    
    PyObject *powers = Py_BuildValue("(iii)", n, n*n, n*n*n);
    
    if (PySequence_SetItem(numbers, n, powers) < 0) {
        Py_DECREF(powers);
        return NULL;
    }
    
    return powers;
}

static PyMethodDef module_functions[] = {
    { "string_peek", string_peek, METH_VARARGS, "Pick a character from a string." },
    { "string_peek2", string_peek2, METH_VARARGS, "Safely pick a character from a string."},
    { "insert_powers1", insert_power1, METH_VARARGS, "Insert a tuple of powers-of-n at index n" },
    { "insert_powers2", insert_power2, METH_VARARGS, "Insert a tuple of powers-of-n at index n" },
    { NULL }
};

void initext2() {
    Py_InitModule3("ext2", module_functions, "A minimal module.");
}