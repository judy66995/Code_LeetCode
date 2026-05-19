#include <iostream>
using namespace std;

// 链表节点定义
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {// 删除链表中的重复元素，返回新的链表头节点
        // 虚拟头节点
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* pre = dummy;// 前一个节点，初始指向虚拟头节点
        ListNode* cur = head;// 当前节点，初始指向链表头节点

        while(cur != nullptr)// 遍历链表
        {
            // 遇到重复值
            while(cur->next != nullptr && cur->val == cur->next->val)// 如果当前节点的值和下一个节点的值相同，继续往后走，直到找到不同的值
            {
                cur = cur->next;
            }
            // 没有重复，正常往后走
            if(pre->next == cur)
            {
                pre = pre->next;
            }
            // 有重复，跳过所有重复节点
            else
            {
                pre->next = cur->next;
            }
            cur = cur->next;// 继续遍历下一个节点
        }
        return dummy->next;
    }
};

// 打印链表
void printList(ListNode* head)
{
    while(head)
    {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main()
{
    // 构建链表 1 2 3 3 4 4 5
    ListNode* n1 = new ListNode(1);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(3);
    ListNode* n4 = new ListNode(3);
    ListNode* n5 = new ListNode(4);
    ListNode* n6 = new ListNode(4);
    ListNode* n7 = new ListNode(5);
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = n6;
    n6->next = n7;

    Solution sol;
    ListNode* res = sol.deleteDuplicates(n1);
    printList(res);
    return 0;
}