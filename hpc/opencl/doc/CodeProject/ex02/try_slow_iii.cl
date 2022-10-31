__kernel void vec_iii_1d(__global int *a, __global int *b, 
                         __global int *c)
{
  size_t tid = get_global_id(0);
  c[tid] = a[tid];
  while(b[tid] > 0) {
    b[tid]--;
    c[tid]++;
  }
}
