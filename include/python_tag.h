#ifndef PYTHON_TAG_H
#define PYTHON_TAG_H
#include <Python.h>
#include <structmember.h>
#include "core/tag.h"

/**
 * Python wrapper for the tag_t struct in the C target.
 **/
typedef struct {
    PyObject_HEAD
    tag_t tag;
} py_tag_t;

#endif