#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION__AUTO_TRANSLATION__IMPORT_HPP
#define INCLUDE_BOOST_PYTHON_EXCEPTION__AUTO_TRANSLATION__IMPORT_HPP

#include <string>

#include <boost/python/object.hpp>

namespace boost_python_exception { namespace auto_translation {

/**
 * @brief Wraps boost::python::import. Deals with python exceptions
 *        using the global exception translator.
 * @param module_name The name of the module which shall be imported
 * @return A python object which represents the imported module
 * @throw unspecified Whatever the global exception translator throws
 *        when python exceptions arise
 */
boost::python::object import(std::string const & module_name);

} }



#endif
