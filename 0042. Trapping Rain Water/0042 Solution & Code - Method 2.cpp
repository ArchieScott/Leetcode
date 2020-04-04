/*
LeetCode 0042. 接雨水

给定 n 个非负整数表示每个宽度为 1 的柱子的高度图, 计算按此排列的柱子, 下雨之后能接多少雨水.

示例:
输入: [0,1,0,2,1,0,1,3,2,1,2,1]
输出: 6
*/

/*
双指针, 首先找到整个数组中最高的柱子的下标, 然后从左右分别使用两个指针向这个最高的柱子移动;
在遍历的过程中不断保存当前遍历的最高柱子的高度, 如果高度得到了更新, 说明从左至右或从右至左高度是增加的,
此时是不可能可中间最高的柱子构成一个高 - 低 - 高的组合的, 我们只记录并且移动指针,
如果当前指向的柱子高度小于遍历过程中记录的最高值, 说明能够接到雨水, 数量为 1 * (maxHeight - height[i])
这样遍历完最高柱子的左右两边, 加得的结果就是答案.
*/

#include <vector>

class Solution {
public:
    int trap(std::vector<int>& height) {
        int res = 0, maxIdx = -1, maxHeight = INT_MIN;
        for (int i = 0; i < height.size(); ++i) {
            if (height[i] > maxHeight) {
                maxHeight = height[i];
                maxIdx = i;
            }
        }
        maxHeight = INT_MIN;
        for (int i = 0; i < maxIdx; ++i) {
            if (height[i] > maxHeight) {
                maxHeight = height[i];
                continue;
            }
            else {
                res += (maxHeight - height[i]);
            }
        }
        maxHeight = INT_MIN;
        for (int i = height.size() - 1; i > maxIdx; --i) {
            if (height[i] > maxHeight) {
                maxHeight = height[i];
                continue;
            }
            else {
                res += (maxHeight - height[i]);
            }
        }
        return res;
    }
};