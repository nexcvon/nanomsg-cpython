"""setup.py"""

from setuptools import setup, Extension

setup(
    name="nanomsg-cpython",
    version="1.0",
    ext_modules=[Extension(
        "nanomsg",
        ["src/nanomsg.c"],
        define_macros=[("NN_STATIC_LIB",1)],
        include_dirs=["include"],
        library_dirs=["lib", "C:/Python34/libs"],
        libraries=["nanomsg", "ws2_32", "mswsock", "advapi32", "python34"]
    )]
)
