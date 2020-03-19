/*
LeetCode 0012. 整数转罗马数字

罗马数字包含以下七种字符: I, V, X, L, C, D 和 M.
字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
例如, 罗马数字 2 写做 II, 即为两个并列的 1.
12 写做 XII, 即为 X + II. 
27 写做 XXVII, 即为 XX + V + II.

通常情况下, 罗马数字中小的数字在大的数字的右边. 
但也存在特例, 例如 4 不写做 IIII, 而是 IV. 数字 1 在数字 5 的左边, 所表示的数等于大数 5 减小数 1 得到的数值 4.
同样地, 数字 9 表示为 IX. 这个特殊的规则只适用于以下六种情况: 
I 可以放在 V (5) 和 X (10) 的左边, 来表示 4 和 9.
X 可以放在 L (50) 和 C (100) 的左边, 来表示 40 和 90. 
C 可以放在 D (500) 和 M (1000) 的左边, 来表示 400 和 900.
给定一个整数, 将其转为罗马数字. 输入确保在 1 到 3999 的范围内.

示例 1:
输入: 3
输出: "III"

示例 2:
输入: 4
输出: "IV"

示例 3:
输入: 9
输出: "IX"

示例 4:
输入: 58
输出: "LVIII"
解释: L = 50, V = 5, III = 3.

示例 5:
输入: 1994
输出: "MCMXCIV"
解释: M = 1000, CM = 900, XC = 90, IV = 4.
*/

/*
举个例子, 表示 1000 我们不会使用 DD 而是使用 M, 即表示更大的数我们会尽量使用更大的罗马数字, 因此这道题可以使用贪心来求解.
首先将从 1000 ~ 1 一共 13 个有特殊表示方法的阿拉伯数字和罗马数字按照从大到小的顺序分别存入两个数组中 (或者直接使用有序的 map),
然后遍历整个数组或者 map, 每次都尽可能地选择最大的罗马数字单位进行表示, 当最后一个数字 1 遍历完之后, 返回的字符串即为所求解.
*/

#include <string>
#include <map>

class Solution {
public:
    std::string intToRoman(int num) {
        std::string res;
        // 注意 map 类实例化时候的 std::greater<int>
        std::map<int, std::string, std::greater<int>> dict{
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
            {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
            {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"},
        };
        // std::vector<int> digits{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        // std::vector<std::string> romans{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

        for (auto& item : dict) {
            while (num >= item.first) {
                num -= item.first;
                res.append(item.second);
            }
        }
        return res;
    }
};