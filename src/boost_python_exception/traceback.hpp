#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_TRACEBACK_H
#define INCLUDE_BOOST_PYTHON_EXCEPTION_TRACEBACK_H

#include <vector>
#include <iosfwd>

#include <boost_python_exception/traceback_step.hpp>

namespace boost_python_exception {

/**
 * @brief Represents a python traceback
 */
typedef std::vector<traceback_step> traceback;

/*
 * @brief Write formatted traceback to a stream. Most recent calls are printed last.
 * @param stream The stream to which the traceback information shall be written
 * @param info The traceback which shall be written
 * @return A reference to stream to facilitate chaining
 */
std::ostream & operator<<(std::ostream & stream, traceback const & traceback);

}

#endif

