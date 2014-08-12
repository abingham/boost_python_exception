#include "clear_python_errors.hpp"

#include <boost_python_exception/clear_exception.hpp>

namespace boost_python_exception {
namespace test {

clear_python_errors::clear_python_errors()
{
    clear_exception();
}

clear_python_errors::~clear_python_errors()
{
    clear_exception();
}

}
}
