#include <iostream>
using namespace std;

class Solution {
public:
    int getSum(int a, int b) {
        // 循环：只要还有进位，就继续计算
        while (b != 0) {
            // 1. 计算进位：只有 1+1 才会产生进位，然后左移1位
            int carry = (a & b) << 1;
            
            // 2. 计算无进位加法结果
            a = a ^ b;
            
            // 3. 把进位值给 b，下一轮继续算
            b = carry;
        }
        // 没有进位了，a 就是最终和
        return a;
    }
};


int main() {
    Solution sol;

    // 测试用例 1：2 + 3 = 5
    int a1 = 2, b1 = 3;
    cout << a1 << " + " << b1 << " = " << sol.getSum(a1, b1) << endl;

    // 测试用例 2：1 + 2 = 3
    int a2 = 1, b2 = 2;
    cout << a2 << " + " << b2 << " = " << sol.getSum(a2, b2) << endl;

    // 测试用例 3：10 + 5 = 15
    int a3 = 10, b3 = 5;
    cout << a3 << " + " << b3 << " = " << sol.getSum(a3, b3) << endl;

    return 0;
}