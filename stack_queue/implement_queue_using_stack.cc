#include "gtest/gtest.h"
#include <stack>


/*
 *  相对于用队列实现栈、最小栈, 本题相对好想一些, 栈和队列一定勤练
 * */
class MyQueue {
    std::stack<int> stk1, stk2;

    void push (int v) {
        stk1,push(v);
    }

    int pop () {
        if (!stk1.empty()) {
            while (!stk1.empty()) {
                stk2.push(stk1.top());
                stk1.pop();
            }

            int peekval = stk2.top();
            stk2.pop();
            while (!stk2.empty()) {
                stk1.push(stk2.top());
                stk2.pop();
            }

            return peekval;
        }
    }

    int peek () {
        if (!stk1.empty()) {
            while (!stk1.empty()) {
                stk2.push(stk1.top());
                stk1.pop();
            }

            int peekval = stk2.top();
            while (!stk2.empty()) {
                stk1.push(stk2.top());
                stk2.pop();
            }

            return peekval;
        }
    }

    bool empty () const {
        return stk1.empty();
    }
};
