from distutils.core import setup, Extension

setup(
    name="foo",
    version="0.1",
    ext_modules=[
        Extension("foo", ["foo.c"])
    ]
)