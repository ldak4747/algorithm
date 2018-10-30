#include "skiplist.h"
#include <iostream>
#include <set>
#include <chrono>

int main () {
    SkipList<int, int> skp;

    std::random_device rd;
    std::set<int> s1, s2;
    while (s1.size() != 10000) {
        int res = rd() % 100000;
        s1.insert(res);
    }
    for (auto i: s1) {
        if (i % 2) {
            s2.insert(i);
        }
        skp.Insert(i, 0);
    }

    for (auto i: s2) {
        skp.Remove(i);
        //skp.Debug();
    }

    std::vector<std::pair<int, int>> res = skp.RangeGet(0, 50000);
    std::cout << res.size() << "," << skp.GetLevel() << std::endl;
    skp.Debug();


    std::chrono::steady_clock::time_point st = std::chrono::steady_clock::now();
    int v;
    skp.Search(50000, v);
    std::chrono::steady_clock::time_point ed = std::chrono::steady_clock::now();
    std::cout << "search cost " << std::chrono::duration_cast<std::chrono::microseconds>(ed - st).count() << std::endl;
    return 0;
}
