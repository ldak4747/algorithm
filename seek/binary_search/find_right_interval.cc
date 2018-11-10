#include "gtest/gtest.h"

/*
 *  本题依然是lower_bound/upper_bound的运用
 *  给定一些区间, 找出对于每个区间, 如果存在其他区间的左值, 都大于等于它的右值, 那么找到这些区间中, 左值最小的一个的位置, 如果不存在返回-1
 *
 *  首先把每个区间的左值和该区间的位置保存起来, 方式是用一个std::map, 
 *  然后, 依次找每个区间的右值, 在这个map中的lower_bound, 即第一个不小于(大于等于)它的右值的区间
 * */
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};
class Solution {
public:
    vector<int> findRightInterval(vector<Interval>& intervals) {
        map<int, int> map;
        for (int i = 0; i < intervals.size(); i++) {
            Interval cur = intervals[i];
            map[cur.start] = i;
        }
        
        vector<int> v(intervals.size(), -1);
        for (int i = 0; i < intervals.size(); i++) {
            Interval cur = intervals[i];
            int curend = cur.end;
            
            std::map<int, int>::iterator iter = map.lower_bound(curend);
            if (iter != map.end()) {
                v[i] = iter->second;
            }
        }
        
        return v;
    }
};
