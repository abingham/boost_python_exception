#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION__EXCEPTION_TRANSLATOR_HPP
#define INCLUDE_BOOST_PYTHON_EXCEPTION__EXCEPTION_TRANSLATOR_HPP

#include <Python.h>

#include <utility>
#include <vector>

#include <boost/exception/info.hpp>
#include <boost/function.hpp>
#include <boost/python/import.hpp>
#include <boost/python/object.hpp>
#include <boost/python/tuple.hpp>

#include <boost_python_exception/exception_info.hpp>

namespace boost_python_exception {

/** A registry of python-to-c++ exception translations.
 */
class exception_translator
{
public:

    void translate(const exception_info& excInfo);

    typedef boost::function<void(const exception_info&)>
    Thrower;

    bool add(boost::python::object excType,
             Thrower thrower);

    bool remove(boost::python::object excType);

private:
    typedef std::pair<boost::python::object, Thrower> Mapping;
    typedef std::vector<Mapping> ThrowMap;
    ThrowMap map_;
};

template <typename Exc>
void throw_(const exception_info&)
{
    throw Exc();
}

typedef boost::error_info<struct tag_exc_info, exception_info> exc_info;

template <typename Exc>
void throw_with_python_info(const exception_info& e)
{
    throw Exc() << exc_info(e);
}

}

#endif
