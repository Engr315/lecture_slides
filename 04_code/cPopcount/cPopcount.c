//https://docs.python.org/3/extending/extending.html

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "popcount.h"

static PyObject *
popcount_system(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    return PyLong_FromLong(sts);
}

static PyObject *
cPopcount(PyObject *self, PyObject *args)
{
    uint64_t num;

    if (!PyArg_ParseTuple(args, "l", &num))
        return NULL;
    
    //popcount!!!
    uint64_t res = popcount(num);

    return PyLong_FromLong(res);
}

//helpful:
// https://stackoverflow.com/questions/22458298/extending-python-with-c-pass-a-list-to-pyarg-parsetuple
static PyObject *
cPopcount_all(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int64_t res = 0;

    //parse the list argument
    if (!PyArg_ParseTuple(args, "O", &obj)) {
        return NULL;
    }
    
    //hope it's iteratable
    PyObject *iter = PyObject_GetIter(obj);
    if (!iter) {
        return NULL;// error not iterator
    }

    //loop over all elements in list
    while (1) {
        PyObject *next = PyIter_Next(iter);

        if (!next) {
            // nothing left in the iterator
            break;
        }
       
        // conver to int64_t
        int64_t num = 0;
        if (PyLong_Check(next)) {
            num = PyLong_AsLong(next);
        } else {
            printf ("unsupported type\n");
            return NULL;
       }
     
        //now do popcount!
        res += popcount(num);// do something with foo
        
        /* release reference when done */
        Py_DECREF(next);
    }
    Py_DECREF(iter);

    return PyLong_FromLong(res); 
}


static PyMethodDef cPopcountMethods[] = {
    {"system",  popcount_system, METH_VARARGS,
     "Execute a shell command."},
    {"cPopcount",  cPopcount, METH_VARARGS,
     "Popcount on a unint64_t value"}, 
    {"cPopcount_all",  cPopcount_all, METH_VARARGS,
     "Popcount on a list of values"}, 
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef cPopcountModule = {
    PyModuleDef_HEAD_INIT,
    "cPopcount",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    cPopcountMethods
};

PyMODINIT_FUNC
PyInit_cPopcount(void)
{
    return PyModule_Create(&cPopcountModule);
}
