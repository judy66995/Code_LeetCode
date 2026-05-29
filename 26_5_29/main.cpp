#include <iostream>
#include <windows.h>

using namespace std;

// 链表节点定义
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head || !head->next) return NULL;// 链表为空或只有一个节点，不可能有环
        
        ListNode *slow = head;
        ListNode *fast = head;
        
        // 第一步：快慢指针找相遇点
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) { // 相遇，说明有环
                // 第二步：head和相遇点同时出发，找环入口
                ListNode *p = head;
                while (p != slow) {
                    p = p->next;
                    slow = slow->next;
                }
                return p;
            }
        }
        return NULL; // 无环
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8); // 设置控制台输出为UTF-8编码，支持中文输出

    // 构建示例链表：3 → 2 → 0 → -4 → 2（环）
    ListNode* n3 = new ListNode(3);
    ListNode* n2 = new ListNode(2);
    ListNode* n0 = new ListNode(0);
    ListNode* n4 = new ListNode(-4);
    n3->next = n2;
    n2->next = n0;
    n0->next = n4;
    n4->next = n2; // 尾节点指向n2，形成环
    
    Solution sol;
    ListNode* ans = sol.detectCycle(n3);
    if (ans) {
        cout << "环入口节点的值为：" << ans->val << endl; // 输出2
    } else {
        cout << "链表无环" << endl;
    }
    
    // 释放内存（简化处理，实际开发中需更严谨）
    delete n3; delete n2; delete n0; delete n4;
    return 0;
}