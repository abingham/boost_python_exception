#include <boost_python_exception/extract_exception_details.hpp>

#include <frameobject.h>

#include <boost/python/extract.hpp>
#include <boost/python/str.hpp>

#include <boost_python_exception/python_compat.hpp>

namespace boost_python_exception {

namespace {

void add_traceback_step(std::vector<traceback_step> & output, PyTracebackObject const * traceback)
{
    traceback_step entry = {
        traceback->tb_lineno,
        python_string_as_std_string(traceback->tb_frame->f_code->co_filename),
        python_string_as_std_string(traceback->tb_frame->f_code->co_name)
    };
    output.push_back(entry);
}

}

traceback extract_traceback(boost::python::object py_traceback)
{
    if (py_traceback.is_none()) {
        return traceback();
    } else {
        PyTracebackObject const * tb = reinterpret_cast<PyTracebackObject *>(py_traceback.ptr());
        std::vector<traceback_step> result;
        for (; tb != 0; tb = tb->tb_next) {
            add_traceback_step(result, tb);
        }

        return result;
    }
}

std::string extract_exception_type(boost::python::object type)
{
    if (PyExceptionClass_Check(type.ptr())) {
        return PyExceptionClass_Name(type.ptr());
    } else {
        throw std::logic_error("Given type is not a standard python exception class");
    }
}

std::string extract_message(boost::python::object value)
{
    return boost::python::extract<std::string>(boost::python::str(value));
}


}
