#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_EXCEPTIONS_HPP
#define INCLUDE_BOOST_PYTHON_EXCEPTION_EXCEPTIONS_HPP

/** C++ counterparts to the standard Python exceptions.
 */

#include <boost_python_exception/exception.hpp>


namespace boost_python_exception {

class exception_info;

/* A template for simple subclasses of exception.
 */
template <typename ExcType>
class exception_template : public exception
{
public:
    exception_template(std::string const & type, std::string const & message, traceback const & traceback) :
        exception(type, message, traceback)
    {}
};

/* A collection of C++ analogues for the standard Python exceptions.
 */
typedef exception_template<class attribute_error_tag> attribute_error;
typedef exception_template<class import_error_tag> import_error;
typedef exception_template<class index_error_tag> index_error;
typedef exception_template<class io_error_tag> io_error;
typedef exception_template<class key_error_tag> key_error;
typedef exception_template<class type_error_tag> type_error;
typedef exception_template<class reference_error_tag> reference_error;
typedef exception_template<class value_error_tag> value_error;
typedef exception_template<class stop_iteration_tag> stop_iteration;
typedef exception_template<class syntax_error_tag> syntax_error;

}

#endif
