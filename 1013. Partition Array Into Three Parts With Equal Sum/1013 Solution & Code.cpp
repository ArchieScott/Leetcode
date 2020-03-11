/*
给你一个整数数组 A, 只有可以将其划分为三个和相等的非空部分时才返回 true, 否则返回 false.
形式上, 如果可以找出索引 i+1 < j 且满足 (A[0] + A[1] + ... + A[i] == A[i+1] + A[i+2] + ... + A[j-1] == A[j] + A[j-1] + ... + A[A.length - 1]) 就可以将数组三等分.

示例 1:

输出: [0,2,1,-6,6,-7,9,1,2,0,1]
输出: true
解释: 0 + 2 + 1 = -6 + 6 - 7 + 9 + 1 = 2 + 0 + 1

示例 2:

输入: [0,2,1,-6,6,7,9,-1,2,0,1]
输出: false

示例 3:

输入: [3,3,6,5,-2,2,5,1,-9,4]
输出: true
解释: 3 + 3 = 6 = 5 - 2 + 2 + 5 + 1 - 9 + 4
 

提示:

3 <= A.length <= 50000
-10^4 <= A[i] <= 10^4
*/

/*
这道题三个和相同的部分都分别是连续的序列,
我们首先判断总和是否能被 3 整除, 如果不行, 直接返回 false.
然后计算出每个部分的 target, 从数组头部开始遍历, 每次累加和 partSum == target 时就将 partTimes 标志加 1, 然后从下一个数开始重新累加,
当最后等于 target 的次数大于等于 3 时返回 true,
需要注意 target == 0 的情况, 此时的 partTimes 可能大于 3
*/

class Solution {
public:
    bool canThreePartsEqualSum(std::vector<int>& A) {
        // template< class InputIt, class T >
        // constexpr T accumulate( InputIt first, InputIt last, T init );
        int sum = std::accumulate(A.begin(), A.end(), 0);
        if (sum % 3 != 0) {
            return false;
        }
        int target = sum / 3;
        int partSum = 0;
        int i = 0;
        int partTimes = 0;
        while (i < A.size()) {
            partSum += A[i++];
            if (partSum == target) {
                partTimes++;
                partSum = 0;
            }
        }
        return partTimes >= 3;
    }
};