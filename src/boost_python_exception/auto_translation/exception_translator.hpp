#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION__AUTO_TRANSLATION__EXCEPTION_TRANSLATOR_HPP
#define INCLUDE_BOOST_PYTHON_EXCEPTION__AUTO_TRANSLATION__EXCEPTION_TRANSLATOR_HPP

#include <Python.h>

namespace boost_python_exception {

class exception_info;
class exception_translator;

}

namespace boost_python_exception { namespace auto_translation {

/**
 * @brief This namespace contains basic functions for interaction with the global exception
 *        translator.
 *
 *        boost_python_exception offers a global exception translator. Once an instance
 *        of boost_python_exception::exception_translator has been registered as the
 *        global exception translator, all functions and classes in the auto_translation
 *        namespace will use this translator to translate python exceptions to C++
 *        exceptions.
 */
namespace exception_translator {

/**
 * @brief This function sets the global exception translator to a copy of the given
 *        translator.
 * @param translator A copy of this translator will be made
 */
void set(boost_python_exception::exception_translator const & translator);

/**
 * @brief This function sets the global exception translator to the default exception translator
 *        as produced by create_standard_exception_translator().
 */
void set_default();

/**
 * @brief This function clears the global exception translator. If you call this method,
 *        calls to other functions in the auto_translation namespace which yield python
 *        exceptions cannot translate errors any more.
 *
 *        Before finalizing the python interpreter, it is highly recommended to call clear().
 *        This way, any python objects which are potentially held by the translator can be
 *        deleted properly while the interpreter is still active.
 */
void clear();

/**
 * @brief Translate the given python exception to C++ exceptions given the exception
 *        translator previously registered with a call to set().
 * @param info Contains information on the python exception
 * @throw unspecified Throws whatever exception is thrown by the currently registered
 *        translator.
 * @throw std::logic_error Throws a logic error in case no translator is registered
 */
void translate(exception_info const & info);

};

} }



#endif
