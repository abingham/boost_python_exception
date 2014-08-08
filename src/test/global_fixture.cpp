#define BOOST_TEST_MODULE boost_python_exception

#include <boost/test/unit_test.hpp>

#include <Python.h>

struct GlobalFixture {
    GlobalFixture()   { Py_Initialize(); }
    ~GlobalFixture()  { /* Py_Finalize(); */ }
};

BOOST_GLOBAL_FIXTURE(GlobalFixture);
