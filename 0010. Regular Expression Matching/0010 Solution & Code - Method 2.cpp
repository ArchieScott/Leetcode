/*
给你一个字符串 s 和一个字符规律 p, 请你来实现一个支持 '.' 和 '*' 的正则表达式匹配.
'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素
所谓匹配, 是要涵盖整个字符串 s 的, 而不是部分字符串.

说明:
s 可能为空, 且只包含从 a-z 的小写字母.
p 可能为空, 且只包含从 a-z 的小写字母, 以及字符 '.' 和 '*'

示例 1:
输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串.

示例 2:
输入:
s = "aa"
p = "a*"
输出: true
解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a', 字符串 "aa" 可被视为 'a' 重复了一次.

示例 3:
输入:
s = "ab"
p = ".*"
输出: true
解释: ".*" 表示可匹配零个或多个任意字符

示例 4:
输入:
s = "aab"
p = "c*a*b"
输出: true
解释: 因为 '*' 表示零个或多个, 这里 'c' 为 0 个, 'a' 被重复一次, 因此可以匹配字符串 "aab".

示例 5:
输入:
s = "mississippi"
p = "mis*is*p*."
输出: false
*/

/*
使用动态规划, 将每个位置比较的结果都保存下来, dp[i][j] 表示 text 的前 i 个字符与 regx 的前 j 个字符的匹配结果,
因此 dp[i][j] 表示的是 s[0 ~ i-1] 和 p[0 ~ j-1] 的匹配结果;
首先我们初始化 base case, dp[0][0] 为 true, 即两个字符串都为空能够匹配成功;
dp[i][0] 都为 false, 因为无法匹配 regx;
dp[0][j] 只有在类似 "a*b*c*" 这种场合为 true, 匹配到空字符串, 因此当 p[j - 1] 为 '*' 时, dp[0][j] 与 dp[0][j - 2] 匹配状态相同;
接下来我们从 i = 1, j = 1 开始更新 dp 数组:
当 s[i - 1] == p[j - 1] 或者 p[j - 1] == '.' , 说明 s 的第 i 个字符与 p 的第 j 个字符匹配成功, 此时 dp[i][j] 与 dp[i - 1][j - 1] 匹配状态相同;
如果 p[j - 1] == '*', 需要考虑三种情况:
匹配 0 个, 比如 ab 和 abc*, 没有 c* 也能匹配上, 此时有 dp[i][j] = dp[i][j - 2];
匹配 1 个, 比如 ab 和 ab*, 没有 * 也能匹配上, 此时有 dp[i][j] = dp[i][j - 1];
匹配多个, 比如 aabbb 和 aab*, b* 匹配到了三个 b, 此时只需要看 aabb 和 aab* 能否匹配上, dp[i][j] = dp[i - 1][j];
*/

#include <string>
#include <vector>

class Solution {
public:
    bool isMatch(std::string s, std::string p) {

        std::vector<std::vector<bool>> dp(s.size() + 1, std::vector<bool>(p.size() + 1, false));
        dp[0][0] = true;

        for (int i = 1; i <= s.size(); ++i) {
            dp[i][0] = false;
        }

        for (int j = 1; j <= p.size(); ++j) {
            if (p[j - 1] == '*' && dp[0][j - 2]) {
                dp[0][j] = true;
            }
        }
        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 1; j <= p.size(); ++j) {
                if (s[i - 1] == p[j - 1] || p[j - 1] == '.') {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                if (p[j - 1] == '*') {
                    if (p[j - 2] != s[i - 1] && p[j - 2] != '.') {
                        dp[i][j] = dp[i][j - 2];
                    }
                    else {
                        dp[i][j] = dp[i - 1][j] || dp[i][j - 1] || dp[i][j - 2];
                    }
                }
            }
        }
        return dp[s.size()][p.size()];
    }
};