/*
LeetCode 0019. 删除链表的倒数第 N 个结点

给定一个链表, 删除链表的倒数第 n 个节点, 并且返回链表的头结点.

示例:
给定一个链表: 1->2->3->4->5, 和 n = 2.
当删除了倒数第二个节点后, 链表变为 1->2->3->5.
给定的 n 保证是有效的.
*/

/*
在一次遍历中使用一个 hashmap 保存该链表中的所有结点. key 表示当前结点的 index, value 表示当前结点的指针.
此处需要额外插入一个头结点用于处理删除第一个结点的情况, 新插入的头结点 index = 0,
那么原链表中的结点编号分别对应着 1 ~ nodeNum, 被删除的倒数第 n 个结点的前一个结点索引为 nodeNum - n;
所以我们只需要将 nodeMap[nodeNum - n]->next 指向 nodeMap[nodeNum - n + 2] 即可;
如果删除的是最后一个结点也无需特别处理, std::unordered_map 的 operator[] 在键不存在时会插入一个新的 kv 对,
并将这个新插入的值进行值初始化, 即 nullptr.
*/

#include <unordered_map>

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
        std::unordered_map<int, ListNode*> nodeMap;
        // 加入头结点是为了便于删除第一个结点
        ListNode resHead(0);
        resHead.next = head;
        ListNode* curNode = &resHead;
        int idx = 0;
        while (curNode) {
            nodeMap[idx++] = curNode;
            curNode = curNode->next;
        }
        int nodeNum = nodeMap.size() - 1;
        if (nodeNum < n) {
            return nullptr;
        }
        else {
            nodeMap[nodeNum - n]->next = nodeMap[nodeNum - n + 2];
        }
        return resHead.next;
    }
};