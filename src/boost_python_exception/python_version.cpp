#include <boost_python_exception/python_version.hpp>

#include <iostream>

#include <patchlevel.h> // python header which contains relevant information




namespace boost_python_exception {

version::version(unsigned int major, unsigned int minor, unsigned int micro) :
	major(major),
	minor(minor),
	micro(micro)
{
}

std::ostream& operator<<(std::ostream& lhs, version const& rhs)
{
	char const point = '.';
	return lhs << rhs.major << point << rhs.minor << point << rhs.micro;
}

bool operator==(version const& lhs, version const& rhs)
{
	return lhs.major == rhs.major and lhs.minor == rhs.minor and lhs.micro == rhs.micro;
}

bool operator!=(version const& lhs, version const& rhs)
{
	return not(lhs == rhs);
}

version python_version() throw()
{
	return version(PY_MAJOR_VERSION, PY_MINOR_VERSION, PY_MICRO_VERSION);
}

}
