__kernel void vec_iii_1d(__global int *a, __global int *b,
                         __global int *c)
{
  size_t tid = get_global_id(0);
  int tmp = a[tid];
  for(int i=b[tid]; i > 0; i--) tmp++;
  c[tid] = tmp;
}
