#include "gtest/gtest.h"
#include <iostream>


/*
 *  基础题
 * */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void deleteNode(ListNode* node) {
        if (node) {
            ListNode *next = node->next;
            if (next) {
                node->val = next->val;
                node->next = next->next;
                delete next;
            } else {
                delete node;
                node = nullptr;
            }
        }
    }
}
