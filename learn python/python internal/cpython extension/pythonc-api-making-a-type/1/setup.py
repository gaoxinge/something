from distutils.core import setup, Extension

setup(
    ext_modules=[
        Extension("ccv", sources=["ccv.c"])
    ]
)