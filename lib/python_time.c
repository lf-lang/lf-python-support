#include <Python.h>
#include <structmember.h>

///////// Time-keeping functions //////////
/** 
 * Return the logical time in nanoseconds.
 */
PyObject* py_lf_time_logical(PyObject *self, PyObject *args) {
    return PyLong_FromLongLong(lf_time(LF_LOGICAL));
}

/** 
 * Return the elapsed logical time in nanoseconds.
 */
PyObject* py_lf_time_elapsed_logical(PyObject *self, PyObject *args) {
    return PyLong_FromLongLong(lf_time(LF_ELAPSED_LOGICAL));
}

/** 
 * Return the physical time in nanoseconds.
 */
PyObject* py_lf_time_physical(PyObject *self, PyObject *args) {
    return PyLong_FromLongLong(lf_time(LF_PHYSICAL));
}

/** 
 * Return the elapsed physical time in nanoseconds.
 */
PyObject* py_lf_time_elapsed_physical(PyObject *self, PyObject *args) {
    return PyLong_FromLongLong(lf_time(LF_ELAPSED_PHYSICAL));
}

/**
 * Return the start time in nanoseconds.
 */
PyObject* py_lf_time_start(PyObject *self, PyObject *args) {
    return PyLong_FromLongLong(lf_time(LF_START));
}

/**
 * Return the current microstep.
 */
PyObject* py_get_microstep(PyObject *self, PyObject *args) {
    return PyLong_FromUnsignedLong(lf_tag().microstep);
}

PyTypeObject PyTimeType;

PyMethodDef PyTimeTypeMethods[] = {
    {"logical", (PyCFunction) py_lf_time_logical, METH_NOARGS|METH_STATIC, "Get the current logical time."},
    {"elapsed_logical", (PyCFunction) py_lf_time_elapsed_logical, METH_NOARGS|METH_STATIC, "Get the current elapsed logical time"},
    {"physical", (PyCFunction) py_lf_time_physical, METH_NOARGS|METH_STATIC, "Get the current physical time"},
    {"elapsed_physical", (PyCFunction) py_lf_time_elapsed_physical, METH_NOARGS|METH_STATIC, "Get the current elapsed physical time"},
    {"start", (PyCFunction) py_lf_time_start, METH_NOARGS|METH_STATIC, "Get the start time"},
    {NULL}  /* Sentinel */
};

/**
 * Definition of the PyTagType Object. 
 **/
PyTypeObject PyTimeType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "LinguaFranca.TimeType",
    .tp_doc = "Time object",
    .tp_basicsize = 0,
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_methods = PyTimeTypeMethods,
};



