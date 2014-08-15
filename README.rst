`Travis CI <https://travis-ci.org/abingham/boost_python_exception>`_ |build-status|

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

Troubleshooting
===============

Matching up Python and Boost.Python versions
--------------------------------------------

The main place you might have trouble is making sure that you link
against the same Python library as Boost.Python. This can be tricky,
but use your system tools (e.g. ``otool``, ``ldd``, ``dependency
walker``, and so forth) to figure it out. In general, this mismatch
will not be apparent except that the test suite will die miserably
rather than pass all tests gloriously.

Hopefully we can find a way to figure this out for you (or at least
detect the problem) sometime.

Mac OSX + Homebrew problems
---------------------------

It appears that homebrew does not install libpython into
/usr/local/lib, and this causes problems since waf expects it to be
there. So, if you experience wierd problems on OSX you may need to
create a link for libpython::

   % sudo ln -s /usr/local/Cellar/python/2.7.6_1/Frameworks/Python.framework/Versions/2.7/lib/libpython2.7.dylib /usr/local/lib

Or something like that.

This problem manifests itself by our build products linking against a
different libpython than libboost_python does. To see if you're
experiencing this problem, you can use otool. First, see which
libboost_python you're linking against::

  % otool -L build_directory/src/test/boost_python_exception_tests | grep libboost_python
  ... look for the path to libboost_python.dylib ...

Then run otool over that libboost_python::

  % otool -L <path to libboost_python>

If they're linking to different libpython's, then you're seeing the problem.

.. Build status badge
.. |build-status|
   image:: https://secure.travis-ci.org/abingham/boost_python_exception.png
           ?branch=master
   :target: http://travis-ci.org/abingham/boost_python_exception
   :alt: Build Status
