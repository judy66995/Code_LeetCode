#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Solution {
public:
    int calculate(string s) {
        stack<int> st;
        int num = 0;
        char op = '+';

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
                op = c;
                num = 0;
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