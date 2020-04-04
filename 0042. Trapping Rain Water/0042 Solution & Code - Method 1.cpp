/*
LeetCode 0042. 接雨水

给定 n 个非负整数表示每个宽度为 1 的柱子的高度图, 计算按此排列的柱子, 下雨之后能接多少雨水.

示例:
输入: [0,1,0,2,1,0,1,3,2,1,2,1]
输出: 6
*/

/*
单调栈结构解决的问题是在一个数组中, 找到所有的数中在它的左边离它最近比它大的, 右边离它最近比它大的, 时间复杂度为 O(n).
这种结构正好与本题的要求契合, 对于某一个高度, 我们需要找到它的两边比它大的, 这样才能接到水.
首先申请一个栈结构, 栈中存放的是对应柱子的下标, 从栈底到栈顶下标对应柱子的高度依次减小,
当一个新的柱子高度小于等于栈顶柱子高度时, 直接将新柱子的下标入栈,
当一个新柱子的高度大于栈顶柱子的高度时, 说明出现了可能能够接到水的情况, 因为此时栈顶的下一个元素和新元素高度都是要大于栈顶元素的,
那么我们将栈顶元素出栈, 计算栈顶元素左边 - 栈顶元素 - 新元素围成的区域面积, 注意这里在计算高度的时候需要减去栈顶元素的高度,
这样就算栈中有相同元素也不会有影响, 因为减出来的高度为 0;
最后我们将围出来的面积加到 res 中, 这样一直循环直到栈为空或者栈顶元素大于将要入栈的新元素, 将新元素入栈, 继续遍历完 height 数组.
*/

#include <vector>
#include <stack>

class Solution {
public:
    int trap(std::vector<int>& height) {
        int res = 0;
        std::stack<int> numSt;
        for (int i = 0; i < height.size(); ++i) {
            while (!numSt.empty() && height[numSt.top()] < height[i]) {
                int cur = numSt.top();
                numSt.pop();
                if (numSt.empty()) {
                    break;
                }
                int left = numSt.top();
                int right = i;
                int h = std::min(height[left], height[right]) - height[cur];
                res += (right - left - 1) * h;
            }
            numSt.push(i);
        }
        return res;
    }
};