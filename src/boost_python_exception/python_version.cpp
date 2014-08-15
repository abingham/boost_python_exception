#include <boost_python_exception/python_version.hpp>

#include <patchlevel.h> // python header which contains relevant information

namespace boost_python_exception {

python_version::python_version() :
    major(PY_MAJOR_VERSION),
    minor(PY_MINOR_VERSION),
    micro(PY_MICRO_VERSION)
{
}

}
