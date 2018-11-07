#include "gtest/gtest.h"
#include <stack>
#include <vector>

/*
 *  本题是栈的一类题的思维方式的典型体现, 类似的还有其他题. 如OJ496 next_greater_element_i、OJ503 next_greater_element_ii
 *  他们的一个共同点是: 在一个序列中, 为每个元素寻找第一个比他大/小的元素
 *  主要思想是: 如果当前元素比栈顶的大, 那么也有可能比栈顶底下的大, 这样当前元素就是这些比它小的元素的"第一个比它大的元素"
 *
 * */
class Solution {
public:
    std::vector<int> dailyTemperatures (std::vector<int>& temperatures) {
        std::vector<int> v(temperatures.size(), 0);
        std::stack<int> stk;
        for (int i = 0; i < temperatures.size(); i++) {
            while (!stk.empty() && temperatures[stk.top()] < temperatures[i]) {
                int idx = stk.top();
                stk.pop();
                v[idx] = i - idx;
            }
            stk.push(i);
        }

        return v;
    }
};
