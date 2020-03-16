/*
请你来实现一个 atoi 函数, 使其能将字符串转换成整数.

首先, 该函数会根据需要丢弃无用的开头空格字符, 直到寻找到第一个非空格的字符为止.

当我们寻找到的第一个非空字符为正或者负号时, 则将该符号与之后面尽可能多的连续数字组合起来, 作为该整数的正负号;
假如第一个非空字符是数字, 则直接将其与之后连续的数字字符组合起来, 形成整数.

该字符串除了有效的整数部分之后也可能会存在多余的字符, 这些字符可以被忽略, 它们对于函数不应该造成影响.

假如该字符串中的第一个非空格字符不是一个有效整数字符或字符串为空或字符串仅包含空白字符时, 则函数不需要进行转换.

在任何情况下, 若函数不能进行有效的转换时, 请返回 0.

说明:

假设我们的环境只能存储 32 位大小的有符号整数, 那么其数值范围为 [−2^31, 2^31 − 1].
如果数值超过这个范围, 请返回 INT_MAX 或 INT_MIN.

示例 1:

输入: "42"
输出: 42

示例 2:

输入: "   -42"
输出: -42
解释: 第一个非空白字符为 '-', 它是一个负号.
     我们尽可能将负号与后面所有连续出现的数字组合起来, 最后得到 -42.

示例 3:

输入: "4193 with words"
输出: 4193
解释: 转换截止于数字 '3', 因为它的下一个字符不为数字.

示例 4:

输入: "words and 987"
输出: 0
解释: 第一个非空字符是 'w', 但它不是数字或正、负号, 因此无法执行有效的转换.

示例 5:

输入: "-91283472332"
输出: -2147483648
解释: 数字 "-91283472332" 超过 32 位有符号整数范围, 因此返回 INT_MIN.
*/

/*
首先, 传入字符串如果为空, 返回 0.
接下来我们看字符串的前面有没有空格, 如果有, 我们需要将空格都删掉;
定义一个 curIdx 表示当前检测到的字符, 如果 str[curIdx] 为空则不断向后移动 curIdx, 直到 curIdx 指向一个不为空的字符;
这个过程中如果 curIdx 到达了字符串末尾, 直接返回 0.
下面需要检查的是符号, 如果是正号直接 curIdx++, 如果是负号还需要将 sign 置为 -1;
接下来遍历的是有效的数位部分:
如果 str[curIdx] 不是 '0' ~ '9', 马上结束循环并返回 res;
否则我们得到该位数字, 在这里需要注意判断溢出的时机, 应该是在获取到 res 的最后一位之前:
如果 res 已经大于了 INT_MAX / 10, 说明此时的 res 一定溢出;
如果 res 等于 INT_MAX / 10, 则最后一位大于 INT_MAX % 10 时一定溢出;
同样的, 如果 res 小于 INT_MIN / 10, res 一定溢出;
res 等于 INT_MAX / 10, 则最后一位大于 -(INT_MIN % 10) 时一定溢出, 即个位的 digit 更大;
如果都不溢出, 转换出的 res 的符号位通过 sign * digit 来保证.
*/

#include <string>

class Solution {
public:
    int myAtoi(std::string str) {
        if (str == "") {
            return 0;
        }
        int strLens = str.size();
        int curIdx = 0;
        while (curIdx < strLens && str[curIdx] == ' ') {
            curIdx++;
        }
        if (curIdx == strLens) {
            return 0;
        }

        int sign = 1;
        if (str[curIdx] == '+') {
            curIdx++;
        }
        else if (str[curIdx] == '-') {
            curIdx++;
            sign = -1;
        }

        int res = 0;
        while (curIdx < strLens && str[curIdx] >= '0' && str[curIdx] <= '9') {
            int digit = str[curIdx] - '0';
            if (res > INT_MAX / 10 || (res == INT_MAX / 10 && digit > INT_MAX % 10)) {
                return INT_MAX;
            }
            if (res < INT_MIN / 10 || (res == INT_MIN / 10 && digit > -(INT_MIN % 10))) {
                return INT_MIN;
            }
            
            res = res * 10 + sign * digit;
            curIdx++;
        }
        return res;
    }
};