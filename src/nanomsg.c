
#include <Python.h>

#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>
#include <nanomsg/pubsub.h>

static PyObject *nanomsg_nn_socket(PyObject *self, PyObject *args)
{
    int domain;
    int protocol;
    int s;

    if (!PyArg_ParseTuple(args, "ii", &domain, &protocol))
    {
        return NULL;
    }

    s = nn_socket(domain, protocol);

    return PyLong_FromLong(s);
}

static PyObject *nanomsg_nn_close(PyObject *self, PyObject *args)
{
    int s;
    int rc;

    if (!PyArg_ParseTuple(args, "i", &s))
    {
        return NULL;
    }

    rc = nn_close(s);

    return PyLong_FromLong(rc);
}

static PyObject *nanomsg_nn_bind(PyObject *self, PyObject *args)
{
    int s;
    const char *addr;
    int eid;

    if (!PyArg_ParseTuple(args, "is", &s, &addr))
    {
        return NULL;
    }

    eid = nn_bind(s, addr);

    return PyLong_FromLong(eid);
}

static PyObject *nanomsg_nn_connect(PyObject *self, PyObject *args)
{
    int s;
    const char *addr;
    int eid;

    if (!PyArg_ParseTuple(args, "is", &s, &addr))
    {
        return NULL;
    }

    eid = nn_connect(s, addr);

    return PyLong_FromLong(eid);
}

static PyObject *nanomsg_nn_send(PyObject *self, PyObject *args)
{
    int s;
    Py_buffer view;
    int flags;
    int nbytes;

    if (!PyArg_ParseTuple(args, "iy*i", &s, &view, &flags))
    {
        return NULL;
    }

    nbytes = nn_send(s, view.buf, view.len, flags);

    PyBuffer_Release(&view);
    return PyLong_FromLong(nbytes);
}

static PyObject *nanomsg_nn_recv(PyObject *self, PyObject *args)
{
    int s;
    Py_buffer view;
    int flags;
    int nbytes;

    if (!PyArg_ParseTuple(args, "iw*i", &s, &view, &flags))
    {
        return NULL;
    }

    nbytes = nn_recv(s, view.buf, view.len, flags);

    PyBuffer_Release(&view);
    return PyLong_FromLong(nbytes);
}

static PyObject *nanomsg_nn_device(PyObject *self, PyObject *args)
{
    int s1;
    int s2;
    int rc;

    if (!PyArg_ParseTuple(args, "ii", &s1, &s2))
    {
        return NULL;
    }

    rc = nn_device(s1, s2);

    return PyLong_FromLong(rc);
}

static PyMethodDef nanomsg_methods[] = {
    {
        "nn_socket",
        nanomsg_nn_socket,
        METH_VARARGS,
        "create an SP socket"
    },
    {
        "nn_close",
        nanomsg_nn_close,
        METH_VARARGS,
        "close an SP socket"
    },
    {
        "nn_bind",
        nanomsg_nn_bind,
        METH_VARARGS,
        "add a local endpoint to the socket"
    },
    {
        "nn_connect",
        nanomsg_nn_connect,
        METH_VARARGS,
        "add a remote endpoint to the socket"
    },
    {
        "nn_send",
        nanomsg_nn_send,
        METH_VARARGS,
        "send a message"
    },
    {
        "nn_recv",
        nanomsg_nn_recv,
        METH_VARARGS,
        "receive a message"
    },
    {
        "nn_device",
        nanomsg_nn_device,
        METH_VARARGS,
        "start a device"
    },
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef nanomsg_module = {
    PyModuleDef_HEAD_INIT,
    "nanomsg",
    "nanomsg library",
    -1,
    nanomsg_methods
};

PyMODINIT_FUNC PyInit_nanomsg(void)
{
    PyObject *module;
    Py_Initialize();
    module = PyModule_Create(&nanomsg_module);
    PyModule_AddIntConstant(module, "AF_SP", AF_SP);
    PyModule_AddIntConstant(module, "AF_SP_RAW", AF_SP_RAW);
    PyModule_AddIntConstant(module, "NN_REQ", NN_REQ);
    PyModule_AddIntConstant(module, "NN_REP", NN_REP);
    PyModule_AddIntConstant(module, "NN_PUB", NN_PUB);
    PyModule_AddIntConstant(module, "NN_SUB", NN_SUB);
    return module;
}
