#include "gtest/gtest.h"
#include <iostream>


/*
 *  注意对于偶数长度链表, 规定中点是第N/2 + 1个节点，如[1,2,3,4]的中点为3
 * */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }

        ListNode *fast = head, *slow = head;
        while (fast && fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;
        }

        return (fast->next)?slow->next:slow;
    }
}
