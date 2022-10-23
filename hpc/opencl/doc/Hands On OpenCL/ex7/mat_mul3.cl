__kernel void mat_mul(const int N, 
                      __global float *A, 
                      __global float *B,
                      __global float *C,
                      __local float *Bwrk) {
    int i = get_global_id(0);
    int iloc = get_local_id(0);
    int nloc = get_local_size(0);
    
    float Awrk[1024]; // set 1024 instead of N
    for (int k = 0; k < N; k++) {
        Awrk[k] = A[i * N + k];
    }
    
    for (int j = 0; j < N; j++) {
        for (int k = iloc; k < N; k += nloc) {
            Bwrk[k] = B[k * N + j];
        }
        barrier(CLK_LOCAL_MEM_FENCE);

        float tmp = 0.0f;
        for (int k = 0; k < N; k++) {
            tmp += Awrk[k] * Bwrk[k]; 
        }
        C[i * N + j] = tmp;
        barrier(CLK_LOCAL_MEM_FENCE); // why set fence here?
    }
}