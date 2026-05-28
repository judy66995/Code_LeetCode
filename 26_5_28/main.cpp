#include <iostream>
using namespace std;

class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int shift = 0;
        // 不断右移，直到left和right相等，找到公共前缀
        while (left != right) {
            left >>= 1;
            right >>= 1;
            shift++;
        }
        // 左移还原位数
        return left << shift;
    }
};

int main() {
    Solution sol;
    // 测试用例1
    cout << sol.rangeBitwiseAnd(5, 7) << endl;   // 输出4
    // 测试用例2
    cout << sol.rangeBitwiseAnd(0, 0) << endl;   // 输出0
    // 测试用例3
    cout << sol.rangeBitwiseAnd(1, 2147483647) << endl; // 输出0
    return 0;
}