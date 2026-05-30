#include <iostream>
#include <stack>
#include <algorithm>// 引入算法库以使用 min 函数
using namespace std;

class MinStack {
private:
    stack<int> stk;// 主栈,用于存储所有元素
    stack<int> minStk;// 最小栈,每一步同步存 “到现在为止的最小值

public:
    MinStack() {}// 构造函数,初始化两个栈

    void push(int val) {
        stk.push(val);// 将元素压入主栈
        // 最小栈同步压入当前的最小值
        if (minStk.empty()) {
            minStk.push(val);
        } else {
            minStk.push(min(val, minStk.top()));
        }
    }

    void pop() {
        stk.pop();
        minStk.pop();
    }

    int top() {
        return stk.top();
    }

    int getMin() {
        return minStk.top();
    }
};


int main() {
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout << minStack.getMin() << endl; // 输出 -3
    minStack.pop();
    cout << minStack.top() << endl;    // 输出 0
    cout << minStack.getMin() << endl; // 输出 -2
    return 0;
}