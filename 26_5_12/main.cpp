#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int compareVersion(string version1, string version2) {
        int i = 0, j = 0;
        int n1 = version1.size(), n2 = version2.size();

        while (i < n1 || j < n2) {//  当 version1 和 version2 都没有比较完时，继续比较
            int num1 = 0, num2 = 0;

            // 解析 version1 当前段
            while (i < n1 && version1[i] != '.') {// 解析 version1 当前段，直到遇到 '.' 或者字符串结束
                num1 = num1 * 10 + (version1[i] - '0');
                i++;
            }
            i++; // 跳过 .

            // 解析 version2 当前段
            while (j < n2 && version2[j] != '.') {// 解析 version2 当前段，直到遇到 '.' 或者字符串结束
                num2 = num2 * 10 + (version2[j] - '0');
                j++;
            }
            j++; // 跳过 .

            if (num1 > num2) return 1;
            if (num1 < num2) return -1;
        }
        return 0;
    }
};

int main() {
    Solution sol;
    cout << sol.compareVersion("1.01", "1.001") << endl;  // 0
    cout << sol.compareVersion("1.0", "1.0.0") << endl;    // 0
    cout << sol.compareVersion("0.1", "1.0") << endl;      // -1
    return 0;
}