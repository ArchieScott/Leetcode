/*
LeetCode 0236. 二叉树的最近公共祖先

给定一个二叉树, 找到该树中两个指定节点的最近公共祖先. 
对于有根树 T 的两个结点 p, q, 最近公共祖先表示为一个结点 x, 满足 x 是 p, q 的祖先且 x 的深度尽可能大.
一个节点也可以是它自己的祖先.

示例 1:
输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出: 3
解释: 节点 5 和节点 1 的最近公共祖先是节点 3. 

示例 2:
输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出: 5
解释: 节点 5 和节点 4 的最近公共祖先是节点 5. 因为根据定义最近公共祖先节点可以为节点本身. 

说明:
所有节点的值都是唯一的. 
p, q 为不同节点且均存在于给定的二叉树中. 
*/

/*
这道题用递归做应该考虑后序遍历的顺序, 即先查找左右子树, 分别判断查找结点是否在该子树中,
对于递归函数 lowestCommonAncestor 来说, 如果查找结点不在该子树中, 返回 nullptr; 如果在该子树中, 返回对应的 p 或者 q;
对于既不是 nullptr 也不是 p 或者 q 的, 就继续递归查找;
当找到 p 和 q 分别位于 root 的左右子树中时, 也就是 leftNode 和 rightNode 都不为 nullptr, 返回 root;
否则就返回那个非空的结点, 也就是查找到的 leftNode/rightNode, 如果都为 nullptr, 也就返回 nullptr
此时相当于已经找到了公共父结点, 接下来就需要退出递归, 该父结点的兄弟结点处的递归返回一定为 nullptr, 那么这个查找到的父结点可以一直返回出去.
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
        if (!root || root == p || root == q) {
            return root;
        }
        TreeNode* leftNode = lowestCommonAncestor(root->left, p, q);
        TreeNode* rightNode = lowestCommonAncestor(root->right, p, q);

        if (leftNode && rightNode) {
            return root;
        }
        return leftNode != nullptr ? leftNode : rightNode;
    }
};