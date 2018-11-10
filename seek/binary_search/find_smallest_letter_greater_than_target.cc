#include "gtest/gtest.h"

/*
 *  给定一组有序可能重复字母letters和一个字母target, 找出letters中第一个比target大的字母, 如果不存在返回letters的第一个字母
 *  很明显, upper_bound, 只要当前字母mid <= target, 那么st就往后赶, 直到st == ed
 *  注意提前判断target >= letters最大字母的情况
 * */
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        if (target >= letters[letters.size() - 1]) {
            return letters[0];
        }
        
        int st = 0, ed = letters.size() - 1;
        while (st < ed) {
            int mid = (st + ed)/2;
            if (letters[mid] <= target) {
                st = mid + 1;
            } else {
                ed = mid;
            }
        }
        
        return letters[st];
    }
};
