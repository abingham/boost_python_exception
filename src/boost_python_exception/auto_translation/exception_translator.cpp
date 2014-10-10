#include <boost_python_exception/auto_translation/exception_translator.hpp>

#include <stdexcept>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <boost_python_exception/exception_info.hpp>
#include <boost_python_exception/exception_translator.hpp>
#include <boost_python_exception/standard_exception_translator.hpp>

namespace boost_python_exception { namespace auto_translation {

namespace {

	boost::shared_ptr<boost_python_exception::exception_translator> & registered_translator()
	{
		static boost::shared_ptr<boost_python_exception::exception_translator> translator;
		return translator;
	}
}

void exception_translator::set(boost_python_exception::exception_translator const & translator)
{
	registered_translator() = boost::make_shared<boost_python_exception::exception_translator>(translator);
}

void exception_translator::set_default()
{
	set(create_standard_exception_translator());
}

void exception_translator::clear()
{
	registered_translator().reset();
}

void exception_translator::translate(exception_info const & info)
{
	if (registered_translator()) {
		registered_translator()->translate(info);
	} else {
		throw std::logic_error("No python to C++ exception translator is currently registered");
	}
}


} }
