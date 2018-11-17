#include "gtest/gtest.h"

/*
 *  给定一个二维数组(可能为各种形式的空数组), 按行列均有序, 给定一个目标数target, 判断这个数在矩阵中是否存在
 *
 *  这道题远没有可能想象中的各种"矩阵二分查找"的伎俩和技巧, lc和实际问题一样, 从实际出发找到解决方案, 
 *  矩阵最小值一定是matrix[0][0]即左上, 最大值一定是matrix[m - 1][n - 1](m和n分别是矩阵的行数和列数)即右下, 
 *  如果target出现在左上或右下则直接得出结果, 如果比左上小或者比右下大, 那么必然不存在, 
 *  如果target落在左上和右下之间, 那么对矩阵每行进行二分查找即可, 这样时间复杂度最大为mlogn, 如果target比当前行的首元素还小则无需查找, 进一步减少无谓查找
 * */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) {
            return false;
        }
        
        int m = matrix.size(), n = matrix[0].size();
        
        if (matrix[0][0] == target || matrix[m - 1][n - 1] == target) {
            return true;
        } else if (matrix[0][0] > target || matrix[m - 1][n - 1] < target) {
            return false;
        }
        
        for (auto v: matrix) {
            if (v[0] > target) {
                continue;
            }
            
            int st = 0, ed = v.size() - 1;
            while (st <= ed) {
                int mid = (st + ed)/2;
                if (v[mid] == target) {
                    return true;
                } else if (v[mid] > target) {
                    ed = mid - 1;
                } else {
                    st = mid + 1;
                }
            }
        }
        
        return false;
    }
};
