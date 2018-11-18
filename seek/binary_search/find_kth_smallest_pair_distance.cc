#include "gtest/gtest.h"

/*
 *  本题是lower_bound的高级运用, 结合滑动数组, 是OJ378、OJ668的进阶版, 
 *  滑动数组有专门的专题.
 *  被注释的部分是NlogN排序后, 再O(N^2)的入最大堆取第K小的方法, 会TLE
 *  
 *  基于滑动数组的思想是: 求distance不大于X的Y个, 通过Y和K的对比关系, 使用lower_bound思想, 
 *  当Y >= K时, 说明当前的X设置过大, 应降低X, 否则应该放大X
 *  降低X和放大X的方法是什么? 
 *  还记得OJ378吗, OJ378是要求矩阵的第K小, 它由矩阵的左上角(矩阵最小值)和右下角(矩阵最大值),
 *  作为left和right, 然后求得中值mid = (left + right)/2, 作为比较的X, 然后求矩阵每行有多少个比X大的数的个数Y, 通过Y和K的比较, 如果Y >= K, 由当前的中值mid作为right, 进而缩小包围圈, 如果Y < K, 利用数组都是整数, 由left = left + 1的方式, 进而扩大包围圈; 直到left和right相等
 *
 *  这道题也一样, 如同OJ378的矩阵最小值最大值分别出现在矩阵左上角和右下角, distance最小是什么?
 *  distance最小可以认为是0, 最大则必然是数组的最大值减最小值, 即left = 0, right = nums[nums.size() - 1] - nums[0], 这样可以计算一个中值mid = (left + right)/2, 然后开始利用滑动数组, 计算对当前的mid, 数组内有多少对, 距离不大于mid的:
 *  (by the way, 滑动数组是一个技巧思想, 甚至不一定必须以数组出现, 单调栈同样属于滑动数组思想);
 *  对数组nums的游标a和b, 如果nums[b] - nums[a] > mid, a要往前提, 直到不再大于mid, 这样得到的b - a, 含义是: 在数组nums的b位置, 存在多少对数, 差值不大于mid, 如[1,2], mid = 1, 那么对于位置b = 1, 有1对不大于mid即元素1和2, 再如[1,2,3], mid = 2, 则有1 + 1 = 2对, 计算逻辑是什么呢?
 *  i.  初始a = 0, b = a + 1 = 1, 
 *  ii. while(b < nums.size()) { 累加nums[b] - nums[a] <= mid的对数 }
 *  iii.累计方法是: 如果发现nums[b] - nums[a]比mid大, a后移, 直到不再比mid大; 这样的结果就是当前的b, b - a的差值, 就是不大于mid的个数;
 *  iv. b继续后移, a不变(想想a为什么不变, 这和单调栈的核心思想"单调"就对上号了!), 因为a以前的和当前已经又后移的b是无需计算的, nums[当前的]b - nums[之前的a]的结果必然大于mid, 无需再尝试.
 *  vi. 最终得到对于当前的mid, 共有Y对差值不大于mid, 根据Y和K的比较关系, 根据比较关系觉得lower_bound的哪一边.
 *
 *  小结0: 不要忽略了, 本题为什么要先排序, 不排序的话, 差值将没有单调性, 滑动数组和二分查找都无依据.
 *  小结1: 本题是二分查找(lower_bound) + 滑动数组(单调无后效)的结合体, 确实有难度, 但应该掌握
 *  小结2: 滑动数组有专题, 滑动数组、单调栈等之类, 属于动态规划题的主要部分(题主个人首发), 掌握了滑动数组、单调栈这些, 动态规划在具体理解和实现环节不再有障碍.
 *
 *  关于滑动数组, 基于本题可以有一个小小的训练题用于锻炼, 对于一个有序可能有重复的数组nums和一个非负整数mid, 问有多少对数的差值不大于(/不小于/大于/小于)mid
 *  将复杂问题, 根据原理简化为最小问题, 是理解复杂问题背后的原理本质的最好方法, 当通过真正理解和解决这个最小问题, 复杂问题也会迎刃而解
 * */
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        
        /*
        priority_queue<int, vector<int>> heap;
        for (int i = 0; i < nums.size() - 1; i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (heap.size() < k) {
                    heap.push(nums[j] - nums[i]);
                } else {
                    if (nums[j] - nums[i] < heap.top()) {
                        heap.pop();
                        heap.push(nums[j] - nums[i]);
                    }
                }
            }
        }
        return heap.top();
        */

        int left = 0, right = nums[nums.size() - 1] - nums[0];
        while (left < right) {
            int mid = (left + right)/2;
            
            int st = 0, ed = 1;
            int count = 0;
            for (; ed < nums.size(); ed++) {
                while (nums[ed] - nums[st] > mid) {
                    ++st;
                }
                
                count += (ed - st);
            }
            
            if (count < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return left;
    }
};
