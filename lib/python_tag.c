#include "python_tag.h"

PyTypeObject TagType;

/**
 * Initialize the Tag object with the given values for "time" and "microstep", 
 * both of which are required.
 * @param self A py_tag_t object.
 * @param args The arguments are:
 *      - time: A logical time.
 *      - microstep: A microstep within the logical time "time".
 */
int Tag_init(py_tag_t *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"time", "microstep", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "Lk", kwlist, &(self->tag.time), &(self->tag.microstep))) {
        return -1;
    }
    return 0;
}

/**
 * Rich compare function for Tag objects. Used in .tp_richcompare.
 * 
 * @param self A py_tag_t object on the left side of the operator.
 * @param other A py_tag_t object on the right side of the operator.
 * @param op the comparison operator
 */
PyObject *Tag_richcompare(py_tag_t *self, PyObject *other, int op) {
    if (!PyObject_IsInstance(other, (PyObject *) &TagType)) {
        PyErr_SetString(PyExc_TypeError, "Cannot compare a Tag with a non-Tag type.");
        return NULL;
    }

    tag_t other_tag = ((py_tag_t *) other)->tag;
    int c = -1;
    if (op == Py_LT) {
        c = (lf_compare_tags(self->tag, other_tag) < 0);
    } else if (op == Py_LE) {
        c = (lf_compare_tags(self->tag, other_tag) <= 0);
    } else if (op == Py_EQ) {
        c = (lf_compare_tags(self->tag, other_tag) == 0);
    } else if (op == Py_NE) {
        c = (lf_compare_tags(self->tag, other_tag) != 0);
    } else if (op == Py_GT) {
        c = (lf_compare_tags(self->tag, other_tag) > 0);
    } else if (op == Py_GE) {
        c = (lf_compare_tags(self->tag, other_tag) >= 0);
    }
    if (c < 0) {
        PyErr_SetString(PyExc_RuntimeError, "Invalid comparator (This statement should never be reached). ");
        return NULL;
    } else if (c) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

/**
 * Tag getter for the "time" attribute
 **/
PyObject* Tag_get_time(py_tag_t *self, void *closure) {
    return PyLong_FromLongLong(self->tag.time);
}

/**
 * Tag getter for the "microstep" attribute
 **/
PyObject* Tag_get_microstep(py_tag_t *self, void *closure) {
    return PyLong_FromUnsignedLong(self->tag.microstep);
}

/**
 * Link names to getter functions.
 * Getters are used when the variable name specified are referenced with a ".".
 * For example:
 * >>> t = Tag(time=1, microstep=2)
 * >>> t.time   # calls Tag_get_time.
 * >>> t.microstep  # calls Tag_get_microstep.
 * >>> t.time = 1  # illegal since setters are omitted.
 **/
PyGetSetDef Tag_getsetters[] = {
    {"time", (getter) Tag_get_time},
    {"microstep", (getter) Tag_get_microstep},
    {NULL}  /* Sentinel */
};

/**
 * Definition of the TagType Object. 
 **/
PyTypeObject TagType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "LinguaFranca.Tag",
    .tp_doc = "Tag object",
    .tp_basicsize = sizeof(py_tag_t),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc) Tag_init,
    .tp_richcompare = (richcmpfunc) Tag_richcompare,
    .tp_getset = Tag_getsetters,
};
