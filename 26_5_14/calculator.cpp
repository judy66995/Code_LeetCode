#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Solution {
public:
    int calculate(string s) {
        stack<pair<int, int>> stk; // 保存括号外的结果和符号; stack<pair<int, int>> stk:一对整数(一个 pair 里面装两个 int 类型的数)
        int result = 0;    // 当前计算结果
        int sign = 1;      // 当前数字的符号，1为正，-1为负
        int num = 0;       // 当前解析的数字

        for (char c : s) {
            if (isdigit(c)) {
                // 解析多位数，比如"123" → 123
                num = num * 10 + (c - '0');
            } else if (c == '+' || c == '-') {
                // 把之前的数字加到结果里
                result += sign * num;
                // 更新当前符号
                sign = (c == '+') ? 1 : -1;
                num = 0; // 重置数字
            } else if (c == '(') {
                // 遇到左括号，保存当前上下文
                stk.push({result, sign});
                // 重置，开始计算括号内的表达式
                result = 0;
                sign = 1;
                num = 0;
            } else if (c == ')') {
                // 遇到右括号，先把括号内的数字加到结果
                result += sign * num;
                // 恢复括号外的上下文
                auto top = stk.top();
                stk.pop();
                int prev_result = top.first;
                int prev_sign = top.second;
                // 括号内的结果，按括号外的符号加到之前的结果里
                result = prev_result + prev_sign * result;
                num = 0;
            }
            // 遇到空格，什么都不做
        }
        // 最后还有一个数字没加进去
        result += sign * num;
        return result;
    }
};


int main() {
    Solution sol;
    // 示例1
    cout << sol.calculate("1 + 1") << endl;          // 输出 2
    // 示例2
    cout << sol.calculate("2-1 + 2") << endl;        // 输出 3
    // 示例3
    cout << sol.calculate("(1+(4+5+2)-3)+(6+8)") << endl; // 输出 23
    // 测试负数
    cout << sol.calculate("-1+2") << endl;           // 输出 1
    return 0;
}