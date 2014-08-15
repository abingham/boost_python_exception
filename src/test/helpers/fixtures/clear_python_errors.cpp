#include "clear_python_errors.hpp"

#include <boost_python_exception/clear_exception.hpp>

using boost_python_exception::clear_exception;

namespace test { namespace fixtures {

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
