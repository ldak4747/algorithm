#include "gtest/gtest.h"

/*
 *  依然沿用和OJ378、OJ668一样的方法, 这一次, 矩阵将变成这样子:
 *  
 *  如针对数据[1,2,3,5], 除数数组为:
 *  1/2     1/3     1/5
 *  xxx     2/3     2/5
 *  xxx     xxx     3/5
 *
 *  变化:
 *  1、数组中有空位
 *  2、数字为浮点数
 *  3、升序改为降序
 *  应对:
 *  1、对于除数数组A, A[i][j] = 什么?
 *      A[i][j] =   i > j:  xxx
 *                  i <= j: nums[i]/nums[j + 1]
 *      如同OJ668一样的情况, 是否真的需要创建数组?
 *      不需要, 判断当前数是否小于等于mid即可判断是否自增count, 当前数用两层循环得到A[i][j]就知道是多少, 以及是否小于等于mid
 *      不创建数组, 无法使用lower_bound找到小于等于mid的位置, 但可以accept
 *  2、数字为浮点数, 困难在于第一次的left、right怎么取?进而的第一次的mid怎么计算?
 *      以0位第一次的left, 1为第一次的right, mid自然为0.5;
 *      还有, 如果累计次数count < K或者count > K, left不能像整型数的加1自增, 怎么办?
 *      count < K:  说明当前圈的范围不够大, 还需要进一步圈范围, 圈更大的数进来, 所以left要变大.         令left = mid, 这时不要加1了
 *      count > K:  说明当前圈的范围太大, 要缩小范围, 这时right要变小, 令right = mid
 *      count == K: 说明达到目标了, 但这时要找到当前圈的范围中最大的的数, 这需要在判断count是否自增的过程中, 如果自增就判断当前值是不是最大, 如果是则需要记录除数和被除数;
 *  3、升序改为降序, 事实上已经融汇到1和2中了, 目前的实现没有用数组, 也就没有用上二分查找的lower_bound的优势, 但可以accept
 * */
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        double left = 0, right = 1;
        
        while (left < right) {
            double mid = (left + right)/2;
            int count = 0;
            
            double max = -1;
            int res1, res2;
            for (int i = 0; i < A.size() - 1; i++) {
                int j = i + 1;
                for (; j < A.size(); j++) {
                    double cur = double(A[i])/A[j];
                    if (cur <= mid) {
                        ++count;
                        if (cur > max) {
                            max = cur;
                            res1 = A[i];
                            res2 = A[j];
                        }
                    }
                }
            }
            
            if (count == K) {
                return {res1, res2};
            } else if (count < K) {
                left = mid;
            } else {
                right = mid;
            }
        }
    }
};
