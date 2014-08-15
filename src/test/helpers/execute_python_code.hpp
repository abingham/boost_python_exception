#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_HELPERS_EXECUTE_PYTHON_CODE_HPP
#define INCLUDE_BOOST_PYTHON_EXCEPTION_HELPERS_EXECUTE_PYTHON_CODE_HPP

#include <Python.h>

#include <string>

namespace test {

void execute_python_code_in_main_module(
    std::string const & python_code,
    bool suppress_exception=false);

}

#endif /* INCLUDE_BOOST_PYTHON_EXCEPTION_HELPERS_EXECUTE_PYTHON_CODE_HPP */
