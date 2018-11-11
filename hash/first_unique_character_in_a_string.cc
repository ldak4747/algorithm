#include "gtest/gtest.h"

/*
 *  最简单的hash运用
 * */
class Solution {
public:
    int firstUniqChar(string s) {
        map<char, int> map;
        for (int i = s.length() - 1; i >= 0; i--) {
            map[s[i]]++;
        }
        for (int i = 0; i < s.length(); i++) {
            if (1 == map[s[i]]) {
                return i;
            }
        }
        
        return -1;
    }
};
