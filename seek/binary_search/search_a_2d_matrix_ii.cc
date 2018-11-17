#include "gtest/gtest.h"

/*
 *  使用和search_a_2d_matrix一模一样的方法, 就可以accept, 时间复杂度: mlogn(m和n分别是矩阵的行数和列数)
 * */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m, n;
        if (matrix.empty()) {
            return false;
        }
        
        m = matrix.size();
        if (matrix[0].empty()) {
            return false;
        }
        
        n = matrix[0].size();
        
        if (target == matrix[0][0] || target == matrix[m - 1][n - 1]) {
            return true;
        } else if (target < matrix[0][0] || target > matrix[m - 1][n - 1]) {
            return false;
        }
        
        for (auto v: matrix) {
            if (v[0] > target || v[n - 1] < target) {
                continue;
            }
            
            int st = 0, ed = n - 1;
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
