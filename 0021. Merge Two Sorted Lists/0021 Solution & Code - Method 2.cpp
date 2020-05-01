/*
LeetCode 0021. 合并两个有序链表
将两个升序链表合并为一个新的升序链表并返回, 新链表是通过拼接给定的两个链表的所有节点组成的.

示例:
输入: 1->2->4, 1->3->4
输出: 1->1->2->3->4->4
*/

/*
方法二: 迭代
我们先设置一个 head 结点, 当 l1 和 l2 都不是空链表时, 判断 l1 和 l2 哪一个链表的头节点的值更小,
将较小值的节点添加到结果里, 当一个节点被添加到结果里之后, 将对应链表中的节点向后移一位.
这样的时间复杂度为 O(N), 额外空间复杂度为 O(1)
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* head = new ListNode(-1);
        ListNode* cur = head;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                cur->next = l1;
                l1 = l1->next;
            }
            else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        cur->next = l1 ? l1 : l2;
        return head->next;
    }
};