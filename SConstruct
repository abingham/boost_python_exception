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

################################################################################
# Our own configuration

env.Append(CPPPATH=['#/src'])
env['INSTALL_DIR'] = '#/install'

source_dirs = [
    os.path.join('src', 'boost_python_exception'),
    os.path.join('src', 'test'),
]

for source_dir in source_dirs:
    env.SConscript(
        os.path.join(source_dir, 'SConscript'),
        exports='env',
        variant_dir=os.path.join('build', source_dir))
