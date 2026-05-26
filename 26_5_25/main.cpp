#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Solution {
public:
    int calculate(string s) {
        stack<int> st;// 存储数字，遇到乘除时直接计算并更新栈顶
        int num = 0;// 当前数字
        char op = '+';// 上一个运算符，初始为'+'，方便处理第一个数字

        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            if (isdigit(c)) {
                num = num * 10 + (c - '0');
            }
            // 遇到运算符 或 最后一位，计算上一个运算符
            if ((!isdigit(c) && c != ' ') || i == s.size() - 1) {
                if (op == '+') st.push(num);
                else if (op == '-') st.push(-num);
                else if (op == '*') {
                    int top = st.top(); st.pop();
                    st.push(top * num);
                } else if (op == '/') {
                    int top = st.top(); st.pop();
                    st.push(top / num);
                }
                op = c;// 更新运算符
                num = 0;// 重置数字
            }
        }
        // 累加栈内所有数
        int res = 0;
        while (!st.empty()) {
            res += st.top();
            st.pop();
        }
        return res;
    }
};

int main() {
    Solution sol;
    cout << sol.calculate("3+2*2") << endl;    // 7
    cout << sol.calculate(" 3/2 ") << endl;    // 1
    cout << sol.calculate(" 3+5 / 2 ") << endl;// 5
    return 0;
}