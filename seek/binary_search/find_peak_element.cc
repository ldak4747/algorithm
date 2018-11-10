#include "gtest/gtest.h"

/*
 *  题意是, 给定一个数组nums, 里边可能有1-N个peak点, 即它比左右两边都大,
 *  并且假定是, 对于数组头元素和尾元素, 可以假定头元素比左边大, 尾元素比右边大(nums[-1] == nums[nums.size()] == -∞),
 *  返回任意一个peak即可
 *
 *  首先, 本题规定了, peak点可能在任何地方出现, 而且不止一个;
 *  其次, 头元素和尾元素, 也可能是peak点;
 *  这种情况下, 如果沿用传统的二分查找思维, 当第一个mid不是peak点时, 不知道应该往左找还是往右找, 也就是说需要左右两边都试图去找才行
 *  这时就又是分治思维运用了;
 *  另外, 头尾元素也可能是peak点, 所以要考虑到边界处理
 * */
class Solution {
public:
    int findpeak (int st, int ed, const vector<int> &nums) {
        if (st > ed) {
            return -1;
        }
        int mid = (st + ed)/2;
        if (!mid) {
            return (nums[mid] > nums[mid + 1])?mid:findpeak(mid + 1, ed, nums);
        } else if (mid == nums.size() - 1) {
            return (nums[mid] > nums[mid - 1])?mid:findpeak(st, mid - 1, nums);
        } else {
            if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) {
                return mid;
            } else {
                int l = findpeak(st, mid - 1, nums);
                if (l != -1) {
                    return l;
                }
                return findpeak(mid + 1, ed, nums);
            }
        }
    }
    
    int findPeakElement(vector<int>& nums) {
        if (nums.size() == 1) {
            return 0;
        }
        return findpeak(0, nums.size() - 1, nums);
    }
};
