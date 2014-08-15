#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_UTIL_STANDARD_EXCEPTION_TRANSLATOR_HPP
#define INCLUDE_BOOST_PYTHON_EXCEPTION_UTIL_STANDARD_EXCEPTION_TRANSLATOR_HPP

#include <boost_python_exception/exception_translator.hpp>

namespace boost_python_exception {

/* Creates an exception_translator pre-configured to translate many of
   the standard Python exceptions.

   The returned translator performs the following translations:

       AttributeError -> attribute_error
       ImportError -> import_error
       IndexError -> index_error
       IOError -> io_error
       KeyError -> key_error
       TypeError -> type_error
       ReferenceError -> reference_error
       ValueError -> value_error
       StopIteration -> stop_iteration

   For example::

       try {
           some_boost_python_code();
       }
       catch (const bp::error_already_set&) {
           create_standard_exception_translator().translate(
               get_exception_info());
       }

 */
exception_translator create_standard_exception_translator();

}

#endif /* INCLUDE_BOOST_PYTHON_EXCEPTION_UTIL_STANDARD_EXCEPTION_TRANSLATOR_HPP */
