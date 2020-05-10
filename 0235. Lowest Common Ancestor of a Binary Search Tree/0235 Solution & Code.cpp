/*
LeetCode 0235. 二叉搜索树的最近公共祖先

给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先. 
对于有根树 T 的两个结点 p, q, 最近公共祖先表示为一个结点 x, 满足 x 是 p, q 的祖先且 x 的深度尽可能大
一个节点也可以是它自己的祖先.

示例 1:
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
输出: 6 
解释: 节点 2 和节点 8 的最近公共祖先是 6. 

示例 2:
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
输出: 2
解释: 节点 2 和节点 4 的最近公共祖先是 2, 因为根据定义最近公共祖先节点可以为节点本身. 
 
说明:
所有节点的值都是唯一的. 
p, q 为不同节点且均存在于给定的二叉搜索树中. 
*/

/*
这道题可以充分利用 BST 的性质, 对于树中的某个结点来说, 如果待查找的两个结点 p 和 q 的值分别位于该结点的左右子树上时, 这个结点就是 p 和 q 的最近公共祖先.
那么我们可以计算当前结点 curr->val 与 p->val 和 q->val 的差值的乘积, 如果该乘积大于 0, 说明 p 和 q 一定位于当前结点的同一条子树上,
如果 curr->val 大于 p->val, 我们就需要将 curr 向左移动, 反之则向右移动,
当当前结点 curr->val 与 p->val 和 q->val 的差值的乘积小于等于 0 时, 迭代结束,
此时有可能 curr 就是 p 或者 q, 或者 curr 在 p 和 q 的中间.
*/


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* curr = root;
        while ((curr->val - p->val) * (curr->val - q->val) > 0) {
            curr = curr->val >= p->val ? curr->left : curr->right;
        }
        return curr;
    }
};