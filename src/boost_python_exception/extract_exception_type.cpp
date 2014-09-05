#include <boost_python_exception/extract_exception_type.hpp>

#include <stdexcept>

namespace boost_python_exception {

std::string extract_exception_type(boost::python::object type)
{
	if (PyExceptionClass_Check(type.ptr())) {
		return PyExceptionClass_Name(type.ptr());
	} else {
		throw std::logic_error("Given type is not a standard python exception class");
	}
}

}

