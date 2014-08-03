#include <boost_python_exception/get_exception_info.hpp>

namespace bp=boost::python;

namespace {

/* Convert a PyObject* into a borrowed bp::object. If `ptr` is NULL,
 * this returns `None`.
 */
bp::object ptr_to_obj(PyObject* ptr)
{
    if (ptr)
        return bp::object(
            bp::handle<>(
                bp::borrowed(ptr)));
    else
        return bp::object();
}

}

namespace boost_python_exception {

bp::tuple getExceptionInfo()
{
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

    bp::object type = ::ptr_to_obj(t);
    bp::object value = ::ptr_to_obj(v);
    bp::object traceback = ::ptr_to_obj(tb);

    // Give the exception back to Python in case anyone else wants it.
    PyErr_Restore(t, v, tb);

    return bp::make_tuple(type, value, traceback);
}

}
