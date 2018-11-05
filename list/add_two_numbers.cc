#include "gtest/gtest.h"

/*
 *  很基础的题，代码量比较大，考量的是基础代码能力
 * */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *l3 = nullptr, *prev = nullptr;
        int add = 0;
        
        while (l1 && l2) {
            int sum = l1->val + l2->val + add;
            if (sum >= 10) {
                add = 1;
                sum -= 10;
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
                add = 1;
                sum -= 10;
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
                add = 1;
                sum -= 10;
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
    l1 = new ListNode(2);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(3);
    l2 = new ListNode(5);
    l2->next = new ListNode(6);
    l2->next->next = new ListNode(4);

    Solution solution;
    l3 = solution.addTwoNumbers(l1, l2);
    solution.traverse(l3);
}

int main (int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
