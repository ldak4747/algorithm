#include "gtest/gtest.h"

/*
 *  找出数组中出现最频繁的前K个数
 *
 *  如果已经通过前面的题熟悉了堆的运用, 那么本题迎刃而解, 设计一个最小堆, 堆按照数的出现的次数排序, 
 *  控制堆大小为K, 这样最终堆内就是出现最频繁的前K个数
 *  出现次数用hash方式统计, 整个时间复杂度不超过2趟
 * */
class Solution {
public:
    struct Item {
        int freq;
        int val;
        bool operator> (Item other) const {
            return freq > other.freq;
        }
        Item(int v, int f): val(v), freq(f) {}
    };
    
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> hmap;
        for (auto i: nums) {
            hmap[i]++;
        }
        
        priority_queue<Item, vector<Item>, greater<Item>> heap;
        for (auto it = hmap.begin(); it != hmap.end(); it++) {
            Item item(it->first, it->second);
            if (heap.size() < k) {
                heap.push(item);
            } else {
                if (item > heap.top()) {
                    heap.pop();
                    heap.push(item);
                }
            }
        }
        
        vector<int> v;
        while (!heap.empty()) {
            v.push_back(heap.top().val);
            heap.pop();
        }
        return v;
    }
};

int main () {
    Solution solution;
    return 0;
}
