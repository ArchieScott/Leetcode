/*
字符串压缩.利用字符重复出现的次数, 编写一种方法, 实现基本的字符串压缩功能.
比如, 字符串 aabcccccaaa 会变为 a2b1c5a3.
若压缩后的字符串没有变短, 则返回原先的字符串, 你可以假设字符串中只包含小写英文字母.

示例1:

输入: "aabcccccaaa"
输出: "a2b1c5a3"

示例2:

输入: "abbccd"
输出: "abbccd"
解释: "abbccd" 压缩后为 "a1b2c2d1", 比原字符串长度更长.

提示：

字符串长度在 [0, 50000] 范围内.
*/

/*
首先准备两个 index i 和 j, 用 i 来表示一个所有字符都相同的子串的第一个字符下标, 用 j 来遍历,
如果当前字符和下一个字符相等, 那么 count++, 并且 j 也向后移动, 
这里需要注意, 如果当前字符为字符串 S 的最后一个字符, S[j + 1] 也依然是有效的, 它返回一个空字符, 可以参考 https://archiescott.github.io//posts/7651320d/ Q284
当下一个字符和当前字符不相等, 跳出 while 循环并将 j 移动到下一个字符处, 此时的 i 仍然指向前一串相同的字符,
我们将 S[i] 与对应的 count 加入 res 中, 修改下标 i, 如果 i 没有到字符串末尾, 继续下一次循环.
最后需要注意返回的是原字符串与新字符串中的较短者.
*/

class Solution {
public:
    std::string compressString(std::string S) {
        std::string res;
        for (int i = 0, j = 0; i < S.size(); ) {
            int count = 1;
            while (S[j] == S[j + 1]) {
                ++count;
                ++j;
            }
            ++j;
            res += S[i] + std::to_string(count);
            i = j;
        }
        return res.size() >= S.size() ? S : res;
    }
};