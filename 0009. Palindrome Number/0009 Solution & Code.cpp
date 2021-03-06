/*
LeetCode 0009. 回文数

判断一个整数是否是回文数, 回文数是指正序和倒序读都是一样的整数.

示例 1:
输入: 121
输出: true

示例 2:
输入: -121
输出: false
解释: 从左向右读, 为 -121. 从右向左读, 为 121-. 因此它不是一个回文数.

示例 3:
输入: 10
输出: false
解释: 从右向左读, 为 01. 因此它不是一个回文数.
*/

/*
一个比较容易想到的方法是将整数转换成字符串, 然后比较两个字符串是否相等.
另一个是将整个整数反转, 但是可能会有溢出的情况, 虽然回文数是不可能溢出的.
这里我们只翻转整个数的一半: 
如果数字位数为偶数, 翻转的后半部分数如果等于前半部分数, 该数为回文数;
如果数字位数为奇数, 翻转的后半部分数大于前半部分数时停止, 如果该数为回文数, reverseNum / 10 == x;
剩下的需要处理一些特殊情况:
负数一定不是回文数;
10 的倍数除了 0 一定不会是回文数;
*/

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0 || (x != 0 && x % 10 == 0)) {
            return false;
        }
        int reverseNum = 0;
        while (reverseNum < x) {
            reverseNum = reverseNum * 10 + x % 10;
            x /= 10;
        }
        if ((reverseNum == x) || (reverseNum/10 == x)) {
            return true;
        }
        return false;
    }
};