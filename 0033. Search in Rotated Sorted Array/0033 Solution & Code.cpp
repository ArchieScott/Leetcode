class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        int vecSize = nums.size();
        if (vecSize < 1)
            return -1;
        if (vecSize == 1)
            return nums[0] == target ? 0 : -1;
        int left = 0, right = vecSize - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
                return mid;
            if (nums[left] <= nums[mid]) {
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                }
                else {
                    left = mid + 1;
                }
            }
            else {
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};