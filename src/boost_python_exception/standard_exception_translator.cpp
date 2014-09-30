#include <boost_python_exception/standard_exception_translator.hpp>

#include <sstream>

#include <boost/python/extract.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>

#include <boost_python_exception/exceptions.hpp>
#include <boost_python_exception/util.hpp>

namespace bp = boost::python;

namespace boost_python_exception {

namespace {

	std::string make_syntax_error_message(bp::object error)
	{
		std::string const module_name = bp::extract<std::string>(error.attr("filename"));
		std::string const code = bp::extract<std::string>(error.attr("text"));

		// for some reason, extract<long> does not work while a python error is set, so do it with CPython
		long const line_number = PyInt_AsLong(bp::object(error.attr("lineno")).ptr());
		long const pos_in_line = PyInt_AsLong(bp::object(error.attr("offset")).ptr());

		std::ostringstream message;
		message << "In module \"" << module_name << "\", line " << line_number << ", position " << pos_in_line << ":\n";
		message << "Offending code: " << code;
		message << "                " << std::string(pos_in_line-1, ' ') << "^";

		return message.str();
	}

	void throw_syntax_error(exception_info const & exc_info)
	{
		throw syntax_error(
				extract_exception_type(exc_info.type),
				make_syntax_error_message(exc_info.value),
				extract_traceback(exc_info.traceback));
	}

}

exception_translator create_standard_exception_translator()
{
    exception_translator translator;

    typedef std::map<std::string const, exception_translator::thrower> translation_map;

    // To add new translations, simply update the contents of this map.
    translation_map translations =
        boost::assign::map_list_of
        ("AttributeError", throw_with_python_info<attribute_error>)
        ("ImportError", throw_with_python_info<import_error>)
        ("IndexError", throw_with_python_info<index_error>)
        ("IOError", throw_with_python_info<io_error>)
        ("KeyError", throw_with_python_info<key_error>)
        ("TypeError", throw_with_python_info<type_error>)
        ("ReferenceError", throw_with_python_info<reference_error>)
        ("ValueError", throw_with_python_info<value_error>)
        ("StopIteration", throw_with_python_info<stop_iteration>)
        ("SyntaxError", throw_syntax_error)
        ;

    BOOST_FOREACH(translation_map::value_type const & mapping, translations)
    {
        translator.add(
            builtins().attr(mapping.first.c_str()),
            mapping.second);
    }

    return translator;
}

}
