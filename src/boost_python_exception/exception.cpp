#include <boost_python_exception/exceptions.hpp>

#include <boost_python_exception/format_exception.hpp>

namespace boost_python_exception {

exception::exception(exception_info const& exc_info) :
    exc_info_(exc_info),
    what_(format_exception(exc_info))
{}

exception::~exception() throw() {}

exception_info const& exception::python_exception() const
{
    return exc_info_;
}

const char* exception::what() const throw()
{
    return what_.c_str();
}

}
