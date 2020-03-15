/*
给定一个字符串 s, 找到 s 中最长的回文子串. 你可以假设 s 的最大长度为 1000.

示例 1:

输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案.

示例 2:

输入: "cbbd"
输出: "bb"
*/

/*
Manacher 算法, 能够在 O(n) 时间复杂度内找到最长回文子串.
首先我们要先处理原字符串, 在字符串的首尾和中间增加字符 '#', 这样做的目的是消除长度奇偶的影响.
然后我们需要维护下面几个变量:
一个回文半径数组 radius, 这个数组内保存的是每个字符的最长回文半径长度, 包含当前字符
回文右边界 pR, 无论从哪个字符开始向外扩, pR 都是即将到达但还未能到达的最右的位置
下面讨论字符 i 的几种外扩情况:
如果当前字符 i 不在已经扩过的回文半径中, 则从该字符开始暴力扩展, 扩展的同时更新回文右边界 pR.
当前字符 i 位于已经扩过的回文半径中, 那么我们可以直接从原来保存的信息进行推断:
首先当前字符一定是相对于此时最大回文半径的 center 对称的, 因此 radius[i] 的值应该至少等于 radius[2 * center - i]
上面这种情况对应这整个以 i 为中心的回文串都在 center - pR 这个回文串的内部
但是如果 radius[2 * center - i] > pR - i, 说明此时的 i 的镜像点 i' 的回文半径左边界超过了 center - pR 的左边界
这样按照 center 镜像时我们只能保证 i ~ pR 这一段属于回文半径的一部分, 剩下的还需要继续向外扩才能判断.
每次更新 center 的时候我们都要检查最长回文字符串的长度是否有变化, 如果有变化需要更新 start 和 end,
注意 start 和 end 分别是添加了 '#' 字符后最长回文串能够到达的首部和尾部, 最后输出结果时需要将 start 和 end 都除以 2.
*/

#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
	std::string longestPalindrome(std::string s) {
        if (s.size() < 1) {
            return "";
        }
        int start = 0, end = 0;
        std::string str = manacherString(s);

        int center = -1, pR = -1;
        std::vector<int> radius(str.size(), -1);
        for (int i = 0; i < str.size(); ++i) {
            // 用于确定不需要检验回文的区域
            radius[i] = pR > i ? std::min(radius[2 * center - i], pR - i) : 1;

            while (i + radius[i] < str.size() && i - radius[i] > -1) {
                if (str[i + radius[i]] == str[i - radius[i]]) {
                    radius[i]++;
                }
                else {
                    break;
                }
            }
            if (i + radius[i] > pR) {
                pR = i + radius[i];
                center = i;
            }
            if (end - start < 2 * radius[i] - 1) {
                start = i - radius[i] + 1;
                end = i + radius[i] - 1;
            }
        }
        return s.substr(start / 2, (end - start) / 2);
    }

private:
    std::string manacherString(std::string str) {
        std::string strNew(2 * str.length() + 1, '#');
        for (int i = 0; i < str.length(); ++i) {
            strNew[2 * i + 1] = str[i];
        }
        return strNew;
    }
};