/*
LeetCode 0018. 四数之和

给定一个包含 n 个整数的数组 nums 和一个目标值 target,
判断 nums 中是否存在四个元素 a, b, c 和 d, 使得 a + b + c + d 的值与 target 相等.
找出所有满足条件且不重复的四元组.

示例: 
给定数组 nums = [1, 0, -1, 0, -2, 2], 和 target = 0.
满足要求的四元组集合为: 
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
*/

/*
这道题仍然是 0015 题的变形, 三数之和我们采用双指针的方法, 确定一个数, 另外两个数通过指针遍历获得,
那么同样的, 四数之和需要我们确定两个数, 另外两个数通过指针遍历获得, 难点仍然在于消除重复解.
首先将数组排序, 相同的数排列到一起.
对于第一个确定的数来说, 当 i > 0, 如果当前数和前一个数相等, 直接 continue 跳过当前循环到下一个数, 
因为相同数字后面的循环都重新执行一遍, 必然产生重复解;
同样的对于第二个确定的数来说, 当 j > i + 1, 如果 nums[j] == nums[j - 1], 也直接跳过当前循环到下一个数;
将 leftIdx 指向 j + 1, rightIdx 指向 nums.size() - 1, 当 leftIdx < rightIdx 时, 依次计算四数之和,
如果 sum == target, 将结果存入 res 中, 同时对下一个数进行判断, 如果 nums[leftIdx] == nums[leftIdx + 1] 并且 leftIdx < rightIdx, leftIdx++,
注意这个循环结束的时候 leftIdx 指向的是最后一个相同数字, 因此还需要 leftIdx++, rightIdx 也是同样的操作,
如果 sum < target, 说明选的数小了, leftIdx++;
如果 sum > target, 说明选的数大了, rightIdx--;
*/

#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
        std::vector<std::vector<int>> res;
        if (nums.size() < 4) {
            return res;
        }
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 3; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            for (int j = i + 1; j < nums.size() - 2; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }
                int leftIdx = j + 1;
                int rightIdx = nums.size() - 1;
                // 优化 1: 因为数组有序, 当从 j 开始的连续三个数的和假设 nums[i] 大于 target
                // 说明后面的和一定都是大于 target, 不需要计算直接 break 跳出当前 j 的循环
                if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) {
                    break;
                }
                // 优化 2: 如果 nums[i] + nums[j] 和最后两个数的和小于 target, 说明这个 nums[i] 太小了
                // 直接 continue 到下一个 j 来尝试
                if (nums[i] + nums[j] + nums[rightIdx - 1] + nums[rightIdx] < target) {
                    continue;
                }
                while (leftIdx < rightIdx) {
                    int sum = nums[i] + nums[j] + nums[leftIdx] + nums[rightIdx];
                    if (sum == target) {
                        res.push_back({nums[i], nums[j], nums[leftIdx], nums[rightIdx]});
                        while (leftIdx < rightIdx && nums[leftIdx] == nums[leftIdx + 1]) {
                            ++leftIdx;
                        }
                        while (leftIdx < rightIdx && nums[rightIdx] == nums[rightIdx - 1]) {
                            --rightIdx;
                        }
                        leftIdx++;
                        rightIdx--;
                    }
                    else if (sum < target) {
                        leftIdx++;
                    }
                    else if (sum > target) {
                        rightIdx--;
                    }
                }
            }
        }
        return res;
    }
};