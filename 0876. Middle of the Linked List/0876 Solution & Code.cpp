/*
给定一个带有头结点 head 的非空单链表, 返回链表的中间结点.
如果有两个中间结点, 则返回第二个中间结点.

示例 1: 
输入: [1,2,3,4,5]
输出: 此列表中的结点 3 (序列化形式: [3,4,5])
返回的结点值为 3.

示例 2: 
输入: [1,2,3,4,5,6]
输出: 此列表中的结点 4 (序列化形式: [4,5,6])
由于该列表有两个中间结点, 值分别为 3 和 4, 我们返回第二个结点.
*/

/*
这道题有两种常规解法:
第一种快慢指针, 每次快指针走两步, 慢指针走一步, 但是这道题表述有误, 应该是不带头结点.
第二种用 vector 记录, 将不能索引的结点变为能随机访问的 vector 元素.
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
};