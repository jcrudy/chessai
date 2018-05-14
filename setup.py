from distutils.core import setup
import versioneer
from setuptools import find_packages, Extension
import sys
import os
import numpy as np

# Determine whether to use Cython
if '--cythonize' in sys.argv:
    from Cython.Build.Dependencies import cythonize
    from Cython.Distutils import build_ext
    cythonize_switch = True
    del sys.argv[sys.argv.index('--cythonize')]
    ext = 'pyx'
    directives = {}
    directives['linetrace'] = False
    directives['binding'] = False
    directives['profile'] = False
    cmdclass = {'build_ext': build_ext}
else:
    from setuptools.command.build_ext import build_ext  # @NoMove @Reimport
    cythonize_switch = False
    ext = 'c'
    cmdclass = {'build_ext': build_ext}

# if '--profile' in sys.argv:
#     '''
#     First do:
#     export MACOSX_DEPLOYMENT_TARGET=10.9
#     cd easy_profiler-1.3.0
#     cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE="Release"
#     Then do:
#     make
#     Then run:
#     python setup.py build_ext --inplace --cythonize --profile
#     '''
#     print('PROFILE!')
#     profile_switch = True
#     del sys.argv[sys.argv.index('--profile')]
#     ext_args = dict(
#                     define_macros = [('BUILD_WITH_EASY_PROFILER', 1),]
# #                                       ('EASY_PROFILER_ENABLE', 1)],
#                     )
# else:
#     profile_switch = False
#     ext_args = dict()


ext_modules = [Extension('chessai.ai.bitboard', 
                         [
                          os.path.join('chessai', 'ai',
                                       'tinythread.cpp'),
                          os.path.join('chessai', 'ai',
                                       'bitboardlib.cpp'),
                          os.path.join('chessai', 'ai',
                                       'movesearch.cpp'),
                          os.path.join('chessai', 'ai',
                                       'bitboard.%s' % ext),
                          
                          ],
                         include_dirs = [
#                                          os.path.join(#'chessai', 
#                                                       'easy_profiler-1.3.0',
#                                                       'easy_profiler_core', 'include'),
                                         np.get_include()
                                         ],
#                          libraries = ['easy_profiler'],
#                          library_dirs = [os.path.join('easy_profiler-1.3.0', 'bin')],
                         extra_compile_args=['-std=c++14', '-Ofast', '-march=native', '-fomit-frame-pointer'] + (['-stdlib=libc++'] if sys.platform.lower().startswith('darwin') else []),
                        #, '-g', '-O0'
#                          **ext_args
                         ),
               Extension('chessai.sparse_data', [os.path.join('chessai', 'sparse_data.%s' % ext)],
                         include_dirs = [np.get_include()],)]

setup(name='chessai',
      version=versioneer.get_version(),
      cmdclass=versioneer.get_cmdclass(cmdclass),
      description='Chess AIs for triplebyte tournament.',
      packages=find_packages(),
      ext_modules = cythonize(ext_modules, compiler_directives=directives) if cythonize_switch else ext_modules,
      package_data = {},
      install_requires = []
     )