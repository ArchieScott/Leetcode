/*
LeetCode 0072. 编辑距离

给你两个单词 word1 和 word2, 请你计算出将 word1 转换成 word2 所使用的最少操作数.
你可以对一个单词进行如下三种操作: 
插入一个字符
删除一个字符
替换一个字符
 
示例 1: 
输入: word1 = "horse", word2 = "ros"
输出: 3
解释: 
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')

示例 2: 
输入: word1 = "intention", word2 = "execution"
输出: 5
解释: 
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')
*/

/*
动态规划, 使用一个二维数组 dp[i][j], 数组中的内容表示 word1 的前 i 个字符要修改为 word2 的前 j 个字符的修改距离.
那么当第 i 个字符与第 j 个字符相同的时候, 无需修改, dp[i][j] = dp[i - 1][j - 1];
否则假设从 word1 的前 i 个字符到 word2 的前 j 个字符最少需要修改 a 次,
那么这个 a 可能由 3 个途径得到:
1. word2 的前 j - 1 个字符后增加一个字符, 那么 a = dp[i - 1][j] + 1;
也就是说对于 word1 的第 i 个字符, 我们在 word2 的最后添加了一个相同字符, 那么 dp[i][j] 最小可以为 dp[i - 1][j] + 1;
2. word1 的前 i - 1 个字符后增加一个字符, 那么 a = dp[i][j - 1] + 1;
也就是说对于 word2 的第 j 个字符, 我们在 word1 的最后添加了一个相同字符, 那么 dp[i][j] 最小可以为 dp[i][j - 1] + 1;
3. word1 修改第 i 个字符, 那么 a = dp[i - 1][j - 1] + 1;
然后我们还需要将 dp 数组初始化, 申请的矩阵大小为 (word1Len + 1) * (word2Len + 1).
*/

class Solution {
public:
    int minDistance(std::string word1, std::string word2) {
        int word1Len = word1.size();
        int word2Len = word2.size();
        if (word1Len == 0 || word2Len == 0) {
            return word1Len == 0 ? word2Len : word1Len;
        }
        std::vector<std::vector<int>> dp(word1Len + 1, std::vector<int>(word2Len + 1, 0));
        for (int i = 1; i < word1Len + 1; ++i) {
            dp[i][0] = i;
        }
        for (int j = 1; j < word2Len + 1; ++j) {
            dp[0][j] = j;
        }
        for (int i = 1; i < word1Len + 1; ++i) {
            for (int j = 1; j < word2Len + 1; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                }
            }
        }
        return dp[word1Len][word2Len];
    }
};