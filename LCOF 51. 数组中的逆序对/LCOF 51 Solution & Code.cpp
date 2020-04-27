/*
LCOF 51. 数组中的逆序对

在数组中的两个数字, 如果前面一个数字大于后面的数字, 则这两个数字组成一个逆序对.
输入一个数组, 求出这个数组中的逆序对的总数.

示例 1:
输入: [7,5,6,4]
输出: 5

限制:
0 <= 数组长度 <= 50000
*/

/*
待补充.
*/

#include <vector>

class Solution {
public:
    int reversePairs(std::vector<int>& nums) {
        int vecLen = nums.size();
        if (vecLen < 2) {
            return 0;
        }
        std::vector<int> temp(vecLen, 0);
        return mergeSort(nums, temp, 0, vecLen - 1);
    }

    int mergeSort(std::vector<int>& nums, std::vector<int>& temp, int left, int right) {
        if (left >= right) {
            return 0;
        }
        int mid = left + (right - left) / 2;
        int reverseCnt = mergeSort(nums, temp, left, mid) + mergeSort(nums, temp, mid + 1, right);
        int i = left, j = mid + 1, pos = left;
        while (i <= mid && j <= right) {
            // 这样可以保证归并排序算法的稳定性
            if (nums[i] <= nums[j]) {
                temp[pos] = nums[i];
                ++i;
            }
            else {
                temp[pos] = nums[j];
                ++j;
                reverseCnt += (mid + 1 - i);
            }
            ++pos;
        }
        for (int k = i; k <= mid; ++k) {
            temp[pos++] = nums[k];
        }
        for (int k = j; k <= right; ++k) {
            temp[pos++] = nums[k];
        }
        std::copy(temp.begin() + left, temp.begin() + right + 1, nums.begin() + left);
        return reverseCnt;
    }
};