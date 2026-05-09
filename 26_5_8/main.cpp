#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int need = 0; // 需要的后续字节数
        for (int num : data) {
            // 只取低8位，模拟1个字节
            int byte = num & 0xFF;//只保留数字的最后 8 位（也就是 1 个字节），前面多余的位全部扔掉。

            if (need == 0) {
                // 处理首字节
                // >>:右移运算符,作用：二进制整体往右挪，右边挤出去的丢掉，左边补 0。
                if ((byte >> 5) == 0x6) {       // 110xxxxx → 2字节字符
                    need = 1;
                } else if ((byte >> 4) == 0xE) { // 1110xxxx → 3字节字符
                    need = 2;
                } else if ((byte >> 3) == 0x1E) { // 11110xxx → 4字节字符
                    need = 3;
                } else if ((byte >> 7) != 0) { // 不是0xxxxxxx，也不是合法的多字节首字节
                    return false;
                }
                // 0xxxxxxx的情况，need保持0，直接处理下一个
            } else {
                // 处理后续字节，必须是10xxxxxx
                if ((byte >> 6) != 0x2) { // 0x2 二进制是10
                    return false;
                }
                need--;
            }
        }
        // 遍历完后必须没有未处理完的后续字节需求
        return need == 0;
    }
};


int main() {
    Solution sol;
    vector<int> data1 = {197, 130, 1};

    //boolalpha 是 C++ 里的一个输出格式控制符，作用只有一个：让 cout 输出 true / false ，而不是输出 1 / 0。
    cout << boolalpha << sol.validUtf8(data1) << endl; // 输出 true

    vector<int> data2 = {235, 140, 4, 1};
    cout << boolalpha << sol.validUtf8(data2) << endl; // 输出 false

    return 0;
}