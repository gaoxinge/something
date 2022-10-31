__kernel void calpi(
    const int N3,
    const float step,
    __global float *global_arr,
    __local float *local_arr
) {
    int global_id = get_global_id(0);
    int local_id = get_local_id(0);
    int local_size = get_local_size(0);
    int group_id = get_group_id(0);

    float tmp = 0.0f;
    for (int i = 0; i < N3; i++) {
	int j = global_id * N3 + i;
	float x = (j + 0.5f) * step;
	tmp += 4.0f / (1.0f + x * x);
    }
    local_arr[local_id] = tmp;

    barrier(CLK_LOCAL_MEM_FENCE);

    if (local_id == 0) {
        float tmp = 0.0f;
	for (int i = 0; i < local_size; i++) {
            tmp += local_arr[i];
	}
	global_arr[group_id] = tmp;
    }
}
