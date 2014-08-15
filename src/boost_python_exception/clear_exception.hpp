#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_CLEAR_EXCEPTION_HPP
#define INCLUDE_BOOST_PYTHON_EXCEPTION_CLEAR_EXCEPTION_HPP

namespace boost_python_exception {

/* Clear the current Python exception, if any.

   If there is a current Python exception, this function clears it. If
   there is no current Python exception, this function has no
   effect. In either case, after this function completes there will be
   no active Python exception.
 */
void clear_exception();

}

#endif /* INCLUDE_BOOST_PYTHON_EXCEPTION_CLEAR_EXCEPTION_HPP */
