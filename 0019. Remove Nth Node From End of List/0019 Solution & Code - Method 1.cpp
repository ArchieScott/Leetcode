/*
LeetCode 0019. 删除链表的倒数第 N 个结点

给定一个链表, 删除链表的倒数第 n 个节点, 并且返回链表的头结点.

示例:
给定一个链表: 1->2->3->4->5, 和 n = 2.
当删除了倒数第二个节点后, 链表变为 1->2->3->5.
给定的 n 保证是有效的.
*/

/*
这一类的链表题有一个统一的套路, 即加入头结点, 然后用头结点指向原先的 head 结点.
然后我们使用两个指针都先指向新的头结点, 第一个指针先走 n 步, 然后两个指针一起走, 当指针 first 的 next 为 nullptr 时,
如果 n 仍然大于 0, 说明原链表的结点数小于 n, 直接返回 nullptr;
否则会因为条件 n = 0 成立而结束循环, 此时指针 second 开始从新头结点移动, 当 first->next == nullptr 时,
second->next 正好指向需要删除的结点, 将 second 与 second->next->next 连接起来, 返回 resHead->next 即为答案.
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (!head || n < 1) {
            return head;
        }
        ListNode resNode(0);
        resNode.next = head;
        ListNode* first = &resNode;
        ListNode* second = &resNode;
        while(first->next && n--) {
            first = first->next;
        }
        if (n > 0) {
            return nullptr;
        }
        while (first->next) {
            first = first->next;
            second = second->next;
        }
        second->next = second->next->next;
        return resNode.next;
    }
};