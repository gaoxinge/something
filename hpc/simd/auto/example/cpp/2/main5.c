#include <tuple>
#include <vector>
#include <iterator>

void f(std::vector<int> &a, std::vector<int> &b, std::vector<int> &c) {
    for (
        auto [aPtr, bPtr, cPtr] = std::make_tuple(a.begin(), b.begin(), c.begin()); 
        aPtr != a.end() && bPtr != b.end() && cPtr != c.end();
        std::advance(aPtr, 1), std::advance(bPtr, 1), std::advance(cPtr, 1)
    ) {
        *cPtr = *aPtr + *bPtr;
    }
}
