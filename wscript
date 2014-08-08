import os
import subprocess
import sys

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


def configure(conf):
    conf.load('compiler_cxx boost python')
    conf.check_python_headers()
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
