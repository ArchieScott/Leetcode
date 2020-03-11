/*
问题描述:

给定一个整数数组 nums 和一个目标值 target,
请你在该数组中找出和为目标值的那两个整数, 并返回他们的数组下标.

你可以假设每种输入只会对应一个答案.
但是,你不能重复利用这个数组中同样的元素.

示例:

给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]
*/

/*
对于数组中的 nums[i] 来说, 符合条件的另一个数为 target - nums[i]
题目需要返回的是满足条件的下标, 为了将查询的事件减少到最低, 在第一遍遍历的时候使用哈希表将 值 - 下标 保存起来,
这样在查询 target - nums[i] 的时间复杂度可以降为 O(1).
因为题目要求不能使用重复的元素, 如果在哈希表中找到了 target - nums[i] 还需要判断是否和当前下标 i 相同,
如果相同则跳过这次循环, 不同时才返回结果.
*/

#include <vector>
#include <unordered_map>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::vector<int> res;
        std::unordered_map<int, int> idxMap;
        for (int i = 0; i < nums.size(); ++i) {
            idxMap[nums[i]] = i;
        }

        for (int i = 0; i < nums.size(); ++i) {
            if ((idxMap.find(target - nums[i]) != idxMap.end()) && idxMap[target - nums[i]] != i) {
                 res.push_back(i);
                 res.push_back(idxMap[target - nums[i]]);
                 break;
            }
        }
        return res;
    }
};
