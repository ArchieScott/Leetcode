/*
对于字符串 S 和 T, 只有在 S = T + ... + T (T 与自身连接 1 次或多次) 时, 我们才认定 T 能除尽 S.

返回最长字符串 X, 要求满足 X 能除尽 str1 且 X 能除尽 str2.

示例 1:

输入:str1 = "ABCABC", str2 = "ABC"
输出:"ABC"

示例 2:

输入: str1 = "ABABAB", str2 = "ABAB"
输出: "AB"

示例 3:

输入: str1 = "LEET", str2 = "CODE"
输出: ""
 
提示:

1 <= str1.length <= 1000
1 <= str2.length <= 1000
str1[i] 和 str2[i] 为大写英文字母
*/

/*
首先找到 str1 和 str2 长度的所有的公约数, 存入 commDiv 数组中, 
现在我们要找 str1 和 str2 的最大公约字符串, 那么该字符串的长度一定是在 commDiv 数组中,
从后向前遍历该数组, 依次在 str1 和 str2 中截取子串, 然后将该子串拼接 str1 / commDivLens 与 str2 / commDivLens 次,
如果拼接出来的子串分别与 str1 和 str2 相等, 那么我们就找到了这个最长的子串.
*/

#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::string gcdOfStrings(std::string str1, std::string str2) {
        std::vector<int> commDiv;
        int minLens = std::min(str1.size(), str2.size());
        for (int i = 1; i <= minLens; ++i) {
            if (str1.size() % i == 0 && str2.size() % i == 0) {
                commDiv.emplace_back(i);
            }
        }
        for (auto iter = commDiv.rbegin(); iter != commDiv.rend(); ++iter) {
            auto fragment = str1.substr(0, *iter);
            std::string a, b;
            for (int i = 0; i != str1.size() / *iter; ++i) {
                a += fragment;
            }
            for (int i = 0; i != str2.size() / *iter; ++i) {
                b += fragment;
            }
            if (a == str1 && b == str2) {
                return fragment;
            }
        }
        return "";
    }
};