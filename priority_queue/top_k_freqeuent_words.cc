#include "gtest/gtest.h"

/*
 *  和OJ347"top_k_freqeuent_elements"非常像, 题意稍有变化, 本质是一道题
 * */
class Solution {
public:
    struct Item {
        int freq;
        string val;
        bool operator> (Item other) const {
            if (freq == other.freq) {
                return val < other.val;
            }
            return freq > other.freq;
        }
        Item(string v, int f): val(v), freq(f) {}
    };
    
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> hmap;
        for (auto i: words) {
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
        
        stack<string> stk;
        vector<string> v;
        while (!heap.empty()) {
            stk.push(heap.top().val);
            heap.pop();
        }
        while (!stk.empty()) {
            v.push_back(stk.top());
            stk.pop();
        }
        return v;
    }
};
