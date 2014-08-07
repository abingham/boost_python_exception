#include <test/fixtures/clear_python_errors.hpp>

#include <Python.h>

namespace fixtures {

clear_python_errors::clear_python_errors()
{
	PyErr_Clear();
}

clear_python_errors::~clear_python_errors()
{
	PyErr_Clear();
}

}
