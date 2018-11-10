#include "gtest/gtest.h"

/*
 *  本题需要找出1-2个众数, 为什么可能是2个?
 *  假设前提是, 超过1/3, 那么最多可能有几个这样的数? 答案是2个, 不可能是3个, 但存在可能是2个
 *  
 *  本题更加重要的是考查, 这个问题如何代码实现, moore vote的关键思想是:
 *  当前数与某个假想数不同时, 先去观察是否与另一个假想数相等, 
 *  不等时, 也不要急于立即给另一个假想数减计数, 而是如果第一个假想数的计数已经为0, 则把当前数先赋值给第一个假想数,
 *  两个假想数都存在, 才双双减计数
 * */
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int m1 = INT_MIN, m2 = INT_MAX, c1 = 0, c2 = 0;
        for (auto i: nums) {
            if (m1 == i) {
                ++c1;
            } else if (m2 == i) {
                ++c2;
            } else if (!c1) {
                m1 = i;
                ++c1;
            } else if (!c2) {
                m2 = i;
                ++c2;
            } else {
                --c1;
                --c2;
            }
        }
        
        vector<int> v;
        c1 = 0;
        c2 = 0;
        for (auto i: nums) {
            if (i == m1) {
                ++c1;
            }
            if (i == m2) {
                ++c2;
            }
        }
        
        if (c1 > nums.size()/3) {
            v.push_back(m1);
        }
        if (c2 > nums.size()/3) {
            v.push_back(m2);
        }
        return v;
    }
};
