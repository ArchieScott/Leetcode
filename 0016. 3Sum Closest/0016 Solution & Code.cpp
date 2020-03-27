/*
LeetCode 0016. 最接近的三数之和

给定一个包括 n 个整数的数组 nums 和 一个目标值 target.
找出 nums 中的三个整数, 使得它们的和与 target 最接近, 返回这三个数的和.
假定每组输入只存在唯一答案.

例如, 给定数组 nums = [-1, 2, 1, -4], 和 target = 1.
与 target 最接近的三个数的和为 2. (-1 + 2 + 1 = 2).
*/

/*
这道题和 0015 做法类似, 使用排序 + 双指针解决,
首先对原数组排序, 然后从第一个元素开始, 依次确定一个数, 剩下的两个数分别从首尾向中间夹逼,
我们分别记录三个数的和, 当和等于 target 时, 说明此时离 target 最近, 直接返回 sum,
如果 sum < target, 说明此时和小于 target, 比较 sum - target 和 diff, 如果小于 diff 就更新 diff, 然后将 leftIdx++,
否则就 rightIdx--, 并且更新 diff, 当外层 for 循环遍历结束后就找到 diff.
*/

#include <vector>
#include <limits>
#include <algorithm>

class Solution {
public:
    int threeSumClosest(std::vector<int>& nums, int target) {
        if (nums.size() < 3) {
            return INT_MIN;
        }
        int res = INT_MAX;
        int diff = INT_MAX;
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); ++i) {
            int leftIdx = i + 1;
            int rightIdx = nums.size() - 1;
            while(leftIdx < rightIdx) {
                int sum = nums[i] + nums[leftIdx] + nums[rightIdx];
                if (sum == target) {
                    return sum;
                }
                else if (sum < target) {
                    if (target - sum < diff) {
                        diff = target - sum;
                        res = sum;
                    }
                    leftIdx++;
                }
                else {
                    if (sum - target < diff) {
                        diff = sum - target;
                        res = sum;
                    }
                    rightIdx--; 
                }
            }
        }
        return res;
    }
};