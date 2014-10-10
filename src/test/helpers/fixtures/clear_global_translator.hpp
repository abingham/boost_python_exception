#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_FIXTURES_CLEAR_GLOBAL_TRANSLATOR_H
#define INCLUDE_BOOST_PYTHON_EXCEPTION_FIXTURES_CLEAR_GLOBAL_TRANSLATOR_H

namespace test { namespace fixtures {

/**
 * @brief A fixture which clears the global exception translator before and after running a test
 */
struct clear_global_translator {
	clear_global_translator();

	~clear_global_translator();
};

} }

#endif /* INCLUDE_BOOST_PYTHON_EXCEPTION_FIXTURES_CLEAR_PYTHON_ERRORS_H */
