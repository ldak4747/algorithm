#include "gtest/gtest.h"

/*
 *  按题型, 本题属于"非直接判断、按条件的二分查找"
 * */
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& A) {
        int st = 0, ed = A.size() - 1;
        while (st <= ed) {
            int mid = (st + ed)/2;
            
            if (A[mid] > A[mid - 1] && A[mid] > A[mid + 1]) {
                return mid;
            } else if (A[mid] > A[mid - 1] && A[mid] < A[mid + 1]) {
                st = mid + 1;
            } else {
                ed = mid - 1;
            }
        }
    }
};
