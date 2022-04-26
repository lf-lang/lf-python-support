#ifndef PYTHON_PORT_H
#define PYTHON_PORT_H

#include <Python.h>
#include <structmember.h>
#include "python_capsule_extension.h"

/**
 * The struct used to instantiate a port
 * in Lingua Franca. This is used 
 * in the PythonGenerator instead of redefining
 * a struct for each port.
 * This can be used for any Python object,
 * including lists and tuples.
 * PyObject* value: the value of the port with the generic Python type
 * is_present: indicates if the value of the port is present
 *             at the current logical time
 * num_destinations: used for reference counting the number of
 *                   connections to destinations.
 **/
typedef struct {
    PyObject* value;
    bool is_present;
    int num_destinations;
    lf_token_t* token;
    int length;
    void (*destructor) (void* value);
    void* (*copy_constructor) (void* value);
    FEDERATED_CAPSULE_EXTENSION
} generic_port_instance_struct;


/**
 * The struct used to represent ports in Python 
 * This template is used as a blueprint to create
 * Python objects that follow the same structure.
 * The resulting Python object will have the type 
 * py_port_capsule_t in C (LinguaFranca.port_capsule in Python).
 * 
 * port: A PyCapsule (https://docs.python.org/3/c-api/capsule.html)
 *       that safely holds a C void* inside a Python object. This capsule
 *       is passed through the Python code and is extracted in C functions
 *       like set and __getitem__.
 * value: The value of the port at the time of invocation of @see convert_C_port_to_py.
 *        The value and is_present are copied from the port if it is not a multiport and can be accessed as
 *        port.value. For multiports, is_present will be false and value will be None. The value of each individual
 *        port can be accessed as port[idx].value (@see port_capsule_get_item). 
 *        Subsequent calls to set will also need to update the value and is_present fields so that they are reflected
 *        in Python code.
 * is_present: Indicates if the value of the singular port is present
 *             at the current logical time
 * width: Indicates the width of the multiport. This is set to -2 for non-multiports.
 * current_index: Used to facilitate iterative functions (@see port_iter)
 **/
typedef struct {
    PyObject_HEAD
    PyObject* port;
    PyObject* value;
    bool is_present;
    int width;
    long current_index;
    FEDERATED_CAPSULE_EXTENSION
} generic_port_capsule_struct;

#endif