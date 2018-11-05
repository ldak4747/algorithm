#include "gtest/gtest.h"
#include <iostream>


/*
 *  看起来不难, 但准确的实现也不是很容易, 本质上依然考量代码实现能力
 * */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }

        ListNode *prev = nullptr, *newhead = head;
        while (head) {
            if (!prev) {
                prev = head;
                head = head->next;
            } else {
                ListNode *next = head->next;
                if (prev->val == head->val) {
                    delete head;
                    head = next;
                } else {
                    prev->next = head;
                    prev = head;
                    head = next;
                }
            }
        }

        prev->next = nullptr;
        return newhead;
    }
}
