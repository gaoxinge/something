#include "Python.h"
#include "structmember.h"

typedef struct {
    PyObject_HEAD
    PyObject *dict;
    int count;
} CountDict;


static int CountDict_init(CountDict *self, PyObject *args, PyObject *kwds) {
    self->dict = PyDict_New();
    self->count = 0;
    return 0;
}

static void CountDict_dealloc(CountDict *self) {
    Py_XDECREF(self->dict);
    self->ob_type->tp_free((PyObject *) self);
}

static PyMemberDef CountDict_members[] = {
    {"dict", T_OBJECT, offsetof(CountDict, dict), 0, "The diction"},
    {"count", T_INT, offsetof(CountDict, count), 0, "The number of times set() has been called."},
    {NULL},
};

static PyObject *CountDict_set(CountDict *self, PyObject *args) {
    const char *key;
    PyObject *value;
    
    if (!PyArg_ParseTuple(args, "sO:set", &key, &value)) {
        return NULL;
    }
    
    if (PyDict_SetItemString(self->dict, key, value) < 0) {
        return NULL;
    }
    
    self->count++;
    
    return Py_BuildValue("i", self->count);
}

static PyMethodDef CountDict_methods[] = {
    {"set", (PyCFunction) CountDict_set, METH_VARARGS, "Set a key and increment the count."},
    {NULL}
};

static PyTypeObject CountDictType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /* ob_size */
    "CountDict",               /* tp_name */
    sizeof(CountDict),         /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor) CountDict_dealloc, /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_compare */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags*/
    "CountDict object",        /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    CountDict_methods,         /* tp_methods */
    CountDict_members,         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc) CountDict_init, /* tp_init */
    0,                         /* tp_alloc */
    0,                         /* tp_new */
};

void initext3() {
    PyObject* mod;
    
    mod = Py_InitModule3("ext3", NULL, "An extension with a type.");
    if (mod == NULL) {
        return;
    }
    
    CountDictType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&CountDictType) < 0) {
        return;
    }
    
    Py_INCREF(&CountDictType);
    PyModule_AddObject(mod, "CountDict", (PyObject *) &CountDictType);
}