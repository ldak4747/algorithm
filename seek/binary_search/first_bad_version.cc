#include "gtest/gtest.h"

/*
 *  这道题开启了二分查找系列的一个重要分支领域: lower_bound/upper_bound
 *  lower_bound和upper_bound也都是STL标准库算法, 
 *  lower_bound: 在一个有序但元素可能重复的容器中, 第一个不小于X的的元素的位置
 *  upper_bound: 在一个有序但元素可能重复的容器中, 第一个大于X的元素的位置
 *
 *  它们很重要, LC也有很多相关题目, 本题就是典型运用, 它的核心思想是:
 *  1、如果符合条件(如本题的isBadVersion() == true), 当前位置作为end;
 *  2、否则, st位置前移;
 *  3、当st == ed时, st就是第一个符合条件的位置, lower_bound
 *
 *  这个思想可以找到如: 最后一个不符合条件的、第一个符合条件的
 *  反过来, 第一个符合条件的, 最后一个不符合条件的
 * */
class Solution {
public:
    int firstBadVersion(int n) {
        long long st = 1, ed = n;
        while (st < ed) {
            long long mid = (st + ed)/2;
            if (isBadVersion(mid)) {
                ed = mid;
            } else {
                st = mid + 1;
            }
        }
        
        return st;
    }
};
