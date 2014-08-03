import os
import subprocess
import sys

top = '.'
out = 'build_directory'


# TODO: Need a better way to install the boost tool cleanly. This is silly.
def options(opt):
    try:
        opt.load('compiler_cxx boost')
    except ImportError:
        print('Recived ImportError during option processing: {}'.format(
            sys.exc_info()))
        print('If this is about "boost", then you can (probably)'
              'safely ignore it.')


def configure(conf):
    # TODO: Need to do something better for finding python-config.
    python_config = '/usr/local/bin/python-config'
    python_cflags = subprocess.check_output(
        [python_config, '--cflags']).split()
    python_ldflags = subprocess.check_output(
        [python_config, '--ldflags']).split()

    conf.load('compiler_cxx boost')

    conf.check_boost(lib='system python',
                     mt=False,
                     stlib=False)

    conf.check_boost(lib='unit_test',
                     mt=False,
                     stlib=False,
                     uselib_store='BOOST_UNIT_TEST')
    
    conf.env.append_value('CXXFLAGS', python_cflags)
    conf.env.append_value('LINKFLAGS', python_ldflags)

    # This lets us include our own headers with the correct path
    # prefixes.
    conf.env.append_value('INCLUDES', [os.path.abspath('src')])


def build(bld):
    bld.recurse('src/boost_python_exception')
