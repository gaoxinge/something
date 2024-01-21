from distutils.core import setup, Extension

setup(
    name="helloworld",
    version="0.0.1",
    ext_modules=[
        Extension("helloworld", ["helloworld.c"])
    ]
)
