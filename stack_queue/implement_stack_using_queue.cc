#include "gtest/gtest.h"
#include <queue>
#include <algorithm>


/*
 *  本题注意pop方法也需要返回top()
 *  依然是栈和队列的逻辑思维、运用能力的考量, 这种题个人感觉是:
 *  1、考的可能大
 *  2、代码量不大, 但考量效果好
 *  3、确实很考验逻辑思维能力, 多做这类题, 虽然可能痛苦, 但是确实提升逻辑思维能力, 还是要多做
 * */
class MyStack {
public:
    std::queue<int> q1, q2;

    void push (int v) {
        q1.push(v);
    }
    
    int pop () {
        if (!q1.empty()) {
            int size = q1.size();
            for (int i = 0; i < size - 1; i++) {
                q2.push(q1.front());
                q1.pop();
            }
            
            int topval = q1.front();
            q1.pop();
            std::swap(q1, q2);
            return topval;
        }
    }

    int top () {
        if (!q1.empty()) {
            int size = q1.size();
            for (int i = 0; i < size - 1; i++) {
                q2.push(q1.front());
                q1.pop();
            }

            int topval = q1.front();
            q2.push(topval);
            q1.pop();
            std::swap(q1, q2);
            return topval;
        }
    }

    bool empty () const {
        return q1.empty();
    }
};

TEST (test, test1) {
}

int main (int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
