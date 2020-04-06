/*
LeetCode 0460. LFU 缓存

设计并实现最不经常使用 (LFU) 缓存的数据结构, 它应该支持以下操作: get 和 put.
get(key) - 如果键存在于缓存中, 则获取键的值, 键的值总是正数, 否则返回 -1.
put(key, value) - 如果键不存在, 请设置或插入值. 当缓存达到其容量时, 它应该在插入新项目之前, 使最不经常使用的项目无效.
                  在此问题中, 当存在两个或更多个键具有相同使用频率时, 最近最少使用的键将被去除.

示例:
LFUCache cache = new LFUCache(2);
cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // 返回 1
cache.put(3, 3);    // 去除 key 2
cache.get(2);       // 返回 -1 (未找到key 2)
cache.get(3);       // 返回 3
cache.put(4, 4);    // 去除 key 1
cache.get(1);       // 返回 -1 (未找到 key 1)
cache.get(3);       // 返回 3
cache.get(4);       // 返回 4
*/

/*
待更新.
*/

class listNode {
public:
    listNode(int key_, int val_, int times_, listNode* up_, listNode* down_)
        : key(key_), value(val_), times(times_), up(up_), down(down_) {}
    int key{0};
    int value{0};
    int times{0};
    listNode* up{nullptr};
    listNode* down{nullptr};
};

class nodeList {
public:
    nodeList(listNode* node) {
        head = node;
        tail = node;
    }

    void addNodeFromHead(listNode* newNode) {
        newNode->down = head;
        head->up = newNode;
        head = newNode;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    void deleteNode(listNode* delNode) {
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        }
        else {
            if (head == delNode) {
                head = delNode->down;
                head->up = nullptr;
            }
            else if (tail == delNode) {
                tail = delNode->up;
                tail->down = nullptr;
            }
            else {
                delNode->up->down = delNode->down;
                delNode->down->up = delNode->up;
            }
        }
        delNode->up = nullptr;
        delNode->down = nullptr;
    }

    listNode* head{nullptr};
    listNode* tail{nullptr};
    nodeList* pre{nullptr};
    nodeList* next{nullptr};
};

class LFUCache {
public:
    LFUCache(int capacity_) {
        capacity = capacity_;
    }
    
    int get(int key) {
        if (capacity == 0) {
            return -1;
        }
        if (records.find(key) == records.end())
            return -1;
        listNode* getNode = records[key];
        nodeList* curNodeList = heads[getNode];
        // 每次操作都要记得修改页面的访问次数
        getNode->times++;
        move(getNode, curNodeList);
        return getNode->value;
    }
    
    void put(int key, int value) {
        if (capacity == 0) {
            return;
        }
        if (records.find(key) != records.end()) {
            listNode* node = records[key];
            node->value = value;
            node->times++;
            nodeList* curNodeList = heads[node];
            move(node, curNodeList);      
        }
        else {
            if (size == capacity) {
                listNode* delNode = headList->tail;
                headList->deleteNode(delNode);
                modifyHeadList(headList);
                records.erase(delNode->key);
                heads.erase(delNode);
                size--;
            }
            listNode* newNode = new listNode(key, value, 1, nullptr, nullptr);
            if (headList == nullptr) {
                headList = new nodeList(newNode);
            }
            else {
                if (headList->head->times == 1) {
                    headList->addNodeFromHead(newNode);
                }
                else {
                    nodeList* newList = new nodeList(newNode);
                    newList->next = headList;
                    headList->pre = newList;
                    headList = newList;
                }
            }
            records[key] = newNode;
            heads[newNode] = headList;
            size++;
        }
    }

private:
    bool modifyHeadList(nodeList* modifyList) {
        if (modifyList->isEmpty()) {
            // 判断是否是 headList
            if (headList == modifyList) {
                headList = modifyList->next;
                // 注意需要对 modifyList 的下一个结点判空
                if (headList != nullptr) {
                    headList->pre = nullptr;
                }
            }
            else {
                modifyList->pre->next = modifyList->next;
                if (modifyList->next != nullptr) {
                    modifyList->next->pre = modifyList->pre;
                }
            }
            return true;
        }
        return false;
    }

    void move(listNode* modifyNode, nodeList* oldNodeList) {
        oldNodeList->deleteNode(modifyNode);
        // 判断删除结点后老链表是否还存在, 用于判断老链表的下一个链表的 pre 指向哪里
        nodeList* preList = modifyHeadList(oldNodeList) ? oldNodeList->pre : oldNodeList;
        nodeList* nextList = oldNodeList->next;
        // nextList 为空, 说明 oldNodeList 已经是原链表的尾部了, 只需要连上 preList 即可
        if (nextList == nullptr) {
            nodeList* newList = new nodeList(modifyNode);
            if (preList != nullptr) {
                preList->next = newList;
            }
            newList->pre = preList;
            if (headList == nullptr) {
                headList = newList;
            }
            heads[modifyNode] = newList;
        }
        else {
            // 下一个 nodeList 的 times 存在
            if (nextList->head->times == modifyNode->times) {
                nextList->addNodeFromHead(modifyNode);
                heads[modifyNode] = nextList;
            }
            else {
                nodeList* newList = new nodeList(modifyNode);
                if (preList != nullptr) {
                    preList->next = newList;
                }
                newList->pre = preList;
                newList->next = nextList;
                nextList->pre = newList;
                if (headList == nextList) {
                    headList = newList;
                }
                heads[modifyNode] = newList;
            }
        }
    }

    int capacity{0};
    int size{0};
    std::unordered_map<int, listNode*> records;
    std::unordered_map<listNode*, nodeList*> heads;
    nodeList* headList{nullptr};
};