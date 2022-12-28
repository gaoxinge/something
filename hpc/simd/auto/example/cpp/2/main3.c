#include <tuple>
#include <vector>
#include <iterator>

void f(std::vector<int> &a, std::vector<int> &b, std::vector<int> &c, int N) {
    for (
        auto [i, aPtr, bPtr, cPtr] = std::tuple{0, a.begin(), b.begin(), c.begin()}; 
        i < N;
        i++, std::advance(aPtr, 1), std::advance(bPtr, 1), std::advance(cPtr, 1)
    ) {
        *cPtr = *aPtr + *bPtr;
    }
}
