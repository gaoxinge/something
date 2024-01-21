from distutils.core import setup, Extension

setup(
    ext_modules = [
        Extension("ext1", sources=["ext1.c"]),
        Extension("ext2", sources=["ext2.c"]),
        Extension("ext3", sources=["ext3.c"]),
    ],
)