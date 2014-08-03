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
run the build. Here are the steps::

     python waf configure
     python waf build

The build output will be in ``build_directory``.
