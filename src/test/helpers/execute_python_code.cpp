#include "execute_python_code.hpp"

#include <boost/python/exec.hpp>
#include <boost/python/import.hpp>
#include <boost/python/object.hpp>

namespace test {

void execute_python_code_in_main_module(
    std::string const & python_code,
    bool suppress_exception)
{
    namespace bp=boost::python;

    bp::object module = bp::import("__main__");
    bp::object dict = module.attr("__dict__");
    try {
        bp::exec(python_code.c_str(), dict);
    }
    catch (bp::error_already_set const &) {
        if (!suppress_exception)
            throw;
    }
}

}
