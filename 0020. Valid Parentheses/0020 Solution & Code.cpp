/*
LeetCode 0020. 有效的括号

给定一个只包括 '(', ')', '{', '}', '[', ']' 的字符串, 判断字符串是否有效. 
有效字符串需满足: 
左括号必须用相同类型的右括号闭合. 
左括号必须以正确的顺序闭合. 
注意空字符串可被认为是有效字符串. 

示例 1:
输入: "()"
输出: true

示例 2:
输入: "()[]{}"
输出: true

示例 3:
输入: "(]"
输出: false

示例 4:
输入: "([)]"
输出: false

示例 5:
输入: "{[]}"
输出: true
*/

/*
遍历字符串, 如果是左括号就入栈并检查下一个字符, 如果是右括号就检查栈顶的左括号能否和该右括号匹配,
是否匹配我们可以将对应的左右括号用一个 hashmap 的 key-value 保存起来;
如果不匹配直接返回 false, 否则将栈顶的左括号出栈, 并检查下一个字符;
当整个字符串检查完毕, 如果能够全部成功匹配, 栈应该为空, 否则肯定有未能成功匹配的括号, 返回 false;
*/

#include <string>
#include <stack>
#include <unordered_map>

class Solution {
public:
    bool isValid(std::string s) {
        if (s.size() % 2 != 0) {
            return false;
        }
        std::stack<char> charSt;
        std::unordered_map<char, char> match{
            {'{', '}'}, {'[', ']'}, {'(', ')'}
        };
        for (auto& c : s) {
            if (c == '(' || c == '{' || c == '[') {
                charSt.push(c);
                continue;
            }
            if (charSt.empty() || c != match[charSt.top()]) {
                return false;
            }
            charSt.pop();
        }
        if (!charSt.empty()) {
            return false;
        }
        return true;
    }
};