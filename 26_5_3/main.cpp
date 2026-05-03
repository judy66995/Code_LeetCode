#include <iostream>
#include <unordered_map>
#include <windows.h>

using namespace std;

// 定义带 random 指针的链表节点
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

// 哈希表法：深拷贝带随机指针的链表
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;// 如果原链表为空，直接返回 nullptr

        // 哈希表map：key = 原节点，value = 新节点
        unordered_map<Node*, Node*> map;

        // 第一步：遍历原链表，创建所有新节点，存入哈希表
        Node* cur = head;
        while (cur != nullptr) {
            map[cur] = new Node(cur->val);
            cur = cur->next;
        }

        // 第二步：再次遍历，给新节点设置 next 和 random
        cur = head;
        while (cur != nullptr) {
            Node* copyNode = map[cur];
            copyNode->next = map[cur->next];
            copyNode->random = map[cur->random];
            cur = cur->next;
        }

        // 返回新链表的头节点
        return map[head];
    }
};



// 打印链表（方便看结果）
void printList(Node* head) {
    Node* cur = head;// 从头节点开始遍历链表
    while (cur != nullptr) {// 当当前节点不为空时，继续遍历
        cout << "节点值：" << cur->val;
        if (cur->random) {// 如果 random 指针不为空，打印它指向的节点值
            cout << "，random 指向：" << cur->random->val;
        } else {// 如果 random 指针为空，说明它指向 null
            cout << "，random 指向：null";
        }
        cout << endl;
        cur = cur->next;
    }
}

int main() {

    SetConsoleOutputCP(CP_UTF8); // 设置控制台输出为 UTF-8，支持中文显示

    // 构建测试链表：1 -> 2 -> 3
    Node* head = new Node(1);// 创建节点 1
    head->next = new Node(2);// 创建节点 2，并连接到节点 1
    head->next->next = new Node(3);// 创建节点 3，并连接到节点 2

    // 设置 random 指针
    head->random = head->next->next;       // 1 的 random 指向 3
    head->next->random = head;             // 2 的 random 指向 1
    head->next->next->random = head->next; // 3 的 random 指向 2

    cout << "===== 原链表 =====" << endl;
    printList(head);

    // 深拷贝
    Solution sol;
    Node* newHead = sol.copyRandomList(head);// 调用深拷贝函数，得到新链表的头节点

    cout << "\n===== 拷贝后的新链表 =====" << endl;
    printList(newHead);

    return 0;
}