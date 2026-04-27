#include <iostream>
#include <queue>// 引入队列头文件,队列FIFO（先进先出）
#include <windows.h>
using namespace std;

class MyStack {
private:
    queue<int> q1, q2;

public:
    MyStack() {}

    // 将元素 x 压入栈顶
    void push(int x) {
        if (!q1.empty()) {
            q1.push(x);
        } else {
            q2.push(x);
        }
    }

    // 移除并返回栈顶元素
    int pop() {
        if (empty()) {
            cerr << "Error: stack is empty!" << endl;
            return -1;
        }

        int topVal;
        if (!q1.empty()) {
            // 把 q1 中除最后一个元素外全部转移到 q2
            while (q1.size() > 1) {
                q2.push(q1.front());
                q1.pop();
            }
            topVal = q1.front();
            q1.pop();
        } else {
            // 把 q2 中除最后一个元素外全部转移到 q1
            while (q2.size() > 1) {
                q1.push(q2.front());
                q2.pop();
            }
            topVal = q2.front();
            q2.pop();
        }
        return topVal;
    }

    // 返回栈顶元素
    int top() {
        if (empty()) {
            cerr << "Error: stack is empty!" << endl;
            return -1;
        }

        int topVal;
        if (!q1.empty()) {
            while (q1.size() > 1) {
                q2.push(q1.front());
                q1.pop();
            }
            topVal = q1.front();
            q2.push(q1.front());
            q1.pop();
        } else {
            while (q2.size() > 1) {
                q1.push(q2.front());
                q2.pop();
            }
            topVal = q2.front();
            q1.push(q2.front());
            q2.pop();
        }
        return topVal;
    }

    // 判断栈是否为空
    bool empty() {
        return q1.empty() && q2.empty();
    }
};

// 测试主函数
int main() {
    SetConsoleOutputCP(65001); // 65001 是 UTF-8 的代码页

    MyStack stack;

    cout << "压入元素: 1, 2, 3" << endl;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    cout << "栈顶元素: " << stack.top() << endl;  // 预期输出 3
    cout << "弹出元素: " << stack.pop() << endl;  // 预期输出 3
    cout << "栈顶元素: " << stack.top() << endl;  // 预期输出 2

    stack.push(4);
    cout << "压入元素: 4" << endl;
    cout << "栈顶元素: " << stack.top() << endl;  // 预期输出 4
    cout << "弹出元素: " << stack.pop() << endl;  // 预期输出 4
    cout << "弹出元素: " << stack.pop() << endl;  // 预期输出 2
    cout << "弹出元素: " << stack.pop() << endl;  // 预期输出 1

    cout << "栈是否为空? " << (stack.empty() ? "是" : "否") << endl;

    return 0;
}