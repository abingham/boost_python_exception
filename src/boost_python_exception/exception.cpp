#include <boost_python_exception/exception.hpp>

#include <sstream>

namespace boost_python_exception {

namespace {

std::string generate_message(std::string const & type, std::string const & message, traceback const & traceback)
{
    std::ostringstream result;
    if (not traceback.empty()) {
        result << "Python traceback (most recent calls last):\n";
        result << traceback;
    }
    result << type;
    if (not message.empty()) {
        result << ": " << message;
    }
    return result.str();
}

}

exception::exception(std::string const & type, std::string const & message, traceback const & traceback) :
    what_(generate_message(type, message, traceback))
{}

exception::~exception() throw() {}

const char* exception::what() const throw()
{
    return what_.c_str();
}

}
