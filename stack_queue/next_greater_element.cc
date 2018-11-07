#include "gtest/gtest.h"
#include <vector>
#include <stack>

class Solution {
public:
    std::vector<int> nextGreaterElement (std::vector<int>& findNums, std::vector<int>& nums) {
        std::map<int, int> map;
        std::stack<int> stk;
        for (int i = 0; i < nums.size(); i++) {
            int curval = nums[i];
            while (!stk.empty() && stk.top() < curval) {
                int preval = stk.top();
                stk.pop();
                map[preval] = curval;
            }
            stk.push(curval);
        }

        std::vector<int> v(findNums.size(), -1);
        for (int i = 0; i < findNums.size(); i++) {
            if (map.find(findNums[i]) != map.end()) {
                v[i] = map[findNums[i]];
            }
        }

        return v;
    }
};
