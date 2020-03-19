/*
LeetCode 0015. 三数之和

给你一个包含 n 个整数的数组 nums, 判断 nums 中是否存在三个元素 a, b, c, 使得 a + b + c = 0.
请你找出所有满足条件且不重复的三元组.
注意: 答案中不可以包含重复的三元组.

示例:
给定数组 nums = [-1, 0, 1, 2, -1, -4], 
满足要求的三元组集合为:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/

/*
这道题有不少坑, 我们一个一个来说.
首先确定方法, 对于 x 数之和, 有一种比较通用的解题方法, 即双指针遍历, 在确定了其他数的值之后, 通过双指针夹逼的方式来确定剩下的两个数.
因此这道题, 需要有两层循环, 外层用于遍历确认第一个数, 内层用于双指针遍历确认另外两个数.
首先排除特殊情况, 即数组元素个数小于 3 的情况;
将数组排序, 此时重复的元素均排在一起, 开始遍历数组:
从第 2 个数开始, 如果某一个数与前一个数相等, 此时如果进行内层循环的遍历一定会出现重复解, 应该直接 continue 跳过;
如果遍历到某一个 i 发现 nums[i] > 0, 因为数组已经是有序的了, 不可能再出现 nums[i] 和后面数之和等于 0, 直接 break;
令左指针为 i + 1, 右指针为 nums.size() - 1, 当 nums[i] + nums[leftIdx] + nums[rightIdx] == 0 时将结果 push 进 res 数组中,
接下来是关键的一步, nums[leftIdx] 与 nums[rightIdx] 也可能出现连续重复的元素, 也需要比较跳过,
leftIdx 与 rightIdx 应该一直指向重复字符/已计算字符的下一个字符去寻找新的解, 所以在跳过相同字符后还需要 ++leftIdx --rightIdx
如果 3Sum 的结果不等于 0 而是大于 0, 说明总和大了, 需要减小 rightIdx, 反之增加 leftIdx
*/

#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::vector<std::vector<int>> res;
        if (nums.size() < 3) {
            return res;
        }
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); ++i) {
            // 如果当前数与前一个数相等, 直接 continue ++i, 去除重复元素
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            // 不会再有 3sum = 0 的情况, 直接 break
            if (nums[i] > 0) {
                break;
            }
            int leftIdx = i + 1;
            int rightIdx = nums.size() - 1;
            while (leftIdx < rightIdx) {
                if (nums[i] + nums[leftIdx] + nums[rightIdx] == 0) {
                    res.push_back({nums[i], nums[leftIdx], nums[rightIdx]});
                    // 找到 res 后还需要跳过相同解
                    while (leftIdx < rightIdx && nums[leftIdx] == nums[leftIdx + 1]) {
                        ++leftIdx;
                    }
                    while (leftIdx < rightIdx && nums[rightIdx] == nums[rightIdx - 1]) {
                        --rightIdx;
                    }
                    // 上面的步骤执行完 leftIdx 与 rightIdx 分别指向相同元素的最后一个字符
                    leftIdx++;
                    rightIdx--;
                }
                else if (nums[i] + nums[leftIdx] + nums[rightIdx] < 0) {
                    leftIdx++;
                }
                else if (nums[i] + nums[leftIdx] + nums[rightIdx] > 0) {
                    rightIdx--;
                }
            }
        }
        return res;
    }
};