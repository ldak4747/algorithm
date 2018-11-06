#include "gtest/gtest.h"
#include <stack>


/*
 *  栈和队列是非常容易出现的题, 因为代码量不大适合面试场合, 但对逻辑思维的考量不亚于任何一个算法类目
 *  本题的思路是: 用一个栈做正常出入功能, 而另一个栈维护一个最小值的顺序序列
 * */
class MinStack {
    std::stack<int> stk1, stk2;

    int getMin () {
        if (!stk2.empty()) {
            return stk2.top();
        }
    }

    int top () {
        if (!stk1.empty()) {
            return stk1.top();
        }
    }

    void push (int v) {
        stk1.push(v);
        if (stk2.empty()) {
            stk2.push(v);
        } else {
            if (stk2.top() >= v) {
                stk2.push(v);
            }
        }
    }

    void pop () {
        if (!stk1.empty()) {
            if (stk2.top() < stk1.top()) {
                stk1.pop();
            } else {
                stk1.pop();
                stk2.pop();
            }
        }
    }
};
