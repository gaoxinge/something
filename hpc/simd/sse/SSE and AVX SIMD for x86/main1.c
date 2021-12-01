#include <stdio.h>

void farray_print(float *vals, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.2f ", vals[i]);
	if (i % 4 == 3) {
            printf("\n");
	}
    }
}

// gcc main1.c -o main
int main() {
    float vals[16];
    float a = 2;
    float b = 2;

    for (int i = 0; i < 16; i++) {
        vals[i] = i;
    }

    for (int i = 0; i < 16; i += 4) {
        vals[i]   = vals[i]   * a + b;
	vals[i+1] = vals[i+1] * a + b;
	vals[i+2] = vals[i+2] * a + b;
	vals[i+3] = vals[i+3] * a + b;
    }

    farray_print(vals, 16);
    
    return 0;
}
