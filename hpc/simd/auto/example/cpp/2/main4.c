#include <tuple>
#include <vector>
#include <iterator>

void f(std::vector<int> &a, std::vector<int> &b, std::vector<int> &c) {
    for (
        auto [aPtr, bPtr, cPtr] = std::tuple{a.begin(), b.begin(), c.begin()}; 
        aPtr != a.end() && bPtr != b.end() && cPtr != c.end(); 
        ++aPtr, ++bPtr, ++cPtr
    ) {
        *cPtr = *aPtr + *bPtr;
    }
}
