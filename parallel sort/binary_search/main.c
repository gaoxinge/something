#include <stdio.h>

// 数组a中不大于b的最大数字的下标
int binary_search1(int *a, int n, int b) {
    int low = -1;
    int high = n;
    while (low + 1 != high) {
        int mid = low + (high - low) / 2;
        if (a[mid] < b)      low = mid;
        else if (a[mid] > b) high = mid;
        else                 return mid;
    }
    return low;
}

// 数组a中不大于b的最大数字的最小下标
int binary_search2(int *a, int n, int b) {
    int low = -1;
    int high = n;
    while (low + 1 != high) {
        int mid = low + (high - low) / 2;
        if (a[mid] < b) low = mid;
        else            high = mid;
    }
    if (high < n && a[high] == b) return high;
    return low;
}

// 数组a中不大于b的最大数字的最大下标
int binary_search3(int *a, int n, int b) {
    int low = -1;
    int high = n;
    while (low + 1 != high) {
        int mid = low + (high - low) / 2;
        if (a[mid] <= b) low = mid;
        else             high = mid;
    }
    return low;
}

// 数组a中不小于b的最小数字的下标
int binary_search4(int *a, int n, int b) {
    int low = -1;
    int high = n;
    while (low + 1 != high) {
        int mid = low + (high - low) / 2;
        if (a[mid] < b)      low = mid;
        else if (a[mid] > b) high = mid;
        else                 return mid;
    }
    if (high == n) return -1;
    return high;
}

// 数组a中不小于b的最小数字的最小下标
int binary_search5(int *a, int n, int b) {
    int low = -1;
    int high = n;
    while (low + 1 != high) {
        int mid = low + (high - low) / 2;
        if (a[mid] < b) low = mid;
        else            high = mid;
    }
    if (high == n) return -1;
    return high;
}

// 数组a中不小于b的最小数字的最大下标
int binary_search6(int *a, int n, int b) {
    int low = -1;
    int high = n;
    while (low + 1 != high) {
        int mid = low + (high - low) / 2;
        if (a[mid] <= b) low = mid;
        else             high = mid;
    }
    if (low > -1 && a[low] == b) return low;
    if (high == n) return -1;
    return high;
}

int main() {
    int a1[] = {};
    int b1 = 0;
    printf("%d ", binary_search1(a1, 0, b1));
    printf("%d ", binary_search2(a1, 0, b1));
    printf("%d ", binary_search3(a1, 0, b1));
    printf("%d ", binary_search4(a1, 0, b1));
    printf("%d ", binary_search5(a1, 0, b1));
    printf("%d ", binary_search6(a1, 0, b1));
    printf("\n");
    
    int a2[] = {1, 2, 3};
    int b2 = 1;
    printf("%d ", binary_search1(a2, 3, b2));
    printf("%d ", binary_search2(a2, 3, b2));
    printf("%d ", binary_search3(a2, 3, b2));
    printf("%d ", binary_search4(a2, 3, b2));
    printf("%d ", binary_search5(a2, 3, b2));
    printf("%d ", binary_search6(a2, 3, b2));
    printf("\n");

    int a3[] = {1, 2, 3};
    int b3 = 2;
    printf("%d ", binary_search1(a3, 3, b3));
    printf("%d ", binary_search2(a3, 3, b3));
    printf("%d ", binary_search3(a3, 3, b3));
    printf("%d ", binary_search4(a3, 3, b3));
    printf("%d ", binary_search5(a3, 3, b3));
    printf("%d ", binary_search6(a3, 3, b3));
    printf("\n");
    
    int a4[] = {1, 2, 3};
    int b4 = 3;
    printf("%d ", binary_search1(a4, 3, b4));
    printf("%d ", binary_search2(a4, 3, b4));
    printf("%d ", binary_search3(a4, 3, b4));
    printf("%d ", binary_search4(a4, 3, b4));
    printf("%d ", binary_search5(a4, 3, b4));
    printf("%d ", binary_search6(a4, 3, b4));
    printf("\n");
    
    int a5[] = {1, 1, 1, 2, 3};
    int b5 = 1;
    printf("%d ", binary_search1(a5, 5, b5));
    printf("%d ", binary_search2(a5, 5, b5));
    printf("%d ", binary_search3(a5, 5, b5));
    printf("%d ", binary_search4(a5, 5, b5));
    printf("%d ", binary_search5(a5, 5, b5));
    printf("%d ", binary_search6(a5, 5, b5));
    printf("\n");
    
    int a6[] = {1, 2, 2, 2, 3};
    int b6 = 2;
    printf("%d ", binary_search1(a6, 5, b6));
    printf("%d ", binary_search2(a6, 5, b6));
    printf("%d ", binary_search3(a6, 5, b6));
    printf("%d ", binary_search4(a6, 5, b6));
    printf("%d ", binary_search5(a6, 5, b6));
    printf("%d ", binary_search6(a6, 5, b6));
    printf("\n");
    
    int a7[] = {1, 2, 3, 3, 3};
    int b7 = 3;
    printf("%d ", binary_search1(a7, 5, b7));
    printf("%d ", binary_search2(a7, 5, b7));
    printf("%d ", binary_search3(a7, 5, b7));
    printf("%d ", binary_search4(a7, 5, b7));
    printf("%d ", binary_search5(a7, 5, b7));
    printf("%d ", binary_search6(a7, 5, b7));
    printf("\n");
    
    return 0;
}