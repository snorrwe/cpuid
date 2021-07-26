#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <cq.h>

#include <assert.h>

static PyObject*
pycq_query(PyObject* self, PyObject* args)
{
    (void)self;
    (void)args;

    PyObject* list = PyList_New(0);

    unsigned cache_idx = 0;
    while (1) {
        struct cq_cache_info info = cq_cache(cache_idx);
        if (info.cache_idx < 0) {
            break;
        }
        PyObject* item = Py_BuildValue("{s:i,s:i,s:i,s:s}", "cache_size", info.cache_size, "lvl", info.lvl, "line_size", info.linesz_ml + 1, "ty", cq_cache_type_str(info.type));
        PyList_Append(list, item);
        Py_DecRef(item);
        ++cache_idx;
    }

    return list;
}

static PyMethodDef QueryMethods[] = {
    { "query", pycq_query, METH_FASTCALL, "Query the current CPU features\nFields: TBA" },
    { NULL, NULL, 0, NULL } // Sentinel
};

static struct PyModuleDef pycqmodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "pycq",
    .m_doc = NULL, // Documentation TODO
    .m_size = -1,   // module state is global
    .m_methods = QueryMethods
};

PyMODINIT_FUNC
PyInit_pycq(void)
{
    return PyModule_Create(&pycqmodule);
}
