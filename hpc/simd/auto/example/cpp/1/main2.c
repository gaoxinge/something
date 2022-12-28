#include <vector>
#include <iterator>

void f(int *a, int *b, int *c, int N) {
    for (int i = 0; i < N; i++, ++c, ++b, ++a) {
        *c = *a + *b;
    }
}
