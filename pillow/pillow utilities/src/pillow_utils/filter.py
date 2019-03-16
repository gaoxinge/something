from PIL import ImageFilter

__all__ = [
    "IdFilter",
    "MeanFilter",
    "GuassianFilter",
    "SharpenV1Filter",
    "SharpenV2Filter",
    "PrewittHFilter",
    "PrewittVFilter",
    "SobelHFilter",
    "SobelVFilter",
    "LaplacianFilter"
]


class IdFilter(ImageFilter.BuiltinFilter):
    """https://blog.csdn.net/chaipp0607/article/details/72236892"""
    name = "Id Filter"
    filterargs = (3, 3), 1, 0, (
        0, 0, 0,
        0, 1, 0,
        0, 0, 0
    )


class MeanFilter(ImageFilter.BuiltinFilter):
    """https://blog.csdn.net/chaipp0607/article/details/72236892"""
    name = "Mean Filter"
    filterargs = (3, 3), 1, 0, (
        1/9, 1/9, 1/9,
        1/9, 1/9, 1/9,
        1/9, 1/9, 1/9
    )


class GuassianFilter(ImageFilter.BuiltinFilter):
    """https://blog.csdn.net/chaipp0607/article/details/72236892"""
    name = "Guassian Filter"
    filterargs = (3, 3), 1, 0, (
        1/16, 2/16, 1/16,
        2/16, 4/16, 2/16,
        1/16, 2/16, 1/16
    )


class SharpenV1Filter(ImageFilter.BuiltinFilter):
    """https://blog.csdn.net/chaipp0607/article/details/72236892"""
    name = "Sharpen V1 Filter"
    filterargs = (3, 3), 1, 0, (
        -1, -1, -1,
        -1, 9, -1,
        -1, -1, -1
    )


class SharpenV2Filter(ImageFilter.BuiltinFilter):
    """https://blog.csdn.net/chaipp0607/article/details/72236892"""
    name = "Shapen V2 Filter"
    filterargs = (3, 3), 1, 0, (
        0, -1, 0,
        -1, 5, -1,
        0, -1, 0
    )


class PrewittHFilter(ImageFilter.BuiltinFilter):
    """https://blog.csdn.net/chaipp0607/article/details/72236892"""
    name = "Prewitt H Filter"
    filterargs = (3, 3), 1, 0, (
        -1, 0, 1,
        -1, 0, 1,
        -1, 0, 1
    )


class PrewittVFilter(ImageFilter.BuiltinFilter):
    """https://blog.csdn.net/chaipp0607/article/details/72236892"""
    name = "Prewitt V Filter"
    filterargs = (3, 3), 1, 0, (
        -1, -1, -1,
        0, 0, 0,
        1, 1, 1
    )


class SobelHFilter(ImageFilter.BuiltinFilter):
    """https://blog.csdn.net/chaipp0607/article/details/72236892"""
    name = "Sobel H Filter"
    filterargs = (3, 3), 1, 0, (
        -1, 0, 1,
        -2, 0, 2,
        -1, 0, 1
    )


class SobelVFilter(ImageFilter.BuiltinFilter):
    """https://blog.csdn.net/chaipp0607/article/details/72236892"""
    name = "Sobel V Filter"
    filterargs = (3, 3), 1, 0, (
        -1, -2, -1,
        0, 0, 0,
        1, 2, 1
    )


class LaplacianFilter(ImageFilter.BuiltinFilter):
    """https://blog.csdn.net/chaipp0607/article/details/72236892"""
    name = "Laplacian Filter"
    filterargs = (3, 3), 1, 0, (
        1, 1, 1,
        1, -8, 1,
        1, 1, 1
    )
