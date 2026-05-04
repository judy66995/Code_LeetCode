#include <iostream>
#include <string>
#include <cctype>    // 用于 isdigit()
#include <climits>   // 用于 INT_MAX 和 INT_MIN
#include <windows.h>

using namespace std;

// 字符串转整数函数
int myAtoi(string s) {
    int i = 0;// 当前处理字符串的索引
    int n = s.size();// 字符串长度
    int sign = 1;         // 符号，默认正数
    long long result = 0; // 用 long long 防止中间溢出

    // 1. 跳过前面的空格
    while (i < n && s[i] == ' ') {
        i++;
    }

    // 2. 处理正负号
    if (i < n && (s[i] == '+' || s[i] == '-')) {
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }

    // 3. 读取数字，遇到非数字停止
    while (i < n && isdigit(s[i])) {
        int digit = s[i] - '0';// 当前字符转换为数字

        // 检查是否会溢出
        if (result > (INT_MAX - digit) / 10) {// 如果 result * 10 + digit > INT_MAX，说明会溢出
            return sign == 1 ? INT_MAX : INT_MIN;
        }

        result = result * 10 + digit;
        i++;
    }

    // 4. 返回带符号的结果
    return (int)(result * sign);// 最后将结果乘以符号并返回，强制转换为 int 类型
}


int main() {
    SetConsoleOutputCP(CP_UTF8); // 设置控制台输出为 UTF-8 编码
    string input;
    cout << "请输入一个字符串：";
    getline(cin, input); // 读取整行输入（包括空格）

    int num = myAtoi(input);// 调用字符串转整数函数
    cout << "转换后的整数是：" << num << endl;

    return 0;
}