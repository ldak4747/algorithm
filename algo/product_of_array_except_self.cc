#include "gtest/gtest.h"
#include <vector>


class Solution {
public；
    std::vector<int> productExceptSelf (std::vector<int>& nums) {
        int product = 1;
        std::vector<int> zeroidxs;

        for (int i = 0; i < nums.size(); i++) {
            if (!nums[i]) {
                zeroidxs.push_back(i);
            }

            product *= nums[i];
        }

        std::vector<int> v(nums.size(), 0);
        if (!product) {
            if (zeroidxs.size() > 1) {
                return v;
            } else {
                v[zeroidxs[0]] = 1;
                for (int i = 0; i < nums.size(); i++) {
                    if (nums[i]) {
                        v[zeroidxs[0]] *= nums[i];
                    }
                }
            }
        } else {
            for (int i = 0; i < nums.size(); i++) {
                v[i] = product/nums[i];
            }
        }

        return v;
    }
};
