/*
LeetCode 0202. 快乐数
编写一个算法来判断一个数 n 是不是快乐数.
快乐数定义为: 
对于一个正整数, 每一次将该数替换为它每个位置上的数字的平方和, 然后重复这个过程直到这个数变为 1,
这个过程也可能是无限循环但始终变不到 1. 如果可以变为 1, 那么这个数就是快乐数.
如果 n 是快乐数就返回 True, 不是则返回 False.

示例: 
输入: 19
输出: true
解释:
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
*/

/*
方法一: unordered_set
首先我们可以发现这样的规律: 一位数最大和为 81, 两位数最大和为 162, 三位数最大和为 243, 四位数最大和为 324,
也就是说从三位数开始, 每次计算平方和结果的位数都会减少, 这也说明了最终只可能有两种结果: 得到 1 或者得到循环.
代码中我们首先写出计算平方和的函数, 然后计算平方和, 首先看它是否为 1, 如果不是, 看它是否在哈希集合中, 
如果不在, 我们就将它加入哈希集合并计算下一个数,如果在, 说明遇到了循环, 返回 false.
*/

#include <unordered_set>

class Solution {
public:
    bool isHappy(int n) {
        std::unordered_set<int> numSet;
        while (n != 1) {
            int tempRes = bitSquareSum(n);
            if (tempRes == 1)
                return true;
            else {
                if (numSet.find(tempRes) == numSet.end()) {
                    numSet.insert(tempRes);
                    n = tempRes;
                }
                else
                    return false;
            }
        }
        return true;
    }

    int bitSquareSum(int n) {
        int sum = 0;
        while (n) {
            int bit = n % 10;
            sum += bit * bit;
            n /= 10;
        }
        return sum;
    }
};