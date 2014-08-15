#include <boost_python_exception/util.hpp>

#include <boost/python/import.hpp>

using namespace boost::python;

namespace boost_python_exception {

object builtins()
{
#if PY_MAJOR_VERSION == 2
    return import("__builtin__");
#elif PY_MAJOR_VERSION == 3
    return import("builtins");
#endif
}

}
