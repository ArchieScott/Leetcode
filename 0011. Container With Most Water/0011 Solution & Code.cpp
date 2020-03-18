/*
LeetCode 0011. 盛水最多的容器

给你 n 个非负整数 a1, a2, ..., an, 每个数代表坐标中的一个点 (i, ai).
在坐标内画 n 条垂直线, 垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0).
找出其中的两条线, 使得它们与 x 轴共同构成的容器可以容纳最多的水.

说明: 你不能倾斜容器, 且 n 的值至少为 2.
*/

/*
这道题要我们求的是垂直的两条线段与坐标轴围成的一个矩形区域的最大面积, 这个面积的大小会受到较短的那条线段的影响.
我们分别使用两个指针指向线段长度数组的头部和尾部, 并且将此时的面积存入 res 中,
接下来移动指针的逻辑是这样的:
因为接下来 j - i 只能减小, 如果我们要找到面积更大的矩阵, 就必须将此时长度更短的那一边舍弃,
因为如果不舍弃, 高度就无法增加, 随着边长减小, 最终的面积只会越来越小. 
*/

#include <vector>
#include <algorithm>

class Solution {
public:
    int maxArea(std::vector<int>& height) {
        int res = INT_MIN;
        for (int i = 0, j = height.size() - 1; i < j;) {
            int lowerHeight = std::min(height[i], height[j]);
            res = std::max(res, (j - i) * lowerHeight);
            if (lowerHeight == height[i]) {
                ++i;
            }
            else {
                --j;
            }
        }
        return res;
    }
};