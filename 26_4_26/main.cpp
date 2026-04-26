#include <iostream>
#include <stack>
#include <string>
#include <windows.h>
using namespace std;


// 字符串解码函数（标准 C++，兼容所有编译器）
string decodeString(string s) {
    // 栈存储：第一个是之前的字符串，第二个是重复次数
    stack<pair<string, int>> st;
    string current_str;
    int current_num = 0;

    for (int i = 0; i < s.size(); i++) {// 遍历输入字符串
        char ch = s[i];
        // 处理数字
        if (ch >= '0' && ch <= '9') {
            current_num = current_num * 10 + (ch - '0');// 处理多位数字
        }
        // 遇到左括号 [，压栈保存状态
        else if (ch == '[') {
            st.push(make_pair(current_str, current_num));// 保存当前字符串和数字
            current_str = "";// 重置当前字符串
            current_num = 0;// 重置当前数字
        }
        // 遇到右括号 ]，弹栈拼接结果
        else if (ch == ']') {
    
            pair<string, int> top = st.top();// 获取栈顶元素
            st.pop();// 弹出栈顶元素
            string prev_str = top.first;// 获取之前的字符串
            int num = top.second;// 获取重复次数

            string temp;// 构建重复的字符串
            for (int j = 0; j < num; j++) {// 重复拼接
                temp += current_str;    
            }
            current_str = prev_str + temp;// 拼接之前的字符串和当前重复的字符串
        }
        // 处理字母
        else {
            current_str += ch;// 直接拼接字母到当前字符串
        }
    }
    return current_str;
}


int main() {
    // 测试用例
    SetConsoleOutputCP(65001); // 65001 是 UTF-8 的代码页

    cout << "解码 3[a]2[bc] = " << decodeString("3[a]2[bc]") << endl;
    cout << "解码 3[a2[c]] = " << decodeString("3[a2[c]]") << endl;
    cout << "解码 10[ab] = " << decodeString("10[ab]") << endl;

    return 0;
}