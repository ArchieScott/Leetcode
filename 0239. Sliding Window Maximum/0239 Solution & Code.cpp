/*
LeetCode 0239. 滑动窗口最大值

给定一个数组 nums, 有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧. 你只可以看到在滑动窗口内的 k 个数字. 滑动窗口每次只向右移动一位. 
返回滑动窗口中的最大值. 

示例:
输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
输出: [3,3,5,5,6,7] 
解释: 
  滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

提示: 
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
1 <= k <= nums.length
*/

/*
双端队列实现单调队列
*/


class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int elemNum = nums.size();
        if (elemNum < 1 || k < 1)
            return {};
        std::vector<int> res;
        std::deque<int> monoQueue;

        for (int i = 0; i < elemNum; ++i) {
            if (!monoQueue.empty() && monoQueue.front() <= i - k) {
                monoQueue.pop_front();
            }
            while (!monoQueue.empty() && nums[i] > nums[monoQueue.back()]) {
                monoQueue.pop_back();
            }
            monoQueue.push_back(i);
            if (i >= k - 1)
                res.push_back(nums[monoQueue.front()]);
        }
        return res;
    }
};