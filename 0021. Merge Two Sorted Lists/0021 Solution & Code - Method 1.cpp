/*
LeetCode 0021. 合并两个有序链表
将两个升序链表合并为一个新的升序链表并返回, 新链表是通过拼接给定的两个链表的所有节点组成的.

示例:
输入: 1->2->4, 1->3->4
输出: 1->1->2->3->4->4
*/

/*
方法一: 递归
递归终止条件: l1 或者 l2 为空
返回值: 每一层调用后排序好的链表表头
递归处理: 如果 l1->val < l2->val, 那么 l1->next 应该指向 l1->next 与 l2 合并后的链表,
        那么就能推导出 l1->next = mergeTwoLists(l1->next, l2)
这样的时间复杂度为 O(N), 额外空间复杂度为 O(N)
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(!l1)
            return l2;
        if(!l2)
            return l1;
        if(l1->val < l2->val){
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }else{
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};