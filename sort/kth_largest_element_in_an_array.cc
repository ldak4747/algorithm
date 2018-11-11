#include "gtest/gtest/h"

/*
 *  题意是, 给定一个无序数组, 找出其中的第K大的元素
 *  直观看, 把全部数据搞成有序, 再找出第K大貌似是唯一方法, 可以通过各种方式, 基于堆的选择、基于二分的插入, 等等
 *
 *  但这些方法都需要O(NlogN), 有没有更快的方法
 *  基于分治思想的快速排序, 是解决本题的最优解, 因为只需要找到第K大, 而不需要第K大前边和后边的元素是否有序, 
 *  只要保证该元素是第K大, 那么快速排序的方法派上用场:
 *  1、第一轮快排的partition, 如分界点是M, 那么数组nums中, M前边的都比该元素小, M后边的都比该元素大, 如果碰巧M=K, 那么显然O(N)就解决了
 *  2、如果M < K, 说明找第K大需要在M右边的元素中找第K - M - 1大, 因为M和M左边的M+1个元素肯定比M右边的元素小, 下一轮的遍历范围只需要针对M右边元素就可以了
 *  3、如果M > K, 说明所求的第K大在M的左边元素中, 那么下一轮的遍历范围只需要针对M左边元素就可以了
 *
 *  这样的方式, 最坏的时间复杂度是NlogN
 * */
class Solution {
public:
    int partition (vector<int> &nums, int st, int ed) {
        if (st <= ed) {
            int flagval = nums[ed];
            int i = st, j = st;
            for (; i < ed; i++) {
                int cur = nums[i];
                if (nums[i] > flagval) {
                    int temp = nums[j];
                    nums[j++] = nums[i];
                    nums[i] = temp;
                }
            }
            
            nums[ed] = nums[j];
            nums[j] = flagval;
            return j;
        } else {
            return -1;
        }
    }
    
    int findKthLargest(vector<int>& nums, int k) {
        int part = partition(nums, 0, nums.size() - 1);
        if (part == k - 1) {
            return nums[part];
        } else if (part > k - 1) {
            vector<int> v(part);
            copy(nums.begin(), nums.begin() + part, v.begin());
            return findKthLargest(v, k);
        } else {
            vector<int> v(nums.size() - part - 1);
            copy(nums.begin() + part + 1, nums.end(), v.begin());
            return findKthLargest(v, k - part - 1);
        }
    }
};
