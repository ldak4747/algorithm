#include "gtest/gtest.h"

/*
 *  本题更像是实现lower_bound了, 寻找有序数组中, 第一个不小于target的数的位置在哪
 *  注意边界处理问题: 如果target比数组里任意数都大, 那么要插入的位置是nums.size(), 另外注意数组为空情况
 * */
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        if (nums.empty()) {
            return 0;
        } else if (target > nums[nums.size() - 1]) {
            return nums.size();
        }
        
        int st = 0, ed = nums.size() - 1;
        while (st < ed) {
            int mid = (st + ed)/2;
            if (nums[mid] >= target) {
                ed = mid;
            } else {
                st = mid + 1;
            }
        }
        
        return st;
    }
};
