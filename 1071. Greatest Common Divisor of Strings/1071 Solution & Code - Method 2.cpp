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
首先需要知道一个性质, 如果 str1 和 str2 拼接后等于 str2 和 str1 拼接的字符串, 那么这个公约子串一定存在.
如果这两个拼接字符串相等, 那么 str1 和 str2 开头的部分必然相等;
此外, 如果存在一个符合要求的字符串 X, 那么一定存在一个符合要求的长度为 gcd(str1.size(), str2.size()) 的字符串 X',
因为 str1 和 str2 都会分别被替换成 len1/(gcd(len1, len2)) 和 len2/(gcd(len1, len2)) 个 X'
*/

#include <string>

class Solution {
public:
    std::string gcdOfStrings(std::string str1, std::string str2) {
        if (str1 + str2 != str2 + str1) {
            return "";
        }
        else {
            return str1.substr(0, gcd(str1.size(), str2.size()));
        }
    }

    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
};