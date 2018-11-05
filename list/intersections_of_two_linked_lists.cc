#include "gtest/gtest.h"
#include <iostream>

/*
 *  只要有一个链表为空, 注定没有交点, 这部分提前排除掉, 大大简化考虑的条件的复杂度, 
 *  接下来, 分别计算两个链表的长度M和N, 然后将长度更长的一方如M > N, 则前移长度为M的链表(M - N)个节点, 
 *  保证两个链表齐头并进时, 同时走到结尾, 过程中发现两链表节点相同则可以返回;
 *
 *  这是相当于时间复杂度O(M + N)的做法, 确切说是最大时间复杂度O((M + N) * 2)
 *  相比之下比较糟糕的解法是, 循环比较某链表的每个节点, 是否在另一个链表里出现过, 时间复杂度O(M * N)
 * */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) {
            return nullptr;
        }

        int l1 = 0, l2 = 0;
        ListNode *A = headA, *B = headB;
        while (A) {
            ++l1;
            A = A->next;
        }
        while (B) {
            ++l2;
            B = B->next;
        }

        int dist;
        if (l1 > l2) {
            dist = l1 - l2;
            while (dist--) {
                headA = headA->next;
            }
        } else if (l1 < l2) {
            dist = l2 - l1;
            while (dist--) {
                headB = headB->next;
            }
        }

        while (headA && headB) {
            if (headA == headB) {
                return headA;
            } else {
                headA = headA->next;
                headB = headB->next;
            }
        }

        return nullptr;
    }
};
