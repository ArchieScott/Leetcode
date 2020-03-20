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
最基础的双指针法暴力查找.
needle 为空时返回 0, 表示查找的空字符串从 0 位置开始;
原字符串如果比目标串短, 直接返回 -1;
否则从原字符串下标 i = 0 开始依次和目标串进行比较, 如果匹配失败, 将目标串下标重新回溯至 j = 0, 
再接着从原字符串下标 i = 1 开始和目标串进行比较, 直到 i = haystack.size() - needle.size()
*/

#include <string>

class Solution {
public:
    int strStr(std::string haystack, std::string needle) {
        if (needle.size() == 0) {
            return 0;
        }
        if (haystack.size() < needle.size()) {
            return -1;
        }
        for (int i = 0; i <= haystack.size() - needle.size(); ++i) {
            int j = 0;
            for ( ;j < needle.size(); ++j) {
                // 注意移动原字符串的下标为 haystack[i + j]
                if (needle[j] != haystack[i + j]) {
                    break;
                }
            }
            if (j == needle.size()) {
                return i;
            }
        }
        return -1;
    }
};