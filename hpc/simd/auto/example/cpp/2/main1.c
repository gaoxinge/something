#include <vector>
#include <iterator>

void f(std::vector<int> &a, std::vector<int> &b, std::vector<int> &c, int N) {
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }
}
