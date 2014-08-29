#include <boost_python_exception/traceback.hpp>

#include <iostream>

namespace boost_python_exception {

std::ostream & operator<<(std::ostream & stream, traceback const & traceback)
{
	for (traceback::const_iterator it = traceback.begin(); it != traceback.end(); ++it) {
		stream << *it << "\n";
	}
	return stream;
}

}

