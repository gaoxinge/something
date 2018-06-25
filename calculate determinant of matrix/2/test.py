import time
import numpy as np
from ctypes import *


def profile(func):
    def wrapper(*args, **kwargs):
        s = time.time()
        result = func(*args, **kwargs)
        e = time.time()
        print("time:", e-s)
        return result
    return wrapper
    

# test dll
matrix_dll = cdll.LoadLibrary("matrix.dll")

class Matrix(Structure):
    _fields_ = [
        ("element", POINTER(POINTER(c_float))),
        ("row", c_uint),
        ("col", c_uint)
    ]
    
matrix_init = matrix_dll.matrix_init
matrix_del = matrix_dll.matrix_del
matrix_determinant = matrix_dll.matrix_determinant
matrix_determinant.restype = c_float

matrix = Matrix()
array = (c_float * 16)(
    1, -1, 1, -2, 
    2, 0, -1, 4, 
    3, 2, 1, 0, 
    -1, 2, -1, 2
)
matrix_init(pointer(matrix), array, 4, 4)

@profile
def test_dll():
    l = []
    for _ in range(10000):
        l.append(matrix_determinant(pointer(matrix)))
    return l[0]

print test_dll()
    
matrix_del(pointer(matrix))


# test numpy
a = np.array([[1, -1, 1, -2], [2, 0, -1, 4], [3, 2, 1, 0], [-1, 2, -1, 2]])

@profile
def test_numpy():
    l = []
    for _ in range(10000):
        l.append(np.linalg.det(a))
    return l[0]
    
print test_numpy()
