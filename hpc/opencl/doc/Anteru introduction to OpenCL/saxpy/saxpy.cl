__kernel void SAXPY (__global float *x, __global float *y, float a) {
    int i = get_global_id(0);
    y[i] += a * x[i];
}
