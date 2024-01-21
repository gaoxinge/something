from distutils.core import setup, Extension

setup(
    name="pyrev",
    version="0.1",
    ext_modules=[
        Extension("pyrev", ["pyrev.c"])
    ]
)