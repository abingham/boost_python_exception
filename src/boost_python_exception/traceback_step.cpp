#include <boost_python_exception/traceback_step.hpp>

#include <iostream>

namespace boost_python_exception {

std::ostream& operator<<(std::ostream& stream, traceback_step const & info)
{
    stream << "File \"" << info.file_name << "\", line " << info.line_number << ", in " << info.source;
    return stream;
}

}
