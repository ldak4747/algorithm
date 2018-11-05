#include "gtest/gtest.h"
#include <iostream>
#include <stack>

/*
 *  这里介绍的是一个用栈的方法, 相比"直接法", 用栈的方法逻辑上更清晰:
 *  1.  如果栈为空, 当前元素进栈;
 *  2.  如果不为空, 栈顶元素和当前元素值相等, 则将当前元素及其后续元素中值和栈顶元素相等的都删除; 最后也删除栈顶元素;
 *  3.  如果不为空, 栈顶元素和当前元素不相等, 则当前元素继续进栈;
 *  4.  最终栈内元素则是需要保留的元素, 注意此时它们是逆序的, 用另一个栈将元素重新进栈, 实现元素反序
 *  5.  然后元素依次出栈, 更新每个元素的next指向, 注意边界处理细节: 最后一个元素需要指向nullptr, 但要注意本身栈就为空的情况
 *
 *  时间复杂度: 最大是链表长度2倍, 相当于O(N)
 *  空间复杂度: 最大是链表长度2倍, 相当于O(N)
 *
 *  另: 所谓"直接法", 就是遍历元素时, 判断它后边是否存在和它相等元素, 根据是否存在的情况, 修改链表头节点、上一次的接头节点
 *  这种方法时间复杂度O(N), 不使用额外空间, 但是容易写错
 * */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *deleteDuplicates (ListNode *head) {
        if (!head || !head->next) {
            return head;
        }

        std::stack<ListNode *> stk;
        while (head) {
            if (stk.empty()) {
                stk.push(head);
            } else {
                if (stk.top()->val == head->val) {
                    while (head && head->val == stk.top()->val) {
                        ListNode *next = head->next;
                        delete head;
                        head = next;
                    }

                    ListNode *delnode = stk.top();
                    stk.pop();
                    delete delnode;
                    if (head) {
                        stk.push(head);
                    }
                } else {
                    stk.push(head);
                }
            }
            if (head) {
                head = head->next;
            }
        }

        std::stack<ListNode *> stk2;
        while (!stk.empty()) {
            stk2.push(stk.top());
            stk.pop();
        }

        ListNode *newhead = nullptr, *prev = nullptr;
        while (!stk2.empty()) {
            if (!newhead) {
                newhead = prev = stk2.top();
                stk2.pop();
                prev->next = nullptr;
            } else {
                prev->next = stk2.top();
                stk2.pop();
                prev = prev->next;
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
    list->next = new ListNode(1);

    Solution solution;
    list = solution.deleteDuplicates(list);
    solution.traverse(list);
}

int main (int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
