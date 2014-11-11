#include "clear_global_translator.hpp"

#include <boost_python_exception/auto_translation/exception_translator.hpp>

using boost_python_exception::auto_translation::exception_translator::clear;

namespace test { namespace fixtures {

clear_global_translator::clear_global_translator()
{
    clear();
}

clear_global_translator::~clear_global_translator()
{
    clear();
}

}
}
