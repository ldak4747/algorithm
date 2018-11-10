#include "gtest/gtest.h"

/*
 *  本题应该是最直接最典型的lower_bound和upper_bound的运用了, 
 *  给定一个有序且元素可能重复的数组nums, 给定一个数target, 找到这个target如果出现的话, 第一次和最后一次出现的位置
 *
 *  我的解法比较"朴实, 可能看起来不是那么聪明, 旨在为了切实理解lower_bound和upper_bound:
 *  1、首先二分查找判断, 这个target是否在nums真正存在, 如果不存在, 直接返回两个-1
 *  2、如存在, 首先查找第一次出现的位置:
 *  2.1、只要当前数mid小于target, st往后赶, 设置st = mid + 1, 直到st == ed, 因为ed都是保证nums[ed] == target的, 所以最终st==ed时, nums[st] == target, 所以此时st就是第一次出现的位置
 *  2.2、只要当前数小于等于target, st往后赶, 设置st = mid + 1, 直到st == ed, 注意, 当st==ed时, 看起来st是第一个大于target的数的位置, 但事实上如果数组的末元素也等于target, 也就是说nums[ed] == target, 这时st就是最后一个出现的位置, 这里需要判断
 *
 *  lower_bound和upper_bound的精妙之处就在于, 同样的代码, 一个是'<', 一个是'<=', 前者能找到的是第一次出现的位置, 而后者则是最后一次出现位置
 * */
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> v({-1, -1});
        if (nums.empty()) {
            return v;
        } else if (nums.size() == 1 && nums[0] == target) {
            v[0] = v[1] = 0;
            return v;
        }
  
        int st = 0, ed = nums.size() - 1;
        while (st < ed) {
            int mid = (st + ed)/2;
            if (nums[mid] == target) {
                break;
            } else if (nums[mid] > target) {
                ed = mid - 1;
            } else {
                st = mid + 1;
            }
        }
        
        if (nums[(st + ed)/2] != target) {
            return v;
        }
        
        //lower_bound
        st = 0;
        ed = nums.size() - 1;
        while (st < ed) {
            int mid = (st + ed)/2;
            if (nums[mid] < target) {
                st = mid + 1;
            } else {
                ed = mid;
            }
        }
        v[0] = st;
        
        //upper_bound      
        st = 0;
        ed = nums.size() - 1;
        while (st < ed) {
            int mid = (st + ed)/2;
            if (nums[mid] <= target) {
                st = mid + 1;
            } else {
                ed = mid;
            }
        }
        if (nums[st] == target) {
            v[1] = st;
        } else {
            v[1] = st - 1;
        }
        
        return v;
    }
};
