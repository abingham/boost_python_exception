#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_HELPERS_EXECUTE_PYTHON_CODE_HPP
#define INCLUDE_BOOST_PYTHON_EXCEPTION_HELPERS_EXECUTE_PYTHON_CODE_HPP

#include <Python.h>

#include <string>

namespace test {

/* Execute ``python_code`` as Python code in the context of the main
   module.

   If ``suppress_exception`` is true, then any
   ``boost::python::error_already_set`` raised while executing the
   code will be suppressed. Otherwise, the exception will be raised.
 */
void execute_python_code_in_main_module(
    std::string const & python_code,
    bool suppress_exception=false);

}

#endif /* INCLUDE_BOOST_PYTHON_EXCEPTION_HELPERS_EXECUTE_PYTHON_CODE_HPP */
