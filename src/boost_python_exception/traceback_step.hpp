#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_TRACEBACK_STEP_H
#define INCLUDE_BOOST_PYTHON_EXCEPTION_TRACEBACK_STEP_H

#include <iosfwd>
#include <string>

namespace boost_python_exception {

/*
 * @brief Represents a single step of a python traceback.
 */
struct traceback_step
{
	/*
	 * @brief The line number in the file where the error occurred
	 */
	int line_number;
	/*
	 * @brief The python file in which the error occurred
	 */
	std::string file_name;
	/*
	 * @brief A description where the error occurred, e.g., a module, function, etc...
	 */
	std::string source;
};

/*
 * @brief Write formatted traceback_info to a stream
 * @param stream The stream to which the traceback information shall be written
 * @param info The traceback_info which shall be written
 * @return A reference to stream to facilitate chaining
 */
std::ostream& operator<<(std::ostream& stream, traceback_step const & info);

}

#endif /* INCLUDE_BOOST_PYTHON_EXCEPTION_TRACEBACK_STEP_H */

