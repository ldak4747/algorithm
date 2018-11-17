#include "gtest/gtest.h"

/*
 *  给定一个升序数组, 这个数组可能(注意是可能)出现旋转, 如原先[1,2,3,4,5,6,7]可能变为[4,5,6,7,1,2,3], 求数组最小值
 *
 *  1、注意率先排除可能没有旋转的情况(即首元素最小)
 *  2、当确实旋转, 最小元素的情况分为两种, 一种是只有首元素被旋转, 这种情况下尾元素最小, 另一种情况是不止一个元素被旋转, 这种情况适用二分查找, 找到哪个元素它的左右两边都比它大
 *     lower_bound再次发挥用场, 找到第一个nums[XX] < nums[0]的地方
 * */
class Solution {
public:
    int findMin(vector<int>& nums) {
        int st = 0, ed = nums.size() - 1;

        if (nums[st] < nums[ed]) {
            return nums[st];
        }

        if (nums[ed] < nums[ed - 1]) {
            return nums[ed];
        }
        
        while (st < ed) {
            int mid = (st + ed)/2;
            if (nums[mid] < nums[mid - 1] && nums[mid] < nums[mid + 1]) {
                return nums[mid];
            } else if (nums[mid] < nums[0]) {
                ed = mid;
            } else {
                st = mid + 1;
            }
        }

        return nums[st];
    }
};
