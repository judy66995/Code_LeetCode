#include <iostream>
#include <unordered_map>// 引入哈希表头文件
using namespace std;

// 双向链表节点
struct DLinkedNode {
    int key, value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value) : key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    // 哈希表：key:int  , value:DLinkedNode*
    unordered_map<int, DLinkedNode*> cache; // key -> 指向双向链表的节点
    DLinkedNode* head; // 虚拟头结点（最近使用）
    DLinkedNode* tail; // 虚拟尾结点（最久未使用）
    int size;          // 当前缓存大小
    int capacity;      // 缓存容量

public:
    LRUCache(int capacity) {// 构造函数，初始化容量和链表
        this->capacity = capacity;
        this->size = 0;
        // 初始化虚拟头尾节点，方便操作边界节点
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (!cache.count(key)) {
            // key不存在，返回-1
            return -1;
        }
        // key存在，取出节点，移到头部（标记为最近使用）
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value) {
        if (cache.count(key)) {
            // key已存在，更新value并移到头部
            DLinkedNode* node = cache[key];//拿着key,去哈希表cache里，快速查到这个key对应的双向链表节点，把这个节点的地址赋值给node指针。
            node->value = value;
            moveToHead(node);
        } else {
            // key不存在，创建新节点
            DLinkedNode* newNode = new DLinkedNode(key, value);
            cache[key] = newNode;
            addToHead(newNode);
            size++;
            if (size > capacity) {
                // 超出容量，删除尾部节点（最久未使用）
                DLinkedNode* tailNode = removeTail();//从链表中删除尾部节点，并返回这个节点的地址
                cache.erase(tailNode->key);//从哈希表中删除这个节点对应的key
                delete tailNode;
                size--;
            }
        }
    }

private:
    // 把节点加到头部（虚拟头结点之后）
    void addToHead(DLinkedNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    // 从链表中移除节点
    void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;//把node的前一个节点(node->prev)的next指向node的下一个节点
        node->next->prev = node->prev;//把node的下一个节点(node->next)的prev指向node的前一个节点
    }

    // 把节点移到头部（先移除再添加）
    void moveToHead(DLinkedNode* node) {
        removeNode(node);//先把node从链表中移除
        addToHead(node);//再把node加到头部
    }

    // 删除尾部节点（虚拟尾结点之前）
    DLinkedNode* removeTail() {
        DLinkedNode* node = tail->prev;
        removeNode(node);
        return node;
    }
};


int main() {
    // 创建容量为 2 的 LRU 缓存
    LRUCache* lru = new LRUCache(2);

    lru->put(1, 1);    // 缓存是 {1=1}
    lru->put(2, 2);    // 缓存是 {1=1, 2=2}
    cout << lru->get(1) << endl;  // 返回 1
    lru->put(3, 3);    // 淘汰 key 2，缓存是 {1=1, 3=3}
    cout << lru->get(2) << endl;  // 返回 -1（未找到）
    lru->put(4, 4);    // 淘汰 key 1，缓存是 {3=3, 4=4}
    cout << lru->get(1) << endl;  // 返回 -1（未找到）
    cout << lru->get(3) << endl;  // 返回 3
    cout << lru->get(4) << endl;  // 返回 4

    delete lru;
    return 0;
}