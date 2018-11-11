#include <iostream>

/*
 *  本题和OJ378"kth_smallest_element_in_a_sorted_matrix", 使用完全相同的解法
 *  被注释掉的是会MLE的解法, 它和OJ378是一点区别没有了, 但是创建m*n的数组导致MLE
 *
 *  事实上没有必要真的创建数组:
 *  解题的目的, 实际是找到前K小的数据在哪里, 这样第K个自然就是这些数据的最后一个即得到结果, 
 *  那么依然使用OJ378的方法:
 *  1、对于乘法表, 首数据left是1, 尾数据right是m*n;
 *  2、算出mid = (left + right)/2, 然后模拟矩阵的每一行, 乘法表的每一行的规律是, 每一行都是以一个基数N, 依次乘以1、2、3、...、N
 *      如对于第一行, 基数N就是1, 第一行的数据就是1、2、3、4、5、...、1 * n
 *            第二行, 基数N就是2, 第二行的数据就是2、4、6、8、10、...、2 * n
 *            .....
 *            第m行, 基数N就是m, 第m行的数据就是m、2*m、3*m、4*m、5*m、...、n*m
 *
 *      而需要找到的是, 每一行中小于等于mid的个数之和, 方法是:
 *      如果mid >= 该行最大值即N*n, 那么该行小于等于mid的个数就是n;
 *      否则, 如果mid/N的结果, 就是该行小于等于mid的个数, 因为比mid大的数, mid/它 = 0
 *
 *  3、上一步则可计算出每次的mid, 取得的矩阵中小于等于mid的个数count, 针对count和所需的k的关系做lower_bound, 
 *     最终得到整个矩阵中, 前K小的part点在哪里, 这个part点就是第K小
 *
 *  细细的品味, 二分查找的运用, 实际上和分治思想(如快排)是不是本出一源呢
 * */
class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        int left = 1, right = m * n;
        
        while (left < right) {
            int mid = (left + right)/2;
            int count = 0;
            
            for (int i = 1; i <= m; i++) {
                if (mid >= i * n) {
                    count += n;
                } else {
                    count += (mid / i);
                }
            }
            
            if (count < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return left;
    }
/*
    int findKthNumber(int m, int n, int k) {
        vector<vector<int>> matrix;
        for (int i = 1; i <= m; i++) {
            vector<int> v;
            int cur = i;
            for (int j = 0; j < n; j++) {
                v.push_back(cur * (j + 1));
            }
            matrix.push_back(v);
        }
        
        int left = matrix[0][0], right = matrix[m - 1][n - 1];
        while (left < right) {
            int mid = (left + right)/2;
            int count = 0;
            for (auto &v: matrix) {
                int pos = upper_bound(v.begin(), v.end(), mid) - v.begin();
                count += pos;
            }
            
            if (count < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }
*/
};
