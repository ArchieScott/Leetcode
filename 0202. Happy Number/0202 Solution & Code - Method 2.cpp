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
方法二: 快慢指针
使用快慢指针找出循环, 如果循环存在, 快指针一定会追上慢指针, 如果循环不存在, 最后快慢指针也会相等并且都指向 1.
*/

class Solution {
public:
    bool isHappy(int n) {
        int slow = n, fast = n;
        do {
            // 慢指针每次计算一个数, 快指针每次计算两个数, 看它们相等的时候是否为 1
            slow = bitSquareSum(slow);
            fast = bitSquareSum(fast);
            fast = bitSquareSum(fast);
        } while(slow != fast);
        
        return slow == 1;
    }

    int bitSquareSum(int n) {
        int sum = 0;
        while(n > 0)
        {
            int bit = n % 10;
            sum += bit * bit;
            n = n / 10;
        }
        return sum;
    }
};