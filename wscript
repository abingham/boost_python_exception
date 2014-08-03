import os
import subprocess

top = '.'
out = 'build_directory'


def options(opt):
    opt.load('compiler_cxx')


def configure(conf):
    # TODO: Need to do something better for finding python-config.
    python_config = '/usr/local/bin/python-config'
    python_cflags = subprocess.check_output(
        [python_config, '--cflags']).split()
    python_ldflags = subprocess.check_output(
        [python_config, '--ldflags']).split()

    conf.load('compiler_cxx')
    conf.env.append_value('CXXFLAGS', python_cflags)
    conf.env.append_value('LINKFLAGS', python_ldflags)

    # TODO: This is for boost.python linking. Need to find a more
    # cross-platform/robust way to do this.
    conf.env.append_value('LIBPATH', ['/usr/local/lib'])
    conf.env.append_value('LIB', ['boost_python'])

    # This lets us include our own headers with the correct path
    # prefixes.
    conf.env.append_value('INCLUDES', [os.path.abspath('src')])


def build(bld):
    bld.recurse('src/boost_python_exception')
