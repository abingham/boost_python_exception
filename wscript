import os
import subprocess
import sys

top = '.'
out = 'build_directory'


# TODO: Need a better way to install the boost tool cleanly. This is silly.
def options(opt):
    opt.load('compiler_cxx')
        
    try:
        opt.load('boost')
    except ImportError:
        print('Recived ImportError during option processing: {}'.format(
            sys.exc_info()))
        print('If this is about "boost", then you can (probably)'
              'safely ignore it.')


def configure(conf):
    conf.load('compiler_cxx boost')

    # NOTE: Normally I think we'd use the python tool for python
    # stuff, but it seems to not do the right WRT homebrew. Pain in
    # the ass.
    conf.find_program('python-config', var='PYTHON_CONFIG')
    python_cflags = subprocess.check_output(
        [conf.env.PYTHON_CONFIG, '--cflags']).split()
    python_ldflags = subprocess.check_output(
        [conf.env.PYTHON_CONFIG, '--ldflags']).split()

    conf.env.append_value('CXXFLAGS', python_cflags)
    conf.env.append_value('LINKFLAGS', python_ldflags)
    
    conf.check_boost(lib='system python',
                     mt=False,
                     stlib=False)

    conf.check_boost(lib='unit_test',
                     mt=False,
                     stlib=False,
                     uselib_store='BOOST_UNIT_TEST')

    # This lets us include our own headers with the correct path
    # prefixes.
    conf.env.append_value('INCLUDES', [os.path.abspath('src')])


def build(bld):
    bld.recurse('src/boost_python_exception')
