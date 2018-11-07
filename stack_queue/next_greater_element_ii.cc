#include "gtest/gtest.h"
#include <stack>
#include <vector>

/*
 *  本质上和OJ496 next_greater_element_i是一样的, 额外需要做的是, 未找到下一个比它大的元素时, 循环找, 即从数组头再找一遍;
 *  那就再找一遍呀!
 * */
class Solution {
public:
    std::vector<int> nextGreaterElements (std::vector<int>& nums) {
        std::stack<int> stk;
        std::vector<int> v(nums.size(), -1);
        for (int i = 0; i < nums.size(); i++) {
            int curval = nums[i];
            while (!stk.empty() && nums[stk.top()] < curval) {
                int prevalidx = stk.top();
                stk.pop();
                v[prevalidx] = curval;
            }
            stk.push(i);
        }

        //再找一遍呀
        //不要关注什么"v[i]当前是不是-1呀的情况", 而是换个思路, 对栈里还存在着的元素下手, 它们都是v[i]=-1的元素
        for (int i = 0; i < nums.size(); i++) {
            while (!stk.empty() && nums[stk.top()] < nums[i]) {
                int idx = stk.top();
                stk.pop();
                v[idx] = nums[i];
            }
        }
        return v;
        
    }
};
