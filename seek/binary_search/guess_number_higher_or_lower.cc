#include <iostream>

/*
 *  稍稍注意下题意(底下也简单实现了下guess方法), 返回1是指, 猜的数猜小了
 * */
class Solution {
    int num;
    int guess (int n) {
        if (n == num) {
            return 0;
        } else if (n > num) {
            return -1;
        } else {
            return 1;
        }
    }
    
public:
    Solution(int n): num(n) {}

    int guessNumber(int n) {
        long long st = 1, ed = n;
        while (st <= ed) {
            long long mid = (st + ed)/2;
            int res = guess(mid);
            if (!res) {
                return mid;
            } else if (res == -1) {
                ed = mid - 1;
            } else {
                st = mid + 1;
            }
        }
    }
};

