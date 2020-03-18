/*
LeetCode 0007. 整数反转

给出一个 32 位的有符号整数, 你需要将这个整数中每位上的数字进行反转.

示例 1:
输入: 123
输出: 321
 
示例 2:
输入: -123
输出: -321

示例 3:
输入: 120
输出: 21

注意:
假设我们的环境只能存储得下 32 位的有符号整数, 则其数值范围为 [−2^31, 2^31 − 1].
如果反转后整数溢出那么就返回 0.
*/

/*
整数翻转需要注意一个问题, 就是翻转之后可能产生的溢出.
为了确保翻转后的数能够被完整保存, 我们先用一个 long 类型变量存储翻转后的值.
然后利用取余不断取出 x 的个位数, 将 newNum * 10 后加上该 digit.
最后我们将 long 类型的 newNum 转换为 int 类型, 如果转换出来的值等于 newNum, 说明没有溢出.
*/

class Solution {
public:
    int reverse(int x) {
        long newNum = 0;
        while (x != 0) {
            newNum = newNum * 10 + x % 10;
            x /= 10;
        }
        return static_cast<int>(newNum) == newNum ? newNum : 0;
    }
};