#include <boost_python_exception/exception_translator.hpp>

#include <boost/foreach.hpp>

using namespace boost::python;

namespace boost_python_exception {

namespace {

	void handle_default_exception(exception_info const & info)
	{
	    if (PyErr_GivenExceptionMatches(info.type.ptr(), PyExc_Exception)) {
	    	throw_with_python_info<exception>(info);
	    }

	    throw exception("<unknown non-standard exception>", "", extract_traceback(info.traceback));
	}

}

void exception_translator::translate(exception_info const & info) const
{
    if (info.type.is_none()) return;

    BOOST_FOREACH(mapping const & mapping, exception_translators_)
    {
        if ( PyErr_GivenExceptionMatches(info.type.ptr(), mapping.first.ptr()) )
        {
            mapping.second(info);
            return;
        }
    }

    handle_default_exception(info);
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
