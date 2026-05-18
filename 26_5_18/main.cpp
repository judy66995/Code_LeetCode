#include <iostream>
#include <vector>
using namespace std;

class MyCircularQueue {
private:
    vector<int> arr;// 存储队列元素的数组
    int front;   // 队头下标
    int rear;    // 队尾下一个位置
    int capacity;// 队列容量

public:
    MyCircularQueue(int k) {
        capacity = k + 1;// 预留一个位置区分满和空
        arr.resize(capacity);
        front = 0;
        rear = 0;
    }

    // 入队
    bool enQueue(int value) {
        if (isFull()) return false;
        arr[rear] = value;
        rear = (rear + 1) % capacity;
        return true;
    }

    // 出队
    bool deQueue() {//从队头删一个元素，成功返回 true
        if (isEmpty()) return false;
        front = (front + 1) % capacity;
        return true;
    }

    // 获取队首
    int Front() {
        if (isEmpty()) return -1;
        return arr[front];
    }

    // 获取队尾
    int Rear() {
        if (isEmpty()) return -1;
        return arr[(rear - 1 + capacity) % capacity];
    }

    // 是否为空
    bool isEmpty() {
        return front == rear;
    }

    // 是否已满
    bool isFull() {
        // (rear + 1) % capacity 计算的结果是rear的下一个环形位置，如果这个位置等于front，说明队列已满
        return (rear + 1) % capacity == front;
    }
};


int main()
{
    MyCircularQueue q(3);
    cout << q.enQueue(1) << endl;
    cout << q.enQueue(2) << endl;
    cout << q.enQueue(3) << endl;
    cout << q.enQueue(4) << endl;
    cout << q.Rear() << endl;
    cout << q.isFull() << endl;
    cout << q.deQueue() << endl;
    cout << q.enQueue(4) << endl;
    cout << q.Rear() << endl;
    return 0;
}