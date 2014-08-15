#include <boost_python_exception/standard_exception_translator.hpp>

#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>

#include <boost_python_exception/exceptions.hpp>
#include <boost_python_exception/util.hpp>

namespace boost_python_exception {

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
