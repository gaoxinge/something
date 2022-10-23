__kernel void mat_mul(const int N, 
                      __global float *A, 
                      __global float *B,
                      __global float *C) {
    int i = get_global_id(0);
    
    float Awrk[1024]; // set 1024 instead of N
    for (int k = 0; k < N; k++) {
        Awrk[k] = A[i * N + k];
    }
    
    for (int j = 0; j < N; j++) {
        float tmp = 0.0f;
        for (int k = 0; k < N; k++) {
            tmp += Awrk[k] * B[k * N + j]; 
        }
        C[i * N + j] = tmp;
    }
}