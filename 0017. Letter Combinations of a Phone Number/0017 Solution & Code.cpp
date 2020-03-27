/*
LeetCode 0017. 电话号码的字母组合

给定一个仅包含数字 2-9 的字符串, 返回所有它能表示的字母组合.
数字到字母的映射与电话按键相同, 注意 1 不对应任何字母.

示例:
输入: "23"
输出: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
说明:
尽管上面的答案是按字典序排列的, 但是你可以任意选择答案输出的顺序.
*/

/*
这道题要求输出所有可能的排列字符序列, 考虑用回溯. 回溯是通过穷举所有可能的情况找到所有解的算法.
如果一个候选解不是可行解, 回溯算法会舍弃它, 并且回到之前的步骤进行修改, 重新尝试其他的路径.
先将每个按键对应的字符保存在 hashtable 中用于查询传入数字对应的字符串;
结果数组 res 保存为类变量, 递归函数 process 参数 idx 表示当前尝试到 digits 的第几个数字, str 表示当前已经组合的字符串;
当 idx == digits.size(), 说明尝试到了最后一个数字, 将 str 放入结果数组;
否则就获取该数字对应的字符串, 对于该字符串中的每一个字符都尝试 str += c, 然后 idx++ 尝试下一个数字;
这里有一个易错的地方是在 process 完成后还需要将刚刚 append 的字符 c pop_back 才能进行下一次的尝试.
*/

#include <vector>
#include <string>
#include <unordered_map>

class Solution {
public:
    std::vector<std::string> letterCombinations(std::string digits) {
        std::unordered_map<char, std::string> button{
            {'2', "abc"}, {'3', "def"}, {'4', "ghi"},
            {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"},
            {'8', "tuv"}, {'9', "wxyz"}
        };
        if (digits.size() >= 1) {
            process(digits, 0, button, "");
        }
        return res;
    }

    void process(std::string& digits, int idx, std::unordered_map<char, std::string>& button, std::string str) {
        if (idx == digits.size()) {
            res.push_back(str);
            return;
        }
        std::string numStr = button[digits[idx]];
        for (auto& c : numStr) {
            str += c;
            process(digits, idx + 1, button, str);
            str.pop_back();
        }
    }
private:
    std::vector<std::string> res;
};