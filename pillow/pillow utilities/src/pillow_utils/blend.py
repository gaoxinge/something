from PIL import Image
import numpy as np
from scipy.sparse import lil_matrix, linalg


__all__ = [
    "alpha_blend",
    "grad_blend",
    "poisson_blend",
]


def alpha_blend(im1, im2, box):
    """https://stackoverflow.com/questions/9014729/manually-alpha-blending-an-rgba-pixel-with-an-rgb-pixel
    :param im1: "RGB" mode
    :param im2: "RGBA" mode
    :param box: box
    :return: im1
    """
    im1_array = np.array(im1)
    im2_array = np.array(im2)
    w, h = im2.size
    for j in range(w):
        for i in range(h):
            i_ = i + box[1]
            j_ = j + box[0]

            alpha = im2_array[i, j, 3] / 255
            beta = alpha
            gamma = 1 - alpha

            im1_array[i_, j_, 0] = im1_array[i_, j_, 0] * gamma + im2_array[i, j, 0] * beta
            im1_array[i_, j_, 1] = im1_array[i_, j_, 1] * gamma + im2_array[i, j, 1] * beta
            im1_array[i_, j_, 2] = im1_array[i_, j_, 2] * gamma + im2_array[i, j, 2] * beta
    return Image.fromarray(im1_array)


def grad_blend(im1, im2, box):
    """http://courses.cs.vt.edu/~masc1044/L20-BlendingChromakey/Blending.html
    :param im1: "RGB" mode
    :param im2: "RGBA" mode
    :param box: box
    :return: im1
    """
    im1_array = np.array(im1)
    im2_array = np.array(im2)
    w, h = im2.size
    for j in range(w):
        for i in range(h):
            i_ = i + box[1]
            j_ = j + box[0]

            alpha = im2_array[i, j, 3] / 255
            beta = alpha * max(1 - i / h, 1 - j / w)
            gamma = 1 - beta

            im1_array[i_, j_, 0] = im1_array[i_, j_, 0] * gamma + im2_array[i, j, 0] * beta
            im1_array[i_, j_, 1] = im1_array[i_, j_, 1] * gamma + im2_array[i, j, 1] * beta
            im1_array[i_, j_, 2] = im1_array[i_, j_, 2] * gamma + im2_array[i, j, 2] * beta
    return Image.fromarray(im1_array)


# poisson blend
#
# reference:
# - http://lafarren.com/image-completer/pie2003.pdf
# - http://eric-yuan.me/poisson-blending/
# - https://blog.csdn.net/hjimce/article/details/45716603
# - https://github.com/willemmanuel/poisson-image-editing
INSIDE = 0
BOUND = 1
OUTSIDE = 2


def position(i, j, mask_array, box):
    h, w = mask_array.shape
    _i = i - box[1]
    _j = j - box[0]

    if _i < 0 or _i >= h or _j < 0 or _j >= w or mask_array[_i, _j] == 0:
        return OUTSIDE

    for __i, __j in [(_i - 1, _j), (_i, _j - 1), (_i + 1, _j), (_i, _j + 1)]:
        if __i < 0 or __i >= h or __j < 0 or __j >= w or mask_array[__i, __j] == 0:
            return BOUND

    return INSIDE


def draw_position(im_array, mask_array, box):
    """test position"""
    h, w, _ = im_array.shape
    for j in range(w):
        for i in range(h):
            pos = position(i, j, mask_array, box)
            if pos in [INSIDE, BOUND]:
                _i = i - box[1]
                _j = j - box[0]
                im_array[i, j, :] = mask_array[_i, _j]
            else:
                im_array[i, j, :] = 0
    return im_array


def get_ijs(mask_array, box):
    nonzero = np.nonzero(mask_array)
    return list(zip(nonzero[0] + box[1], nonzero[1] + box[0]))


def get_A(ijs):
    N = len(ijs)
    A = lil_matrix((N, N))
    for index1, ij1 in enumerate(ijs):
        for index2, ij2 in enumerate(ijs):
            if index2 < index1:
                continue

            i, j = ij2
            if ij1 == (i, j):
                A[index1, index2] = 4
            elif ij1 in [(i - 1, j), (i, j - 1), (i + 1, j), (i, j + 1)]:
                A[index1, index2] = -1
                A[index2, index1] = -1
    return A


def get_b(ijs, rgb, im1_array, im2_array, mask_array, box):
    N = len(ijs)
    b = np.zeros(N)
    h, w, _ = im1_array.shape
    _h, _w, _ = im2_array.shape
    for index, ij in enumerate(ijs):
        i, j = ij
        _i = i - box[1]
        _j = j - box[0]

        b[index] = 4 * im2_array[_i, _j, rgb]
        for __i, __j in [(_i - 1, _j), (_i, _j - 1), (_i + 1, _j), (_i, _j + 1)]:
            if 0 <= __i < _h and 0 <= __j < _w:
                b[index] -= im2_array[__i, __j, rgb]

        if position(i, j, mask_array, box) == BOUND:
            for i_, j_ in [(i - 1, j), (i,  j - 1), (i + 1, j), (i, j + 1)]:
                if 0 <= i_ < h and 0 <= j_ < w and position(i_, j_, mask_array, box) == OUTSIDE:
                    b[index] += im1_array[i_, j_, rgb]
    return b


def poisson_blend(im1, im2, box):
    """
    :param im1: "RGB" mode
    :param im2: "RGBA" mode
    :param box: box
    :return: im1
    """
    im1_array = np.array(im1)
    im2_array = np.array(im2)
    mask_array = im2_array[:, :, 3]

    ijs = get_ijs(mask_array, box)
    A = get_A(ijs)
    b_r = get_b(ijs, 0, im1_array, im2_array, mask_array, box)
    b_g = get_b(ijs, 1, im1_array, im2_array, mask_array, box)
    b_b = get_b(ijs, 2, im1_array, im2_array, mask_array, box)
    r = linalg.cg(A, b_r)
    g = linalg.cg(A, b_g)
    b = linalg.cg(A, b_b)
    for index, ij in enumerate(ijs):
        i, j = ij
        im1_array[i, j, 0] = r[0][index]
        im1_array[i, j, 1] = g[0][index]
        im1_array[i, j, 2] = b[0][index]
    return Image.fromarray(im1_array)
