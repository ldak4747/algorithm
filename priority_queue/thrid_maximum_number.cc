#include "gtest/gtest.h"

/*
 *  题意是, 给定一个数组, 找到数组中第3大元素, 注意:
 *  1、数组中可能有重复元素, 如[2,2,1,3], 应该返回第三大元素是1
 *  2、如果数组按大小排序的元素数不足3, 如[1,1,1,1,1,2], 第三大元素不存在, 则返回最大元素
 *
 *  本题看起来很简单, 不过良好处理起来也需要一些手筋, 首先用set排除掉重复元素, 途中记录最大值, 然后针对个数不足3个的直接返回最大值,
 *  个数不小于3个时, 用3大小的最小堆实现找到第3大元素, 整个处理的时间复杂度是两趟
 * */
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        int max = INT_MIN;
        set<int> s;
        for (auto i: nums) {
            s.insert(i);
            if (i > max) {
                max = i;
            }
        }
        
        if (s.size() < 3) {
            return max;
        }
        
        priority_queue<int, vector<int>, greater<int>> heap;
        for (auto it = s.begin(); it != s.end(); it++) {
            if (heap.size() < 3) {
                heap.push(*it);
            } else {
                if (*it > heap.top()) {
                    heap.pop();
                    heap.push(*it);
                }
            }
        }
        
        return heap.top();
    }
};
