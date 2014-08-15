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

exception_info get_exception_info()
{
    /* This bears some explanation. Our plan is to:

         a) Get the (possibly NULL) exception references from Python,
         b) Keep references to them for ourselves, and
         c) Give the original references back to Python via PyErr_Restore.

       Since PyErr_Fetch gives us ownership of the exception info, and
       since PyErr_Restore will try to *take* ownership (i.e. claim the
       existing ref-count) when we use it, we need to increment the
       ref-count on the exception objects so that we keep one reference
       for ourselves. To do this, we use bp::borrowed which inc-refs for us.

       If the exception objects are NULL, we of course don't do
       anything but create some new references to None. PyErr_Restore
       is well-behaved when you pass it NULLs.
     */

    PyObject *t, *v, *tb;

    // This gives us pre-incremented references. We own the references
    // to t, v, and tb after this call (if they're non-NULL.)
    PyErr_Fetch(&t, &v, &tb);
    PyErr_NormalizeException(&t, &v, &tb);

    // Take references to the exception objects, inc-ref'ing them so
    // we can share them with PyErr_Restore.
    bp::object type = ::ptr_to_obj(t);
    bp::object value = ::ptr_to_obj(v);
    bp::object traceback = ::ptr_to_obj(tb);

    // Give the exception back to Python in case anyone else wants it.
    PyErr_Restore(t, v, tb);

    return exception_info(type, value, traceback);
}

}
