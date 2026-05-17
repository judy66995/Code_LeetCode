#include <iostream>
#include <vector>
#include <stack>
#include <Windows.h>
using namespace std;

class Solution
{
public:
    vector<int> dailyTemperatures(vector<int>& temperatures)
    {
        int n = temperatures.size();
        vector<int> res(n, 0);// 创建一个int类型动态数组，一共开辟n个位置，并且把里面每一个元素全部初始化为0
        
        // 栈里存的是数组下标
        stack<int> st;

        // 从最后一天往前遍历
        for (int i = n - 1; i >= 0; i--)
        {
            // 把栈里温度 <= 当前温度的全部弹出
            while (!st.empty() && temperatures[st.top()] <= temperatures[i])
            {
                st.pop();
            }

            // 栈不为空，说明找到了更热的一天
            if (!st.empty())
            {
                res[i] = st.top() - i;// 计算等待天数
            }
            
            // 当前下标入栈
            st.push(i);
        }
        return res;
    }
};

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    Solution sol;
    vector<int> temp = {73,74,75,71,69,72,76,73};
    vector<int> ans = sol.dailyTemperatures(temp);

    cout << "等待天数：";
    for (int num : ans)
    {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}