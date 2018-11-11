#include "gtest/gtest.h"

/*
 *  和前面几道入门题是一样的
 * */
class Solution {
public:
    struct Item {
        char val;
        int freq;
        Item(char ch, int f): val(ch), freq(f) {}
        bool operator< (Item other) const {
            return freq < other.freq;
        }
    };
    
    string frequencySort(string s) {
        unordered_map<char, int> hmap;
        for (auto ch: s) {
            hmap[ch]++;
        }
        
        priority_queue<Item, vector<Item>> heap;
        for (auto it = hmap.begin(); it != hmap.end(); it++) {
            Item item(it->first, it->second);
            heap.push(item);
        }
        
        string res = "";
        while (!heap.empty()) {
            Item item = heap.top();
            heap.pop();
            for (int i = 0; i < item.freq; i++) {
                res += item.val;
            }
        }
        return res;
    }
};

int main () {
    Solution solution;
}
