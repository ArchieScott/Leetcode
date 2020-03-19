/*
LeetCode 0014. 最长公共前缀

编写一个函数来查找字符串数组中的最长公共前缀.
如果不存在公共前缀, 返回空字符串 "".
说明: 所有输入只包含小写字母 a-z.

示例 1:
输入: ["flower","flow","flight"]
输出: "fl"

示例 2:
输入: ["dog","racecar","car"]
输出: ""
解释: 输入不存在公共前缀.
*/

/*
垂直扫描法.
以第 1 个字符串为 base, 将第 2 ~ n 个字符串依次从第 1 个字符开始扫描,
顺序为:
| 1. x xxxxx...
| 2. x xxx.....
v      .   .
|      .   .
|      .   .
v n. x xxxx....
如果发现某一个字符串中的某一个字符不等于第 1 个字符串对应的字符, 立即返回 strs[0].substr(0, i)
如果遍历结束了都没有找到不相同的字符, 则直接返回 strs[0], 此时 strs[0] 为最短或者并列最短的字符串.
*/

#include <string>
#include <vector>

class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        if (strs.size() < 1) {
            return "";
        }

        for (int i = 0; i < strs[0].size(); ++i) {
            for (int j = 1; j < strs.size(); ++j) {
                if (strs[j][i] != strs[0][i]) {
                    return strs[0].substr(0, i);
                }
            }
        }

        return strs[0];
    }
};