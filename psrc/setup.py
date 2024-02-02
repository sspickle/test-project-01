from distutils.core import setup, Extension
from Cython.Build import cythonize

setup(name='proj1_impl',
      version='1.0',
      ext_modules = cythonize(Extension("p1_impl", ["psrc/cimpl.pyx"],
                                        extra_objects=["build/impl.o"],
                                        include_dirs=["src/."]
                                        )
                            )
)
