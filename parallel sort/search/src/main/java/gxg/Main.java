package gxg;

public class Main {
    // 找到a中不大于b的最大数字的下标
    public int binarySearch(int[] a, int b) {
        if (a.length == 0) return -1;
        if (a.length == 1) {
            if (a[0] > b) return -1;
            else          return 0;
        }

        if (a[0] > b)            return -1;
        if (a[a.length - 1] < b) return a.length - 1;

        int low = 0;
        int high = a.length;
        while (low + 1 < high) {
            int mid = low + (high - low) / 2;
            if (a[mid] > b)      high = mid;
            else if (a[mid] < b) low = mid;
            else                 return mid;
        }
        return low;
    }

    public static void main(String[] args) {
        System.out.println(binarySearch());
    }
}
