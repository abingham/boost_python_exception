#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_FIXTURES_CLEAR_PYTHON_ERRORS_H
#define INCLUDE_BOOST_PYTHON_EXCEPTION_FIXTURES_CLEAR_PYTHON_ERRORS_H

namespace test { namespace fixtures {

/**
 * @brief A fixture which clears python errors before and after running a test
 */
struct clear_python_errors {
	clear_python_errors();

	~clear_python_errors();
};

} }

#endif /* INCLUDE_BOOST_PYTHON_EXCEPTION_FIXTURES_CLEAR_PYTHON_ERRORS_H */
