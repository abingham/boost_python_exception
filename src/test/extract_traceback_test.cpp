#include <boost_python_exception/extract_traceback.hpp>

#include <boost/test/unit_test.hpp>

#include <sstream>

#include <boost/python/import.hpp>
#include <boost/python/exec.hpp>

#include <boost_python_exception/get_exception_info.hpp>

#include "helpers/execute_python_code.hpp"
#include "helpers/fixtures/clear_python_errors.hpp"

namespace bp = boost::python;
namespace bpe = boost_python_exception;

namespace {

 void verify_traceback(std::string const & expected_traceback, bp::object py_traceback)
 {
  bpe::traceback tb = bpe::extract_traceback(py_traceback);

  std::ostringstream actual;
  for (bpe::traceback::const_iterator it = tb.begin(); it != tb.end(); ++it) {
   actual << *it << "\n";
  }

  BOOST_CHECK_EQUAL(expected_traceback, actual.str());
 }

 void test_traceback(std::string const & python_code, std::string const & expected_traceback)
 {
  test::execute_python_code_in_main_module(python_code, true);
  bpe::exception_info const info = bpe::get_exception_info();
  verify_traceback(expected_traceback, info.traceback);
 }

}

BOOST_FIXTURE_TEST_SUITE(extract_traceback, test::fixtures::clear_python_errors)

BOOST_AUTO_TEST_CASE(no_error)
{
 std::string const python_code("1 + 2");
 std::string const expected_traceback("");

 test_traceback(python_code, expected_traceback);
}

BOOST_AUTO_TEST_CASE(single_line_with_error)
{
 std::string const python_code("1 + \"2\"");
 std::string const expected_traceback("File \"<string>\", line 1, in <module>\n");

 test_traceback(python_code, expected_traceback);
}

BOOST_AUTO_TEST_CASE(function_call_with_error)
{
 std::string const python_code(
   "def main():\n"
   "\t 1 + \"2\"\n"
   "if __name__ == \"__main__\":\n"
   "\t main()\n"
  );

 std::string const expected_traceback(
   "File \"<string>\", line 4, in <module>\n"
   "File \"<string>\", line 2, in main\n"
  );

 test_traceback(python_code, expected_traceback);
}

BOOST_AUTO_TEST_SUITE_END()
