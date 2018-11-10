#include "gtest/gtest.h"

/*
 *  题意是, 找出数组中出现次数过半数的数(众数)
 *  本题的前提是假定在"这种情况肯定存在"
 *  在这种前提下, 有一种思维方式非常适合
 *  1、第一个数设置为假想数, 次数自然也是为1
 *  2、接下来, 如果出现的数和当前假想数一样的话, 次数加1, 如果不一样, 次数减1, 如果次数为0了, 换当前数作为假想数
 *  3、最后剩下的就是过半数的数
 * */
class Solution {
public:
    int helper_algo (const vector<int> &nums) {
        int cur, cnt = 0;
        
        for (auto i: nums) {
            if (!cnt) {
                cur = i;
                ++cnt;
            } else {
                if (cur == i) {
                    ++cnt;
                } else {
                    --cnt;
                }
            }
        }
        
        return cur;
    }
    
    int majorityElement(vector<int>& nums) {
        return helper_algo(nums);
    }
};
