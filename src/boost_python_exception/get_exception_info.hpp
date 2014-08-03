#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_GET_EXCEPTION_INFO_H
#define INCLUDE_BOOST_PYTHON_EXCEPTION_GET_EXCEPTION_INFO_H

#include <Python.h>

#include <boost/python/tuple.hpp>

namespace boost_python_exception {

namespace detail {

boost::python::object ptr_to_obj(PyObject* ptr)
{
    if (ptr)
        return boost::python::object(
            boost::python::handle<>(
                boost::python::borrowed(ptr)));
    else
        return boost::python::object();
}

}

/** Get the current Python exception info tuple

    This leaves the Python exception registers unchanged (with the
    exception of inc-ref'ing the objects in the registers, if any.)

    @return A ``(type, value, traceback)`` tuple for the current Python
      exception. If there is no current exception, all of the elements
      of the tuple will be ``None``.
 */
boost::python::tuple getExceptionInfo()
{
    namespace bp=boost::python;

    PyObject *t, *v, *tb;

    // This gives us pre-incremented references. We own the references
    // to t, v, and tb after this call (if they're non-NULL.)
    PyErr_Fetch(&t, &v, &tb);
    PyErr_NormalizeException(&t, &v, &tb);

    /* This bears some explanation. First, since t could be NULL
     * (i.e. PyErr_Fetch returned NULL because there is no active
     * exception), we use allow_null.
     *
     * Then, since we use borrowed because we want to create a new
     * reference to the PyObject. Since we plan to give t back to
     * Python via PyErr_Restore, and since PyErr_Restore will steal a
     * reference, we have to create a new one for our own purposes.
     *
     * Finally,
     */

    bp::object type = detail::ptr_to_obj(t);
    bp::object value = detail::ptr_to_obj(v);
    bp::object traceback = detail::ptr_to_obj(tb);

    // Give the exception back to Python in case anyone else wants it.
    PyErr_Restore(t, v, tb);

    return bp::make_tuple(type, value, traceback);
}

}

#endif /* INCLUDE_BOOST_PYTHON_EXCEPTION_GET_EXCEPTION_INFO_H */
