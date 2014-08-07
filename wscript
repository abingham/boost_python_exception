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
    python_libs = [l[2:] for l in subprocess.check_output(
        [conf.env.PYTHON_CONFIG, '--libs']).split()]

    conf.env.append_value('CXXFLAGS', python_cflags)
    conf.env.append_value('LINKFLAGS', python_ldflags)
    
    # TODO: We have to list the libs separately like this so that we 
    # can force them to come after the source file in the link command. 
    # This appeases gcc. It's kludgy, but until we can get the python 
    # tool working properly I think it's necessary.
    conf.env.append_value('LIB', python_libs)

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
