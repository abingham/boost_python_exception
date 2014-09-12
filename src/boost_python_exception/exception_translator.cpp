#include <boost_python_exception/exception_translator.hpp>

#include <boost/foreach.hpp>

using namespace boost::python;

namespace boost_python_exception {

void exception_translator::translate(exception_info const & excInfo) const
{
    if (excInfo.type.is_none()) return;

    BOOST_FOREACH(mapping const & mapping, exception_translators_)
    {
        if ( PyErr_GivenExceptionMatches(excInfo.type.ptr(), mapping.first.ptr()) )
        {
            mapping.second(excInfo);
            return;
        }
    }

    if (PyErr_GivenExceptionMatches(excInfo.type.ptr(), PyExc_Exception)) {
    	throw_with_python_info<exception>(excInfo);
    }

    throw exception("<unknown non-standard exception>", "", extract_traceback(excInfo.traceback));
}

bool exception_translator::add(boost::python::object excType,
                               thrower thrower)
{
    BOOST_FOREACH(mapping& mapping, exception_translators_)
    {
        if (mapping.first == excType)
        {
            mapping.second = thrower;
            return true;
        }
    }

    exception_translators_.push_back(mapping(excType, thrower));
    return false;
}

bool exception_translator::remove(boost::python::object excType)
{
    for (exception_translators::iterator itr = exception_translators_.begin();
         itr != exception_translators_.end();
         ++itr)
    {
        if (itr->first == excType)
        {
            exception_translators_.erase(itr);
            return true;
        }
    }

    return false;
}

}
