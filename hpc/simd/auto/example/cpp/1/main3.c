#include <vector>
#include <iterator>

void f(int *a, int *b, int *c, int N) {
    for (int i = 0; i < N; i++, std::advance(a, 1), std::advance(b, 1), std::advance(c, 1)) {
        *c = *a + *b;
    }
}
