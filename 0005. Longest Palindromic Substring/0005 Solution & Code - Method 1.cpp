/*
给定一个字符串 s, 找到 s 中最长的回文子串. 你可以假设 s 的最大长度为 1000.

示例 1:

输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案.

示例 2:

输入: "cbbd"
输出: "bb"
*/

/*
如果采用暴力法查找最长回文子串, 会出现反复判断同一个字符串是否是回文串的情况, 时间复杂度 O(n^3)
动态规划, 如果一个子串是回文串, 那么当它的左右两侧字符相同时, 新串也是回文串,
写成状态转移方程形式如下:
dp[i][j] == true if dp[i + 1][j - 1] == true and str[i] == str[j]
这里需要注意原字符串长度为奇偶的不同:
当原字符串为长度为奇数时, 只需要初始化 dp[i][i] 的情况
当原字符串长度为偶数时, 还需要初始化 dp[j - 1][j] 的情况, 我们根据 j - i == 1 && s[i] == s[j] 来判断
此外, 更新 dp 数组的方向是 j 增大 i 减小, 即从矩阵对角线出发, 向矩阵右上角更新
如果方向不对会出现递推的依赖数据没有更新的情况, 答案错误
*/

#include <string>

class Solution {
public:
	std::string longestPalindrome(std::string s) {
		int start = 0;
		int end = 0;
		std::vector<std::vector<bool>> dp(s.size(), std::vector<bool>(s.size(), false));
		for (int i = 0; i < s.size(); ++i) {
			dp[i][i] = true;
		}

		for (int j = 1; j < s.size(); ++j) {
			for (int i = j - 1; i >= 0; --i) {
				if ((j - i == 1 || dp[i + 1][j - 1] == true) && s[i] == s[j]) {
					dp[i][j] = true;
					if (end - start < j - i) {
						start = i;
						end = j;
					}
				}
			}
		}
		return s.substr(start, end - start + 1);
	}
};