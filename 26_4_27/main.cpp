#include <iostream>
#include <queue>// 引入队列头文件,队列FIFO（先进先出）;而栈是LIFO（后进先出）
#include <windows.h>
using namespace std;

class MyStack {
private:
    queue<int> q1, q2;// 定义两个队列来实现栈的功能

public:
    MyStack() {}

    // 将元素x压入栈顶
    void push(int x) {
        if (!q1.empty()) {// 如果 q1 不为空，则将元素压入 q1
            q1.push(x);// q.push(x):队尾添加元素x,无返回值
        } else {
            q2.push(x);// 否则将元素压入 q2
        }
    }

    // 移除并返回栈顶元素
    int pop() {
        if (empty()) {// 等价于 this->empty(),它就是当前这个栈自己调用自己的成员函数,如果栈为空，输出错误信息并返回 -1
            cerr << "Error: stack is empty!" << endl;
            return -1;
        }

        int topVal;// 用于存储栈顶元素的变量
        if (!q1.empty()) {// 如果 q1 不为空，则从 q1 中弹出元素
            // 把 q1 中除最后一个元素外全部转移到 q2
            while (q1.size() > 1) {
                q2.push(q1.front());// 将 q1 的队头元素压入 q2
                q1.pop();// q.pop():删除队头元素,无返回值,无参数
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
        if (empty()) {// 如果栈为空，输出错误信息并返回 -1
            cerr << "Error: stack is empty!" << endl;
            return -1;
        }

        int topVal;// 用于存储栈顶元素的变量
        if (!q1.empty()) {//如果q1不为空
            while (q1.size() > 1) {// 把 q1 中除最后一个元素外全部转移到 q2
                q2.push(q1.front());// 将 q1 的队头元素压入 q2
                q1.pop();// q.pop():删除队头元素,无返回值,无参数
            }
            topVal = q1.front();// 获取 q1 的队头元素作为栈顶元素
            q2.push(q1.front());// 将栈顶元素重新压入 q2
            q1.pop();// 从 q1 中弹出栈顶元素
        } else {
            while (q2.size() > 1) {// 把 q2 中除最后一个元素外全部转移到 q1
                q1.push(q2.front());// 将 q2 的队头元素压入 q1
                q2.pop();// q.pop():删除队头元素,无返回值,无参数
            }
            topVal = q2.front();
            q1.push(q2.front());
            q2.pop();
        }
        return topVal;
    }

    // 判断栈是否为空
    bool empty() {
        return q1.empty() && q2.empty();// 当两个队列都为空时，栈才为空
    }
};

// 测试主函数
int main() {
    SetConsoleOutputCP(65001); // 65001 是 UTF-8 的代码页

    MyStack stack;// 创建 MyStack 对象

    cout << "压入元素: 1, 2, 3" << endl;
    stack.push(1);// 向栈中压入元素 1
    stack.push(2);// 向栈中压入元素 2
    stack.push(3);// 向栈中压入元素 3

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