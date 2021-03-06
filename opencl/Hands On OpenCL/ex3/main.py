import numpy as np
import pyopencl as cl


ctx = cl.create_some_context()
queue = cl.CommandQueue(ctx)

a_np = np.random.rand(10).astype(np.float32)
b_np = np.random.rand(10).astype(np.float32)
res_np = np.empty_like(a_np)

a_g = cl.Buffer(ctx, cl.mem_flags.READ_ONLY|cl.mem_flags.COPY_HOST_PTR, hostbuf=a_np)
b_g = cl.Buffer(ctx, cl.mem_flags.READ_ONLY|cl.mem_flags.COPY_HOST_PTR, hostbuf=b_np)
res_g = cl.Buffer(ctx, cl.mem_flags.WRITE_ONLY, res_np.nbytes)

prg = cl.Program(ctx, """
__kernel void sum(__global const float *a_g, __global const float *b_g, __global float *res_g) {
    int gid = get_global_id(0);
    res_g[gid] = a_g[gid] + b_g[gid];
}
""").build()
prg.sum(queue, a_np.shape, None, a_g, b_g, res_g)

cl.enqueue_copy(queue, res_np, res_g)
print(a_np)
print(b_np)
print(res_np)