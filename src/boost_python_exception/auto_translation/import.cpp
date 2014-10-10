#include <boost_python_exception/auto_translation/import.hpp>

#include <boost/python/import.hpp>

#include <boost_python_exception/get_exception_info.hpp>
#include <boost_python_exception/clear_exception.hpp>
#include <boost_python_exception/auto_translation/exception_translator.hpp>

namespace bp = boost::python;

namespace boost_python_exception { namespace auto_translation {

boost::python::object import(std::string const & module_name)
{
	try {
		return bp::import(module_name.c_str());
	} catch (bp::error_already_set const &) {
		exception_info const error = get_exception_info();
//		clear_exception();
		exception_translator::translate(error);
	}
}

} }
