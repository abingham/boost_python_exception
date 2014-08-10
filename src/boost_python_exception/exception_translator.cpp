#include <boost_python_exception/exception_translator.hpp>

using namespace boost::python;

namespace boost_python_exception {

void
exception_translator::translate(const exception_info& excInfo)
{
    if (excInfo.type.is_none()) return;

    for (ThrowMap::const_iterator itr = map_.begin();
         itr != map_.end();
         ++itr)
    {
        if (PyErr_GivenExceptionMatches(itr->first.ptr(),
                                        excInfo.type.ptr()))
        {
            itr->second(excInfo);

            return;
        }
    }
}

bool exception_translator::add(boost::python::object excType,
                               Thrower thrower)
{
    for (ThrowMap::iterator itr = map_.begin();
            itr != map_.end();
            ++itr)
    {
        if (itr->first == excType)
        {
            itr->second = thrower;
            return true;
        }
    }

    map_.push_back(Mapping(excType, thrower));
    return false;
}

bool exception_translator::remove(boost::python::object excType)
{
    for (ThrowMap::iterator itr = map_.begin();
            itr != map_.end();
            ++itr)
    {
        if (itr->first == excType)
        {
            map_.erase(itr);
            return true;
        }
    }

    return false;
}

}
