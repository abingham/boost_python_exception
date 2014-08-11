#include <boost_python_exception/exception_translator.hpp>

#include <boost/foreach.hpp>

using namespace boost::python;

namespace boost_python_exception {

void exception_translator::translate(const exception_info& excInfo)
{
    if (excInfo.type.is_none()) return;

    BOOST_FOREACH(const mapping& mapping, map_)
    {
        if (PyErr_GivenExceptionMatches(mapping.first.ptr(),
                                        excInfo.type.ptr()))
        {
            mapping.second(excInfo);

            return;
        }
    }
}

bool exception_translator::add(boost::python::object excType,
                               Thrower thrower)
{
    BOOST_FOREACH(mapping& mapping, map_)
    {
        if (mapping.first == excType)
        {
            mapping.second = thrower;
            return true;
        }
    }

    map_.push_back(mapping(excType, thrower));
    return false;
}

bool exception_translator::remove(boost::python::object excType)
{
    for (throw_map::iterator itr = map_.begin();
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
