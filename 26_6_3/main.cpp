#include <iostream>
using namespace std;

// 链表节点定义
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;// 链表为空或只有一个节点，无需排序

        // 1.计算链表总长度
        int n = 0;
        ListNode* p = head;
        while(p) {n++; p = p->next;}

        ListNode dummy(0); // 哨兵头节点，统一链表头操作
        dummy.next = head;

        // 自底向上：分组长度从1开始翻倍
        for(int len=1; len<n; len *=2){
            ListNode* pre = &dummy;// 每轮分组前，pre指向已排序部分的末尾
            ListNode* cur = pre->next;// cur指向待排序部分的起始
            while(cur){
                // 拆分第一段：cur起始，取len个节点
                ListNode* l1 = cur;
                ListNode* l2 = split(l1, len);
                // 拆分第二段：l2起始，取len个节点
                cur = split(l2, len);
                // 合并两个有序链表，拼到pre后面
                pre->next = merge(l1,l2);
                // pre移动到合并后链表尾，准备下一组
                while(pre->next) pre = pre->next;
            }
        }
        return dummy.next;// 返回排序后的链表头
    }

private:
    // 从head切出前k个节点，返回后半段起点
    ListNode* split(ListNode* head, int k){
        while(--k && head) head = head->next;
        if(!head) return nullptr;
        ListNode* next = head->next;
        head->next = nullptr; // 断开前后链表
        return next;
    }

    // 合并两个有序单链表，返回新表头
    ListNode* merge(ListNode* l1, ListNode* l2){
        ListNode dummy(0);
        ListNode* p = &dummy;
        while(l1 && l2){
            if(l1->val < l2->val){
                p->next = l1; l1 = l1->next;
            }else{
                p->next = l2; l2 = l2->next;
            }
            p = p->next;
        }
        p->next = l1 ? l1 : l2;
        return dummy.next;
    }
};


int main()
{
    // 构建 4->2->1->3
    ListNode n4(3),n3(1,&n4),n2(2,&n3),n1(4,&n2);
    Solution sol;
    ListNode* res = sol.sortList(&n1);
    // 遍历输出
    while(res){
        cout << res->val << " ";
        res = res->next;
    }
    return 0;
}