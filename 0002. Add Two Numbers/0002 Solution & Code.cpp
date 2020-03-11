/*
给出两个非空的链表用来表示两个非负的整数.
其中, 它们各自的位数是按照逆序的方式存储的, 并且它们的每个节点只能存储一位数字.

如果, 我们将这两个数相加起来, 则会返回一个新的链表来表示它们的和.

您可以假设除了数字 0 之外, 这两个数都不会以 0 开头.

示例:

输入: (2 -> 4 -> 3) + (5 -> 6 -> 4)
输出: 7 -> 0 -> 8
原因: 342 + 465 = 807
*/

/*
因为链表表示的数字本身已经是逆序的了, 我们可以从两个链表的表头开始依次相加, 将结果存在新链表结点中.
因为每个结点都只能保存一位数字, 因此我们需要考虑进位的问题, 用一个变量 carryBit 来表示进位,
所以每个结点值可以表示为 l1->val + l2->val + carryBit
如果结点不存在, 我们需要将该结点的值用 0 表示
除此之外, 还要考虑到进位导致的多出一位的情况, 因此在 while 循环中需要 while(l1 || l2 || carryBit), 只有当 l1 l2 均为空且没有进位才算计算完成
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carryBit = 0;
        int sum = 0;
        // 结果链表的头结点
        ListNode* resHead = new ListNode(0);
        // 结果链表用于计算 sum 的指针
        ListNode* currNode = resHead;
        while(l1 || l2 || carryBit){
            sum = (l1 == nullptr ? 0 : l1->val) + (l2 == nullptr ? 0 : l2->val) + carryBit;
            l1 = l1 == nullptr ? nullptr : l1->next;
            l2 = l2 == nullptr ? nullptr : l2->next;
            currNode->next = new ListNode(sum % 10);
            carryBit = sum / 10;
            currNode = currNode->next;
        }
        return resHead->next;
    }
};