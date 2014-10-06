import os
import sys

import waflib.Errors

top = '.'
out = 'build_directory'


# TODO: Need a better way to install the boost tool cleanly. This is silly.
def options(opt):
    opt.load('compiler_cxx python')

    try:
        opt.load('boost')
    except ImportError:
        print('Recived ImportError during option processing: {}'.format(
            sys.exc_info()))
        print('If this is about "boost", then you can (probably)'
              'safely ignore it.')


def load_if_exists(conf, tool):
    """Try to load a tool, but ignore errors if it doesn't exist.

    This is for e.g. loading optional tools, the absence of which
    won't impact the correctness of the build.
    """
    try:
        conf.load(tool)
    except waflib.Errors.ConfigurationError:
        print('Extra tool "{}" not found. Ignoring.'.format(tool))


def configure(conf):
    conf.load('compiler_cxx boost python')
    load_if_exists(conf, 'clang_compilation_database')
    conf.check_python_headers()

    # On some systems, boost_python does not link against python
    # This line avoids missing references
    conf.env.append_value('LIB', conf.env['LIB_PYEMBED'])

    conf.check_boost(lib='system python',
                     mt=False,
                     stlib=False)

    # This lets us include our own headers with the correct path
    # prefixes.
    conf.env.append_value('INCLUDES', [os.path.abspath('src')])

    conf.recurse('src/test')


def build(bld):
    bld.recurse('src/boost_python_exception')
    bld.recurse('src/test')
