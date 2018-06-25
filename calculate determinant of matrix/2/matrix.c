#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float** element;
    unsigned row, col;
} Matrix;

_declspec(dllexport) void matrix_init(Matrix* matrix, float* array, unsigned row, unsigned col) {
    matrix->element = (float**) malloc(row * sizeof(float*));
    for (unsigned i = 0; i < row; i++)
        matrix->element[i] = (float*) malloc(col * sizeof(float));
    
    for (unsigned i = 0; i < row; i++)
        for (unsigned j = 0; j < col; j++)
            matrix->element[i][j] = array[col * i + j];
        
    matrix->row = row;
    matrix->col = col;
}

_declspec(dllexport) void matrix_del(Matrix* matrix) {
    for (unsigned i = 0; i < matrix->row; i++)
        free(matrix->element[i]);
    free(matrix->element);
}

void __exchange(Matrix* matrix, unsigned i1, unsigned i2) {
    float* tmp;
    tmp = matrix->element[i1];
    matrix->element[i1] = matrix->element[i2];
    matrix->element[i2] = tmp;
}

float __determinant(Matrix* matrix, unsigned dim) {
    // 如果矩阵是1*1，那么返回matrix[0][0]
    if (dim == 1)              
        return matrix->element[0][0];
    
    // 矩阵从下往上遍历，寻找满足最后一列不为0的行
    int index;
    for (index = dim - 1; index > -1; index--)
        if (matrix->element[index][dim - 1] != 0)
            break;
    
    // 如果没有找到，那么为奇异矩阵，返回0
    if (index == -1)
        return 0;
    
    // 查看是否需要换行，使得最后一行的最后一个元素不为0
    double sign = 1;
    if (index != dim - 1) {
        __exchange(matrix, index, dim - 1);
        sign = -1;
    }
    
    // 利用最后一行的最后一个元素进行消元
    double last_element = matrix->element[dim - 1][dim - 1];
    for (unsigned i = 0; i < dim - 1; i++) {
        float factor = matrix->element[i][dim - 1] / last_element;
        matrix->element[i][dim - 1] = 0;
        for (unsigned j = 0; j < dim - 1; j++)
            matrix->element[i][j] -= factor * matrix->element[dim - 1][j];
    }

    return sign * last_element * __determinant(matrix, dim - 1);
}

_declspec(dllexport) float matrix_determinant(Matrix* matrix) {
    return __determinant(matrix, matrix->row);
}

int main() {
    Matrix matrix;
    float a[] = {
        1, -1, 1, -2, 
        2, 0, -1, 4, 
        3, 2, 1, 0, 
        -1, 2, -1, 2
    };
    matrix_init(&matrix, a, 4, 4);
    printf("row=%u col=%u\n", matrix.row, matrix.col);
    for (unsigned i = 0; i < matrix.row; i++) {
        for (unsigned j = 0; j < matrix.col; j++)
            printf("%-2.f ", matrix.element[i][j]);
        printf("\n");
    }
    printf("result=%.f ", matrix_determinant(&matrix));
    matrix_del(&matrix);
    
    return 0;
}




