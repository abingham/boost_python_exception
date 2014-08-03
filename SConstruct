import os
import subprocess


env = Environment()

################################################################################
# Python configuration

python_config = '/usr/local/bin/python-config'
python_cflags = subprocess.check_output([python_config, '--cflags']).split()
python_ldflags = subprocess.check_output([python_config, '--ldflags']).split()

env.Append(CXXFLAGS=python_cflags)
env.Append(LINKFLAGS=python_ldflags)

################################################################################
# Boost configuration

env.Append(LIBPATH=[
    '/usr/local/lib',
])

env.Append(LIBS=[
    'boost_python',
    'boost_unit_test_framework',
])

env.SConscript(
    os.path.join('src', 'test', 'SConscript'),
    exports='env')