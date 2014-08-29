#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_EXCEPTION_HPP
#define INCLUDE_BOOST_PYTHON_EXCEPTION_EXCEPTION_HPP

#include <Python.h>

#include <exception>
#include <string>

#include <boost/exception/exception.hpp>

#include <boost_python_exception/exception_info.hpp>

namespace boost_python_exception {

/** The base for all boost_python_exception exceptions. */
class exception : public virtual boost::exception,
                  public virtual std::exception
{
public:
    explicit exception(exception_info const& exc_info);
    ~exception() throw();

    exception_info const& python_exception() const;

    const char* what() const throw();

private:
    exception();
    exception_info exc_info_;
    std::string what_;
};

}

#endif
