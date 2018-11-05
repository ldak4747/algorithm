#include "gtest/gtest.h"
#include <iostream>

/*
 *  依然是考量代码能力的基础题, 更加注重细节的考虑和代码处理能力
 * */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (!head) {
            return head;
        }
        ListNode *newhead = nullptr, *prev = nullptr;

        while (head) {
            if (head->val == val) {
                ListNode *next = head->next;
                delete head;
                head = next;
            } else {
                if (!newhead) {
                    newhead = head;
                }

                if (prev) {
                    prev->next = head;
                }
                prev = head;
                head = head->next;
            }
        }
        if (prev) {
            prev->next = nullptr;
        }

        return newhead;
    }

    void traverse (ListNode *l) {
        while (l) {
            std::cout << l->val << "->";
            l = l->next;
        }
        std::cout << std::endl;
    }
};

TEST (test, test1) {
    ListNode *list = new ListNode(1);
    list->next = new ListNode(2);
    list->next->next = new ListNode(3);
    list->next->next->next = new ListNode(1);
    list->next->next->next->next = new ListNode(2);
 
    Solution solution;
    solution.traverse(list);
    list = solution.removeElements(list, 1);
    solution.traverse(list);
}

int main (int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
