/*
LeetCode 0028. 实现 strStr() 函数

给定一个 haystack 字符串和一个 needle 字符串, 在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从 0 开始).
如果不存在, 则返回 -1. 当 needle 是空字符串时应该返回 0, 和 C 语言的 strstr() 函数以及 Java的 indexOf() 定义相符.

示例 1:
输入: haystack = "hello", needle = "ll"
输出: 2

示例 2:
输入: haystack = "aaaaa", needle = "bba"
输出: -1
*/

/*
KMP 算法实际解决的是字符串的包含问题, 它之所以比前一种暴力匹配的方法快是因为前面的匹配信息能够指导后面的匹配.
KMP 算法的核心就是不让主串的指针回溯, 而是根据 next 数组的指示回溯子串的指针;
KMP 算法要求我们先求出 next 数组, 该数组中的每一个元素表示的是每个位置之前的子串的最长前缀与最长后缀的匹配长度.
next 数组的 next[0] next[1] 分别为 -1 和 0, 通过不断调整匹配前缀后一个字符 cn 来计算原字符串每个位置的前后缀最长匹配长度.
在匹配的过程中, 我们从头开始依次比较, 因为原字符串不会回溯, 所以当 hIdx 和 nIdx 分别到达末尾时匹配就结束.
结束时如果 nIdx 到达匹配串的末尾, 说明找到了字符串.
*/

#include <string>
#include <vector>

class Solution {
public:
    int strStr(std::string haystack, std::string needle) {
        if (needle.size() == 0) {
            return 0;
        }
        if (haystack.size() < needle.size()) {
            return -1;
        }
        auto next = getNextArray(needle);
        int hIdx = 0, nIdx = 0;
        while (hIdx < haystack.size() && nIdx < needle.size()) {
            if (haystack[hIdx] == needle[nIdx]) {
                hIdx++;
                nIdx++;
            }
            // 子串回溯到起点了, 因为上面的的比较条件也不满足, 说明子串的第一个字符与母串的当前字符也不匹配, 母串 hIdx++
            else if (next[nIdx] == -1) {
                hIdx++;
            }
            // 向前找另一个能够匹配的位置
            else {
                nIdx = next[nIdx];
            }
        }
        return nIdx == needle.size() ? hIdx - nIdx : -1;
    }
private:
    std::vector<int> getNextArray(std::string str) {
        std::vector<int> next(str.size(), -1);
        if (str.size() == 1) {
            return next;
        }
        next[1] = 0;
        int i = 2;
        // cn 表示与后缀匹配的前缀的下一个字符
        int cn = 0;
        while (i < str.size()) {
            // 如果前缀的下一个字符能够与后缀的下一个字符匹配, next[i]++, cn++
            if (str[i - 1] == str[cn]) {
                next[i++] = ++cn;
            }
            // 如果不能匹配, cn > 0, 因为 next[cn] 表示的是 0 ~ cn - 1 的匹配情况
            // next[cn] > 0, 说明 cn 前面还有能够匹配的前后缀, 这个更短的前缀能够与前面较长的后缀匹配上,
            // 因此我们只需要看这个较短前缀的下一个字符能否和较长后缀的下一个字符匹配成功即可
            else if (cn > 0) {
                cn = next[cn];
            }
            else {
                next[i++] = 0;
            }
        }
        return next;
    }
};