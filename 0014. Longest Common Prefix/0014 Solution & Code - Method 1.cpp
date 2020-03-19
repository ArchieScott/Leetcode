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
水平扫描法.
以第 1 个字符串为基准, 将其作为 prefix, 然后依次扫描第 2 ~ n 个字符串查找 prefix,
如果没有找到 prefix, 将 prefix 截掉最后一个字符再重新查找 strs[n].find(prefix.substr(0, prefix.size() - 1)),
第 2 个字符串必须要循环至找到 prefix 才能继续查找第 3 个字符串;
顺序为:
--->--->--->
1. xxxxxx...
2. xxxx.....
     .   .
     .   .
     .   .
n. xxxxx....
有一点需要注意, 就是 strs.find 方法的返回值, 如果查找成功它返回的是找到子串的首字符位置, 没有找到返回 std::string::npos (-1)
*/

#include <string>
#include <vector>

class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        if (strs.size() < 1) {
            return "";
        }

        int i = 0, j = 0;
        std::string prefix = strs[0];

        for (int k = 1; k < strs.size(); ++k) {
            while (strs[k].find(prefix) != 0) {
                prefix = prefix.substr(0, prefix.size() - 1);
                if (prefix == "") {
                    return "";
                }
            }
        }
        return prefix;
    }
};