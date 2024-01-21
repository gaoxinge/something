from distutils.core import setup, Extension

setup(
    name="dummy",
    version="0.0.1",
    ext_modules=[
        Extension("dummy", ["dummy.c"])
    ]
)
