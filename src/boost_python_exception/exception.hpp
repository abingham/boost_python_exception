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
	/**
	 * @brief Create a new exception. The return value of what() depends on the
	 *        passed parameters
	 * @param type The type of the python exception
	 * @param message The message of the python exception
	 * @param traceback The python traceback
	 */
    exception(std::string const & type, std::string const & message, traceback const & traceback);
    ~exception() throw();

    const char* what() const throw();

private:
    exception();
    std::string what_;
};

}

#endif
