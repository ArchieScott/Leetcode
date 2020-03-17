/*
将一个给定字符串根据给定的行数, 以从上往下从左到右进行 Z 字形排列.
比如输入字符串为 "LEETCODEISHIRING", 行数为 3 时, 排列如下:
L   C   I   R
E T O E S I I G
E   D   H   N
之后, 你的输出需要从左往右逐行读取, 产生出一个新的字符串, 比如: "LCIRETOESIIGEDHN".
请你实现这个将字符串进行指定行数变换的函数.
string convert(string s, int numRows);

示例 1:
输入: s = "LEETCODEISHIRING", numRows = 3
输出: "LCIRETOESIIGEDHN"

示例 2:
输入: s = "LEETCODEISHIRING", numRows = 4
输出: "LDREOEIIECIHNTSG"
解释:
L     D     R
E   O E   I I
E C   I H   N
T     S     G
*/

/*
这道题我们可以从新字符串下标的规律入手, 每一个竖列的字符个数为 numRows, 每两个竖列之间的字符个数为 numRows - 2,
所以如果不看斜着排列的字符, 两个竖列之间对应的字符下标的差值应该为 2 * numRows - 2,
但是如果加入了斜着排列的字符, 这个规律只适用于首行和末行, 而中间的行满足 step 与 interval - step 的交叉排列,
我们只看字符拐角的位置就不难发现 step 的规律, 用上面的示例来举例:
E 和 C 相差 2, E 和 O 相差 4, 所以斜字符的一端 step = 2 * row, 另一端 step = interval - step, 
最后我们修改下标时需要区分 interval 和 step, 当一行字符遍历完成后再 ++row.
*/

#include <string>

class Solution {
public:
	std::string convert(std::string s, int numRows) {
        if (numRows == 1) {
            return s;
        }
		std::string res;
		int row = 0;
		int interval = 2 * numRows - 2;
		while (row < numRows) {
			int step = 2 * row;
			for (int i = row; i < s.size(); ) {
				res.push_back(s[i]);
				step = interval - step;
				i += (row == 0 || row == numRows - 1) ? interval : step;
			}
			++row;
		}
		return res;
	}
};