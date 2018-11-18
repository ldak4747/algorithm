#include "gtest/gtest.h"

/*
 *  本题是OJ153"find_minimum_in_rotated_sorted_array"的延伸, OJ153是通过lower_bound寻找可能旋转数组的最小值
 *  本题是在找到最小值后, 根据target所处是旋转的部分还是未旋转的部分, 再进行二分查找
 *
 *  注意, 如果只有一个元素被旋转, 和多个元素被旋转, 不同的界定左右区间的方式
 * */
class Solution {
public:
    int bs (const vector<int> &nums, int st, int ed, const int &target) {
        while (st <= ed) {
            int mid = (st + ed)/2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > target) {
                ed = mid - 1;
            } else {
                st = mid + 1;
            }
        }
        
        return -1;
    }
    
    int search(vector<int>& nums, int target) {
        if (nums.empty()) {
            return -1;
        }
        if (target == nums[0]) {
            return 0;
        } else if (target == nums[nums.size() - 1]) {
            return nums.size() - 1;
        }
        if (nums[0] < nums[nums.size() - 1]) {
            return bs(nums, 0, nums.size() - 1, target);
        }
        
        int st = 0, ed = nums.size() - 1, mid;
        while (st < ed) {
            mid = (st + ed)/2;
            if (nums[mid] < nums[mid - 1] && nums[mid] < nums[mid + 1]) {
                break;
            } else if (nums[mid] < nums[0]) {
                ed = mid;
            } else {
                st = mid + 1;
            }
        }

        if (nums[mid] > nums[mid + 1]) {
            mid = mid + 1;
        }

        if (target < nums[0]) {
            st = mid;
            ed = nums.size() - 1;
            return bs(nums, st, ed, target);
        } else {
            st = 0;
            ed = mid - 1;
            return bs(nums, st, ed, target);
        }
    }
};
