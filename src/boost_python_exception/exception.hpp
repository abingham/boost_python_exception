#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_EXCEPTION_HPP
#define INCLUDE_BOOST_PYTHON_EXCEPTION_EXCEPTION_HPP

#include <Python.h>

#include <exception>
#include <string>

#include <boost/exception/exception.hpp>

#include <boost_python_exception/traceback.hpp>

namespace boost_python_exception {

/** The base for all boost_python_exception exceptions. */
class exception : public virtual boost::exception,
                  public virtual std::exception
{
public:
    exception(std::string const & type, std::string const & message, traceback const & traceback);
    ~exception() throw();

    const char* what() const throw();

private:
    exception();
    std::string what_;
};

}

#endif
