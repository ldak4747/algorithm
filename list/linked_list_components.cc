#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <set>

/*
 *  本质上, 依然是代码能力的考量, 边界细节的考虑和处理
 * */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    int numComponents(ListNode* head, vector<int>& G) {
        std::set<int> set;
        for (auto i: G) {
            set.insert(i);
        }

        int part = 0;
        bool prev = false;
        while (head) {
            if (set.find(head->val) != set.end()) {
                if (!prev) {
                    prev = true;
                }
            } else {
                if (prev) {
                    ++part;
                    prev = false;
                }
            }
            head = head->next;
        }

        if (prev) {
            ++part;
        }
        return part;
    }
}
