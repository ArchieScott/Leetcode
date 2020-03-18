/*
LeetCode 0003. 无重复字符的最长子串

给定一个字符串, 请你找出其中不含有重复字符的最长子串的长度.

示例 1:
输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc", 所以其长度为 3.

示例 2:
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b", 所以其长度为 1.

示例 3:
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke", 所以其长度为 3.

请注意, 你的答案必须是子串的长度, "pwke" 是一个子序列, 不是子串.
*/

/*
对于找子串的这一类题目, 有一种比较万能的思路, 即我们可以遍历整个字符串, 依次判断必须以当前字符 str[i] 结尾的最长不重复子串的长度是多少,
当我们遍历完整个字符串, 也就相当于找到了必须以整个字符串最后一个字符结尾的最长不重复子串的长度, 然后取 max 即可.
因为整个过程中遍历了所有可能的子串, 时间复杂度为 O(n), 且不会有遗漏.
接下来我们看 str[i - 1] 与 str[i] 之间的递推关系:
假设必须以 str[i - 1] 结尾的最长不重复子串是从下标 pre + 1 开始计算的, 即 pre + 1 ~ str[i - 1] 是不重复的, 而 pre 与该字符串中的某个字符是一样的,
现在扩展到 str[i] 时有两种情况:
1. pre + 1 ~ i - 1 中不存在 str[i], 则最长子串长度为 pre + 1 ~ i
2. pre + 1 ~ i - 1 中存在 str[i], 则最长子串长度为 charMap[str[i]] ~ i, 其中 charMap[str[i]] 表示字符 str[i] 最晚出现的位置.
满足条件 2 的时候还需要更新 pre 为 charMap[str[i]], pre 表示的是最长不重复子串的前一个字符.
*/

#include <string>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        if (s.size() < 1) {
            return 0;
        }
        // charMap 中保存字符最近一次出现的下标
        std::unordered_map<char, int> charMap;

        int pre = -1;
        int curLen = 0;
        // res 中一直保存的是最大值, 注意和 curLen 的必须以 str[i] 结尾的最大值区分
        int res = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (charMap.find(s[i]) == charMap.end()) {
                charMap[s[i]] = -1;
            }
            // 如果字符 s[i] 最近出现过, 下标一定会大于 pre, 更新 pre 并计算长度
            pre = std::max(pre, charMap[s[i]]);
            curLen = i - pre;
            res = std::max(res, curLen);
            charMap[s[i]] = i;
        }
        return res;
    }
};