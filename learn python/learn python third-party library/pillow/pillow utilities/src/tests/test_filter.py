import unittest
from PIL import Image
from pillow_utils import IdFilter, MeanFilter, GuassianFilter, SharpenV1Filter, SharpenV2Filter, PrewittHFilter, \
    PrewittVFilter, SobelHFilter, SobelVFilter, LaplacianFilter


class Filter(unittest.TestCase):

    def test_id_filter(self):
        im = Image.open("image/1.jpg")
        im = im.filter(IdFilter())
        im.save("test.jpg")

    def test_mean_filter(self):
        im = Image.open("image/1.jpg")
        im = im.filter(MeanFilter())
        im.save("test.jpg")

    def test_guassian_filter(self):
        im = Image.open("image/1.jpg")
        im = im.filter(GuassianFilter())
        im.save("test.jpg")

    def test_sharpen_v1_filter(self):
        im = Image.open("image/1.jpg")
        im = im.filter(SharpenV1Filter())
        im.save("test.jpg")

    def test_shapren_v2_filter(self):
        im = Image.open("image/1.jpg")
        im = im.filter(SharpenV2Filter())
        im.save("test.jpg")

    def test_prewitt_h_filter(self):
        im = Image.open("image/1.jpg")
        im = im.filter(PrewittHFilter())
        im.save("test.jpg")

    def test_prewitt_v_filter(self):
        im = Image.open("image/1.jpg")
        im = im.filter(PrewittVFilter())
        im.save("test.jpg")

    def test_sobel_h_filter(self):
        im = Image.open("image/1.jpg")
        im = im.filter(SobelHFilter())
        im.save("test.jpg")

    def test_sobel_v_filter(self):
        im = Image.open("image/1.jpg")
        im = im.filter(SobelVFilter())
        im.save("test.jpg")

    def test_laplacian_filter(self):
        im = Image.open("image/1.jpg")
        im = im.filter(LaplacianFilter())
        im.save("test.jpg")
