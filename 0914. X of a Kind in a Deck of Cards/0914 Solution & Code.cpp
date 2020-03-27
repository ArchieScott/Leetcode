/*
LeetCode 0914. 卡牌分组

给定一副牌, 每张牌上都写着一个整数.
此时, 你需要选定一个数字 X, 使我们可以将整副牌按下述规则分成 1 组或更多组: 
每组都有 X 张牌.
组内所有的牌上都写着相同的整数.
仅当你可选的 X >= 2 时返回 true.

示例 1: 
输入: [1,2,3,4,4,3,2,1]
输出: true
解释: 可行的分组是 [1,1], [2,2], [3,3], [4,4]

示例 2: 
输入: [1,1,1,2,2,2,3,3]
输出: false
解释: 没有满足要求的分组.

示例 3: 
输入: [1]
输出: false
解释: 没有满足要求的分组.

示例 4: 
输入: [1,1]
输出: true
解释: 可行的分组是 [1,1]

示例 5: 
输入: [1,1,2,2,2,2]
输出: true
解释: 可行的分组是 [1,1], [2,2], [2,2]

提示: 
1 <= deck.length <= 10000
0 <= deck[i] < 10000
*/

/*
首先弄清题意, 题目让我们分出 N 组卡牌, 每一组数量相同, 点数相同, 并且数量要大于等于 2.
首先统计所有不同点数卡牌的数量, 并且保存在 hashtable 中.
对于两组数量不同的卡牌来说, [1, 1, 2, 2, 2, 2] 能够成功分组, 因为 2 和 4 的最大公约数为 2,
也就是说, 只要找到所有统计数的最大公约数, 我么就能够按照最大公约数来分组, 因为每一组大于最大公约数的数都可以整除这个最大公约数.
遍历 hashtable 找到不同点数卡牌张数的最大公约数, 如果出现两个数的最大公约数为 1, 直接返回 false.
*/

#include <vector>
#include <unordered_map>
#include <numeric>

class Solution {
public:
    bool hasGroupsSizeX(std::vector<int>& deck) {
        std::unordered_map<int, int> deckNum;
        for (auto item : deck) {
            deckNum[item]++;
        }
        // 任何数和 0 的最大公约数都为那个数
        int res = 0;
        for (auto item : deckNum) {
            res = std::gcd(res, item.second);
            if (res == 1) {
                return false;
            }
        }
        return res >= 2;
    }
};