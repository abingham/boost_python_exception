#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_EXCEPTIONS_HPP
#define INCLUDE_BOOST_PYTHON_EXCEPTION_EXCEPTIONS_HPP

/** C++ counterparts to the standard Python exceptions.
 */

#include <exception>

#include <boost/exception/exception.hpp>

namespace boost_python_exception {

/** The base for all boost_python_exception exceptions. */
class exception : public virtual boost::exception,
                  public virtual std::exception
{};

/* A collection of C++ analogues for the standard Python exceptions.
 */

class attribute_error : public exception {};
class import_error : public exception {};
class index_error : public exception {};
class io_error : public exception {};
class key_error : public exception {};
class type_error : public exception {};
class reference_error : public exception {};
class value_error : public exception {};
class stop_iteration : public exception {};

}

#endif
