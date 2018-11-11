#include "gtest/gtest.h"

/*
 *  设计一个类, 先用一个数组初始化, 然后可以加入新的数, 加入时要获取到第K大的数
 *
 *  最原生的堆运用, 既然是要找第K大的数, 那么创建一个最小堆, 即堆顶最小, 堆元素最多K个, 
 *  达到K个时, 除非更大的值可以插入, 这样保证每次插入后, size为K的堆的堆顶元素就是当前第K大的元素
 *
 *  相当于本题的姊妹题OJ215"kth_largest_element_in_an_array", 也可以用堆处理, 不过那道题用基于分治思维的快速排序方式求解更为"精妙"
 * */
class KthLargest {
public:
    priority_queue<int, vector<int>, greater<int>> heap;
    int K;
    KthLargest(int k, vector<int> nums): K(k) {
        for (auto i: nums) {
            if (heap.size() < k) {
                heap.push(i);
            } else {
                if (i > heap.top()) {
                    heap.pop();
                    heap.push(i);
                }
            }
        }
    }
    
    int add(int val) {
        if (heap.size() < K) {
            heap.push(val);
        } else {
            if (val > heap.top()) {
                heap.pop();
                heap.push(val);
            }
        }
        
        if (heap.size() == K) {
            return heap.top();
        }
    }
};
