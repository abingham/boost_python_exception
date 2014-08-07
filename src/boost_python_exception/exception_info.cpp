#include <boost_python_exception/exception_info.hpp>

namespace bp=boost::python;

namespace boost_python_exception {

exception_info::exception_info(
		bp::object type,
		bp::object value,
		bp::object traceback
	) :
		type(type),
		value(value),
		traceback(traceback)
{
}

}
