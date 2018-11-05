#include "gtest/gtest.h"
#include <iostream>

/*
 *  考量代码能力的加强版
 * */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void Reverse (ListNode *&list) {
        if (list) {
            ListNode *head = list, *prev = nullptr;
            while (head) {
                ListNode *next = head->next;
                head->next = prev;
                prev = head;
                head = next;
            }

            list = prev;
        }
    }

    ListNode *addTwoNumbers (ListNode* l1, ListNode* l2) {
        Reverse(l1);
        Reverse(l2);

        ListNode *l3 = nullptr, *prev = nullptr;
        int add = 0;
        while (l1 && l2) {
            int sum = l1->val + l2->val + add;
            if (sum >= 10) {
                sum -= 10;
                add = 1;
            } else {
                add = 0;
            }

            if (!l3) {
                l3 = new ListNode(sum);
                prev = l3;
            } else {
                l3->next = new ListNode(sum);
                l3 = l3->next;
            }

            l1 = l1->next;
            l2 = l2->next;
        }

        while (l1) {
            int sum = l1->val + add;
            if (sum >= 10) {
                sum -= 10;
                add = 1;
            } else {
                add = 0;
            }

            l3->next = new ListNode(sum);
            l3 = l3->next;
            l1 = l1->next;
        }
        while (l2) {
            int sum = l2->val + add;
            if (sum >= 10) {
                sum -= 10;
                add = 1;
            } else {
                add = 0;
            }

            l3->next = new ListNode(sum);
            l3 = l3->next;
            l2 = l2->next;
        }

        if (add) {
            l3->next = new ListNode(1);
        }

        Reverse(prev);
        return prev;
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
    ListNode *l1 = nullptr, *l2 = nullptr, *l3 = nullptr;
    l1 = new ListNode(1);
    l1->next = new ListNode(8);
    l2 = new ListNode(0);

    Solution solution;
    l3 = solution.addTwoNumbers(l1, l2);
    solution.traverse(l3);
}

int main (int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
