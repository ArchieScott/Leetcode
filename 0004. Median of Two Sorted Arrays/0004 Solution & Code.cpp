/*
LeetCode 0004. 寻找两个有序数组的中位数

给定两个大小为 m 和 n 的有序数组 nums1 和 nums2,
请你找出这两个有序数组的中位数, 并且要求算法的时间复杂度为 O(log(m + n)).
你可以假设 nums1 和 nums2 不会同时为空.

示例 1:
nums1 = [1, 3]
nums2 = [2]
则中位数是 2.0

示例 2:
nums1 = [1, 2]
nums2 = [3, 4]
则中位数是 (2 + 3)/2 = 2.5
*/

/*
当看到要求对数时间复杂度, 应该想到利用二分的方式查找中位数.
首先, 在任一位置 i 将长度为 m 的数组 A 划分成两个部分:
        leftA      |        rightA
A[0],A[1],… A[i-1] | A[i],A[i+1],…A[m - 1]
由于 A 有 m 个元素, 所以有 m + 1 种划分方式, len(leftA) = i, len(rightA) = m - i
采用同样的方式, 将 B 也划分为两部分:
        leftB      |        rightB
B[0],B[1],… B[j-1] | B[j],B[j+1],…B[n - 1]
同样的, len(leftB) = j, len(rightB) = n - j

将 leftA 和 leftB 放入一个集合, 将 rightA 和 rightB 放入一个集合,
这两个集合分别为 leftPart 和 rightPart.
     leftPart      |       rightPart
A[0],A[1],… A[i-1] | A[i],A[i+1],…A[m - 1]
B[0],B[1],… B[j-1] | B[j],B[j+1],…B[n - 1]
当左右两边长度相等的时候, 如果左半边的最大值小于右半边的最小值, 可以得到中位数:
median = (max(leftPart) + min(rightPart))/2

整个调整过程其实是不断地增大 i 减小 j 或者增加 j 减小 i,
始终保持 leftPart 和 rightPart 数量之差不超过 1,
最终找到一个使得左边最大值小于右边最小值的分界线.
*/

#include <vector>
#include <algorithm>

class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        // 需要保证 m < n
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        int m = nums1.size(), n = nums2.size();
        // halfLen 表示左半边/右半边数据的个数
        int leftPart = 0, rightPart = m, halfLen = (m + n + 1)/2;
        // i 和 j 分别是 nums1 和 nums2 的划分点
        // 如果 m + n 为奇数, leftPart 会比 rightPart 多 1 个数
        int i = leftPart + (rightPart - leftPart) / 2;
        int j = halfLen - i;
        while (leftPart < rightPart) {
            // 因为 nums1 有序, leftPart 一定小于 rightPart, 因此只需要比较 nums2 的 leftPart 与 nums1 的 rightPart
            // nums2 leftPart 中最大的数比 nums1 rightPart 最小的数要大, 此时需要减小 j, 增大 i, leftPart 左边界右移
            if (i < rightPart && nums2[j - 1] > nums1[i]) {
                leftPart = i + 1;
            }
            // 其他情况都减小 rightPart, nums1[i - 1] >= nums2[j]
            // i 划分多了, 此时需要减小 i, 增大 j, rightPart 右边界左移
            else {
                rightPart = i;
            }
            // 修改了 leftPart 或者 rightPart 后需要更新划分点
            i = leftPart + (rightPart - leftPart) / 2;
            j = halfLen - i;
        }
        // 退出 while 循环时, leftPart 和 rightPart 应该相等
        // 此时已经找到了分割点, 开始讨论 leftPart 最大值与 rightPart 最小值以及一些临界条件
        int maxLeft;
        // nums1 左边为空, leftPart 最大值就是 nums2 左边最大值, 为 nums2[j - 1]
        if (i == 0) {
            maxLeft = nums2[j - 1];
        }
        else if (j == 0) {
            maxLeft = nums1[i - 1];
        }
        else {
            maxLeft = std::max(nums1[i - 1], nums2[j - 1]);
        }

        // 当总个数为奇数时, 中位数位于 leftPart
        if ((m + n) % 2 == 1) {
            return maxLeft;
        }

        int minRight;
        if (i == m) {
            minRight = nums2[j];
        }
        else if (j == n) {
            minRight = nums1[i];
        }
        else {
            minRight = std::min(nums1[i], nums2[j]);
        }

        return (maxLeft + minRight) / 2.0;
    }
};