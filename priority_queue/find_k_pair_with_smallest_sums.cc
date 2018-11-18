#include "gtest/gtest.h"

/*
 *  本题看起来, 和二分查找有些关系, 但其实不然, 因为所需的结果是由两个数组各出一个数, 而每个数组的有序性, 并不难保证加和的有序性, 如[1,3]和[2,5], 并不能保证1 + 5 > 3 + 2
 *  所以O(N^2)的遍历入堆, 是比较直观的选择
 * */
class Solution {
public:
    struct Pair {
        int a;
        int b;
        Pair(int _a, int _b): a(_a), b(_b) {}
        bool operator> (Pair other) const {
            return (a + b) > (other.a + other.b);
        }
        bool operator< (Pair other) const {
            return (a + b) < (other.a + other.b);
        }
    };
    
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        priority_queue<Pair, vector<Pair>> heap;
        for (auto i: nums1) {
            for (auto j: nums2) {
                Pair p(i, j);
                if (heap.size() < k) {
                    heap.push(p);
                } else {
                    if (p < heap.top()) {
                        heap.pop();
                        heap.push(p);
                    }
                }
            }
        }
        
        vector<pair<int, int>> v;
        while (!heap.empty()) {
            Pair p = heap.top();
            heap.pop();
            v.emplace_back(p.a, p.b);
        }
        return v;
    }
};
