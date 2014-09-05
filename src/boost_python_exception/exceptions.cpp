#include <boost_python_exception/exceptions.hpp>

#include <boost/python/extract.hpp>
#include <boost/python/str.hpp>

#include <boost_python_exception/exception_info.hpp>
#include <boost_python_exception/extract_traceback.hpp>

namespace boost_python_exception { namespace impl {

exception make_exception(exception_info const & exc_info)
{
	std::string const type = boost::python::extract<std::string>(boost::python::str(exc_info.type));
	std::string const message = boost::python::extract<std::string>(boost::python::str(exc_info.value));
	traceback const traceback = extract_traceback(exc_info.traceback);

	return exception(type, message, traceback);
}

} }
