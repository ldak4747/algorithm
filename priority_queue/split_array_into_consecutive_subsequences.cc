#include "gtest/gtest.h"

/*
 *  题意是, 给定一个数组, 里边会有重复的元素, 试图保证把这个数组切分成若干个子数组, 保证:
 *  1、每个数组都升序且连续的, 如1、2、3, 不可以是1、2、4这样
 *  2、每个数组至少长度为3
 *
 *  本题greedy是最优解, 但这里给出一个会TLE的"dfs+priority_queue"解法, 既是堆的运用, 还是dfs的运用
 *  思路是, 设法若干个最大堆承载全部的数据, 并且在插入时, 判断是否比堆顶只大1,, 确保每个堆的数都升序且连续的, 当全部数据加载如堆后, 判断是否存在长度不足3的堆;
 *  如果返回false, 则试图把当前数加在另外可以push的堆中;
 *  如果统统返回false, 再尝试扩建一个堆并push这个数
 *
 *  by the way, 个人感觉对于数据结构算法练习者, gready不是一个特别好的东西, 因为gready的思路在临场时不那么容易想的到, 或者简单说, 如我等智商不足的, 还是需要建立扎实的概念和方法论去临场解题, 建议能dfs的不要gready, dfs效率低的学会用dp
 * */
class Solution {
public:
    bool helper (int st, const vector<int>& nums, vector<priority_queue<int, vector<int>>> v) {
        if (st == nums.size()) {
            for (auto &heap: v) {
                if (heap.size() < 3) {
                    return false;
                }
            }
            
            return true;
        }
        
        for (int i = st; i < nums.size(); i++) {
            if (v.empty()) {
                priority_queue<int, vector<int>> heap;
                heap.push(nums[i]);
                v.push_back(heap);
                return helper(st + 1, nums, v);
            } else {
                for (auto &heap: v) {
                    if (heap.top() != nums[i] && nums[i] - heap.top() == 1) {
                        heap.push(nums[i]);
                        if (helper(st + 1, nums, v)) {
                            return true;
                        }
                        heap.pop();
                    }
                }
                
                priority_queue<int, vector<int>> heap;
                heap.push(nums[i]);
                v.push_back(heap);
                return helper(st + 1, nums, v);
            }
        }
    }
    
    bool isPossible(vector<int>& nums) {
        vector<priority_queue<int, vector<int>>> v;
        return helper(0, nums, v);
    }
};
