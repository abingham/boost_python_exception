#include <boost_python_exception/traceback.hpp>

#include <boost/test/unit_test.hpp>

#include <sstream>

namespace bpe = boost_python_exception;


BOOST_AUTO_TEST_SUITE(traceback)

BOOST_AUTO_TEST_CASE(stream_inserter)
{
    bpe::traceback traceback;
    bpe::traceback_step const step_1 = {42, "file_1", "source_1"};
    bpe::traceback_step const step_2 = {23, "file_2", "source_2"};
    traceback.push_back(step_1);
    traceback.push_back(step_2);

    std::ostringstream expected;
    expected << step_1 << "\n" << step_2 << "\n";

    std::ostringstream actual;
    actual << traceback;
    BOOST_CHECK_EQUAL(expected.str(), actual.str());
}

BOOST_AUTO_TEST_SUITE_END()
