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
暴力匹配采用的是回溯的思想, 我们用 si 和 pj 分别表示字符串和匹配串的匹配位置, 依次比较,
没有匹配成功的时候, process 什么都不做, 直接返回 false;
否则, 我们先检查 regx[pj] 的下一个字符是否是 '*', 如果不是, 直接进行下面的对比:
如果 regx 中对应的是相同字符或者 '.' 字符, 并且 si 和 pj 都没有到达末尾, 说明匹配成功, regx 和 text 都向后移动一个字符;
如果 regx[pj] 下一个字符是 '*', 那么有两种匹配情况:
第一种 '*' 匹配 0 个 regx[pj], 此时 pj 直接跳过 regx[pj] 和 '*', 整个过程变为 process(str, si, regx, pj + 2),
这种情况需要注意 pj 的范围, 因为要检查 pj + 2 的情况是 pj + 1 为 '*', 为了保证 pj 不越界, 应该取 pj + 1 < regx.size(), 此时是最后一个字符为 '*' 的情况;
第二种 '*' 匹配 1 或多个 regx[pj] 的情况, 此时需要 regx[pj] 与 str[si] 相同或者为字符 '.',
这种情况下 si 向后移动, pj 不变, 因为后面还可能继续匹配到相同的 regx[pj], 
此时也需要注意个一个边界条件, 即 si 已经匹配到最后一个字符了, pj 后面还有一个 '*' 未匹配, 而匹配成功必须要求 text 和 regx 都到达 end() 才行,
因此我们让 si <= str.size(), 让它能够取到 text 最后的空字符, 此时 regx 通过 pj + 2 也能够取得最后的空字符, 成功匹配.
*/

#include <string>

class Solution {
public:
    bool isMatch(std::string s, std::string p) {
        process(s, 0, p, 0);
        return res;
    }

    void process(std::string& str, int si, std::string& regx, int pj) {
        if (res) {
            return;
        }
        if (pj == regx.size() && si == str.size()) {
            res = true;
            return;
        }
        if (si <= str.size() && pj + 1 < regx.size() && regx[pj + 1] == '*') {
            process(str, si, regx, pj + 2);
            if (str[si] == regx[pj] || regx[pj] == '.') {
                process(str, si + 1, regx, pj);
            }
        }
        if (si < str.size() && pj < regx.size() && (str[si] == regx[pj] || regx[pj] == '.')) {
            process(str, si + 1, regx, pj + 1);
        }
    }

private:
    bool res{false};
};