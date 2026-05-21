#include <iostream>
#include <stack>
using namespace std;

// 二叉树节点定义
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {//  中序遍历，非递归实现
        stack<TreeNode*> st;// 辅助栈
        TreeNode* cur = root;// 当前节点
        int cnt = 0;

        while (cur != nullptr || !st.empty())
        {
            // 一直往左走，压栈
            while (cur != nullptr)
            {
                st.push(cur);
                cur = cur->left;
            }

            // 取出栈顶
            cur = st.top();
            st.pop();
            cnt++;

            // 找到第k小，直接返回
            if (cnt == k)
                return cur->val;

            // 处理右子树
            cur = cur->right;
        }
        return -1;
    }
};

int main()
{
    // 构建示例树：3,1,4,null,2
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n2 = new TreeNode(2);
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n4 = new TreeNode(4);
    n3->left = n1;
    n3->right = n4;
    n1->right = n2;

    Solution sol;
    cout << sol.kthSmallest(n3, 3) << endl; // 输出3
    return 0;
}