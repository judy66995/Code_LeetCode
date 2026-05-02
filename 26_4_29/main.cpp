#include <iostream>
#include <unordered_map>
#include <windows.h>

using namespace std;

// 节点结构：保存 key、value、使用频率 freq、前后指针
struct Node {
    int key;// 键
    int value;// 存储的值
    int freq;// 使用频率
    Node* prev;// 前一个节点
    Node* next;// 后一个节点

    Node(int k, int v) : key(k), value(v), freq(1), prev(nullptr), next(nullptr) {}// 构造函数，初始化 key、value 和 freq（初始为 1）
};

// 双向链表：管理同一频率的所有节点
struct DLinkedList {
    Node* head;// 链表头（虚拟节点）
    Node* tail;// 链表尾（虚拟节点）

    DLinkedList() {
        head = new Node(-1, -1);// 初始化头尾虚拟节点
        tail = new Node(-1, -1);// 初始化头尾虚拟节点
        head->next = tail;
        tail->prev = head;
    }

    // 添加到头部（表示最近使用）
    void addToHead(Node* node) {
        node->next = head->next;// 插入节点到头部
        node->prev = head;// 插入节点的前一个节点指向虚拟节点
        head->next->prev = node;// 原头部节点的前一个节点指向新节点
        head->next = node;// 虚拟节点的下一个节点指向新节点
    }

    // 删除任意节点
    void removeNode(Node* node) {
        node->prev->next = node->next;// 原节点的前一个节点的下一个节点指向原节点的下一个节点
        node->next->prev = node->prev;// 原节点的下一个节点的前一个节点指向原节点的前一个节点
    }

    // 删除尾部（最久未使用）
    Node* removeTail() {
        Node* res = tail->prev;// 获取尾部节点（最久未使用的节点）
        removeNode(res);// 删除该节点
        return res;// 返回被删除的节点
    }

    // 判断链表是否为空
    bool isEmpty() {
        return head->next == tail;
    }
};

// LFU 缓存类
class LFUCache {
private:
    int capacity;       // 最大容量
    int size;           // 当前元素数量
    int minFreq;        // 当前最小频率
    unordered_map<int, Node*> keyMap;    // key -> 节点
    unordered_map<int, DLinkedList*> freqMap; // 频率 -> 链表

    // 核心：更新节点频率
    void updateFreq(Node* node) {
        int oldFreq = node->freq;// 获取旧频率
        freqMap[oldFreq]->removeNode(node);// 从旧频率链表中删除节点

        // 如果旧频率空了，且是最小频率，最小频率+1
        if (oldFreq == minFreq && freqMap[oldFreq]->isEmpty()) {// 如果旧频率是当前最小频率，并且该频率的链表已经空了
            minFreq++;// 最小频率增加
        }

        // 频率+1，加入新频率链表
        node->freq++;// 节点频率增加
        int newFreq = node->freq;// 获取新频率

        if (freqMap.find(newFreq) == freqMap.end()) {// 如果新频率链表不存在，创建一个
            freqMap[newFreq] = new DLinkedList();// 创建新频率的链表
        }
        freqMap[newFreq]->addToHead(node);// 将节点添加到新频率链表的头部（表示最近使用）
    }

public:
    LFUCache(int cap) {// 构造函数，初始化容量、大小和最小频率
        capacity = cap;
        size = 0;
        minFreq = 0;
    }

    // 获取 key 对应的值
    int get(int key) {
        if (keyMap.find(key) == keyMap.end()) {// 如果 key 不存在，返回 -1
            return -1;
        }
        Node* node = keyMap[key];// 获取节点
        updateFreq(node);// 更新节点频率
        return node->value;// 返回节点值
    }

    // 插入/更新 key-value
    void put(int key, int value) {
        if (capacity == 0) return;

        // 已存在：更新值 + 频率
        if (keyMap.find(key) != keyMap.end()) {// 如果 key 已存在，更新值并更新频率
            Node* node = keyMap[key];// 获取节点
            node->value = value;// 更新节点值
            updateFreq(node);// 更新节点频率
            return;
        }

        // 已满：删除最少使用的
        if (size == capacity) {
            DLinkedList* minList = freqMap[minFreq];// 获取最小频率的链表
            Node* delNode = minList->removeTail();// 删除最久未使用的节点
            keyMap.erase(delNode->key);// 从 keyMap 中删除该节点
            delete delNode;// 释放节点内存
            size--;// 当前元素数量减少
        }

        // 新增节点
        Node* newNode = new Node(key, value);// 创建新节点
        keyMap[key] = newNode;// 将新节点添加到 keyMap 中

        if (freqMap.find(1) == freqMap.end()) {// 如果频率为 1 的链表不存在，创建一个
            freqMap[1] = new DLinkedList();// 创建频率为 1 的链表
        }
        freqMap[1]->addToHead(newNode);// 将新节点添加到频率为 1 的链表的头部（表示最近使用）
        minFreq = 1;// 新节点的频率为 1，所以最小频率更新为 1
        size++;
    }
};


int main() {
    SetConsoleOutputCP(CP_UTF8); // 设置控制台输出编码为 UTF-8

    cout << "=== LFU 缓存测试开始 ===" << endl;

    // 创建容量为 2 的 LFU 缓存
    LFUCache* cache = new LFUCache(2);

    cache->put(1, 1);// 插入 (1, 1)
    cache->put(2, 2);// 插入 (2, 2)

    cout << "get(1) = " << cache->get(1) << endl; // 预期 1

    cache->put(3, 3); // 缓存满，淘汰使用最少的 2

    cout << "get(2) = " << cache->get(2) << endl; // 预期 -1
    cout << "get(3) = " << cache->get(3) << endl; // 预期 3

    cache->put(4, 4); // 淘汰 1

    cout << "get(1) = " << cache->get(1) << endl; // 预期 -1
    cout << "get(3) = " << cache->get(3) << endl; // 预期 3
    cout << "get(4) = " << cache->get(4) << endl; // 预期 4

    cout << "=== 测试结束 ===" << endl;

    delete cache;
    return 0;
}