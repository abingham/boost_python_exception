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

namespace boost_python_exception {

/** A registry of python-to-c++ exception translations.
 */
class exception_translator
{
public:

    void translate(boost::python::tuple excInfo);

    typedef boost::function<void(boost::python::object,
                                 boost::python::object,
                                 boost::python::object)>
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
void throw_(boost::python::object /* type */,
            boost::python::object /* value */,
            boost::python::object /* traceback */)
{
    throw Exc();
}

typedef boost::error_info<struct tag_exc_info, boost::python::tuple> exc_info;

template <typename Exc>
void throw_with_python_info(boost::python::object type,
                            boost::python::object value,
                            boost::python::object traceback)
{
    Exc e;

    boost::python::tuple t =
        boost::python::make_tuple(type, value, traceback);
    e << exc_info(t);

    throw e;
}

}

#endif
