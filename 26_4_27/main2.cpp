#include <iostream>
#include <windows.h>

using namespace std;

// 定义链表节点结构体
struct ListNode {
    int val;// 节点值
    ListNode* next;// 指向下一个节点的指针
    ListNode(int x) : val(x), next(nullptr) {}// 构造函数，初始化节点值和指针
};

class MyLinkedList {
private:
    ListNode* head;  // 链表头节点（虚拟哨兵节点，简化边界处理）
    int size;        // 记录链表长度

public:
    // 构造函数：初始化链表
    MyLinkedList() {
        //在内存中新建一个链表节点,数据为0,再把这个节点的地址交给head指针保存。
        head = new ListNode(0); // 虚拟头节点，不存有效数据
        size = 0;//初始时链条是空的
    }

    // 获取第 index 个节点的值
    int get(int index) {
        // 下标越界判断
        if (index < 0 || index >= size) {
            return -1;
        }
        ListNode* cur = head->next; // 从第一个有效节点开始遍历
        for (int i = 0; i < index; i++) {// 循环移动到第 index 个节点
            cur = cur->next;
        }
        return cur->val;
    }

    // 在头部插入节点
    void addAtHead(int val) {
        ListNode* newNode = new ListNode(val);// 创建新节点
        newNode->next = head->next;// 新节点指向当前第一个有效节点
        head->next = newNode;// 虚拟头节点指向新节点
        size++;// 链表长度增加
    }

    // 在尾部插入节点
    void addAtTail(int val) {
        ListNode* newNode = new ListNode(val);// 创建新节点
        ListNode* cur = head;// 从虚拟头节点开始遍历
        // 找到最后一个节点
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = newNode;// 最后一个节点指向新节点
        size++;
    }

    // 在第 index 个节点前插入 val
    void addAtIndex(int index, int val) {
        // index 大于链表长度，不插入
        if (index > size) return;
        // index 小于等于0，插入头部
        if (index <= 0) {
            addAtHead(val);
            return;
        }
        ListNode* newNode = new ListNode(val);// 创建新节点
        ListNode* cur = head;// 从虚拟头节点开始遍历
        // 找到第 index 个节点的前一个节点
        for (int i = 0; i < index; i++) {
            cur = cur->next;
        }
        newNode->next = cur->next;
        cur->next = newNode;
        size++;
    }

    // 删除第 index 个节点
    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) return;
        ListNode* cur = head;
        // 找到第 index 个节点的前一个节点
        for (int i = 0; i < index; i++) {
            cur = cur->next;
        }
        ListNode* toDelete = cur->next;
        cur->next = toDelete->next;
        delete toDelete; // 释放内存，避免泄漏
        size--;
    }

    // 析构函数：释放链表所有节点（避免内存泄漏）
    ~MyLinkedList() {
        ListNode* cur = head;
        while (cur != nullptr) {// 遍历链表，逐个删除节点
            ListNode* next = cur->next;
            delete cur;// 释放当前节点的内存
            cur = next;// 移动到下一个节点
        }
    }

    // 辅助函数：打印链表（用于测试）
    void printList() {
        ListNode* cur = head->next;
        cout << "链表: ";
        while (cur != nullptr) {
            cout << cur->val << " -> ";
            cur = cur->next;
        }
        cout << "nullptr" << endl;
    }
};

// 测试主函数
int main() {

    SetConsoleOutputCP(65001); // 65001 是 UTF-8 的代码页
    MyLinkedList* obj = new MyLinkedList();

    // 测试用例
    cout << "=== 测试 addAtHead(1) ===" << endl;
    obj->addAtHead(1);
    obj->printList();

    cout << "\n=== 测试 addAtTail(3) ===" << endl;
    obj->addAtTail(3);
    obj->printList();

    cout << "\n=== 测试 addAtIndex(1, 2) ===" << endl;
    obj->addAtIndex(1, 2);
    obj->printList();

    cout << "\n=== 测试 get(1) ===" << endl;
    cout << "get(1) = " << obj->get(1) << endl;

    cout << "\n=== 测试 deleteAtIndex(1) ===" << endl;
    obj->deleteAtIndex(1);
    obj->printList();

    cout << "\n=== 测试 get(1) ===" << endl;
    cout << "get(1) = " << obj->get(1) << endl;

    delete obj;
    return 0;
}