#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st; // 用栈存储操作数，嵌入式里也可以用数组手动实现
        
        for (const string& token : tokens) {//const：不修改这个字符串（只读）; &：避免字符串复制，直接引用原字符串（效率更高）
            // 情况1：当前是运算符，弹出两个数计算
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                // 注意：先弹出来的是右操作数
                int right = st.top(); st.pop();
                int left = st.top(); st.pop();
                int res;// 存储计算结果
                
                // 按运算符执行计算，嵌入式里也常用switch-case
                if (token == "+") {
                    res = left + right;
                } else if (token == "-") {
                    res = left - right;
                } else if (token == "*") {
                    res = left * right;
                } else { // 除法：题目要求向零截断，直接C++整数除法即可
                    res = left / right;
                }
                
                st.push(res); // 计算结果压回栈中
            } 
            // 情况2：当前是数字，直接压栈
            else {
                st.push(stoi(token)); // stoi是字符串转整数，嵌入式里也可以手动实现
            }
        }
        
        return st.top(); // 栈中最后剩下的就是结果
    }
};


int main() {
    Solution sol;
    
    // 示例1测试：["2","1","+","3","*"] → (2+1)*3=9
    vector<string> t1 = {"2","1","+","3","*"};
    cout << sol.evalRPN(t1) << endl; // 输出9
    
    // 示例2测试：["4","13","5","/","+"] → 4+(13/5)=6
    vector<string> t2 = {"4","13","5","/","+"};
    cout << sol.evalRPN(t2) << endl; // 输出6
    
    return 0;
}