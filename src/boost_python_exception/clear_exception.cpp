#include <boost_python_exception/clear_exception.hpp>

#include <Python.h>

namespace boost_python_exception {

void clear_exception()
{
    PyErr_Clear();
}

}
