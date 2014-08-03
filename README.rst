========================
 boost_python_exception
========================

This is a small library that makes it easier to work with Python
exceptions in Boost.Python. The primary target for this project is
people who are embedding Python in C++ programs and need to deal with
exceptions coming from Python.

Building
========

The build system is based on `waf
<https://code.google.com/p/waf/>`_. You just need Python installed to
run the build. The first time you run the build (or after a
``distclean``) you need to install the boost tool::

     % python waf update --files=boost

After that, the standard waf commands are all you need::

     % python waf configure
     % python waf build

The build output will be in ``build_directory``.

Running tests
=============

The tests are built using the `Boost Test Library
<http://www.boost.org/doc/libs/1_56_0_b1/libs/test/doc/html/index.html>`_. To
run the tests, first do a full build (see above.) Then::

    % ./build_directory/src/test/boost_python_exception_tests

This will run all of the tests.
