import unittest
import numpy as np
from PIL import Image
from pillow_utils import alpha_blend, grad_blend, poisson_blend
from pillow_utils.blend import draw_position


class Blend(unittest.TestCase):

    def test_alpha_blend(self):
        im1 = Image.open("image/1.jpg")
        im2 = Image.open("image/1.png")
        im1 = alpha_blend(im1, im2, (483, 937))
        im1.save("test.jpg")

    def test_grad_blend(self):
        im1 = Image.open("image/1.jpg")
        im2 = Image.open("image/1.png")
        im1 = grad_blend(im1, im2, (483, 937))
        im1.save("test.jpg")

    def test_draw_position(self):
        im1 = Image.open("image/1.jpg")
        im2 = Image.open("image/1.png")

        im1_array = np.array(im1)
        im2_array = np.array(im2)
        mask_array = im2_array[:, :, 3]

        im1_array = draw_position(im1_array, mask_array, (483, 936))
        im1 = Image.fromarray(im1_array)
        im1.save("test.jpg")

    def test_poisson_blend(self):
        im1 = Image.open("image/1.jpg")
        im2 = Image.open("image/1.png")
        im1 = poisson_blend(im1, im2, (483, 937))
        im1.save("test.jpg")
