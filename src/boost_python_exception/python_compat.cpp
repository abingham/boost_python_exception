#include <boost_python_exception/python_compat.hpp>

namespace boost_python_exception {

std::string python_string_as_std_string(PyObject* obj)
{
#if PY_MAJOR_VERSION == 2
    return PyString_AsString(obj);
#else
    return PyUnicode_AsUTF8(obj);
#endif
}

long python_integral_as_long(PyObject* obj)
{
#if PY_MAJOR_VERSION == 2
    return PyInt_AsLong(obj);
#else
    return PyLong_AsLong(obj);
#endif
}

}
