#include <iostream>
#include <string>
#include <vector>
#include <sstream> // string stream字符串流，用于字符串分割

using namespace std;

class Solution {
public:
    string validIPAddress(string queryIP) {
        // 判断IPv4
        if (queryIP.find('.') != string::npos) {// 包含'.'，可能是IPv4
            vector<string> parts;// 存储分割后的IP地址段

            // 创建字符串流对象
            // 把字符串queryIP（比如 "192.168.1.1"）装进一个叫ss的 “字符串流” 里,让这个字符串可以像水流一样，一段一段读出来
            stringstream ss(queryIP);

            string part;// 临时变量，用来存储每段IP地址

            // 按'.'分割
            while (getline(ss, part, '.')) {//从字符串流 ss 里读取一段内容,读到 . 这个字符就停止读取，并且自动把这个 . 丢掉，不放进 part
                parts.push_back(part);
            }
            // 必须4段
            if (parts.size() != 4) return "Neither";
            for (string p : parts) {
                // 长度非法：空、大于3位
                if (p.empty() || p.size() > 3) return "Neither";
                // 前导零
                if (p.size() > 1 && p[0] == '0') return "Neither";
                // 必须全是数字
                for (char c : p) {
                    if (!isdigit(c)) return "Neither";
                }
                // 数值0~255
                int num = stoi(p);// 把字符串p转换成整数num
                if (num < 0 || num > 255) return "Neither";
            }
            return "IPv4";
        }
        // 判断IPv6
        else if (queryIP.find(':') != string::npos) {
            vector<string> parts;
            stringstream ss(queryIP);
            string part;
            // 按':'分割
            while (getline(ss, part, ':')) {
                parts.push_back(part);
            }
            // 必须8段
            if (parts.size() != 8) return "Neither";
            for (string p : parts) {
                // 长度非法：空、大于4位
                if (p.empty() || p.size() > 4) return "Neither";
                // 校验十六进制字符
                for (char c : p) {
                    if (!isdigit(c) && !(c >= 'a' && c <= 'f') && !(c >= 'A' && c <= 'F'))
                        return "Neither";
                }
            }
            return "IPv6";
        }
        return "Neither";
    }
};

int main() {
    Solution sol;
    cout << sol.validIPAddress("192.168.1.1") << endl;        // IPv4
    cout << sol.validIPAddress("2001:0db8:85a3:0000:0000:8a2e:0370:7334") << endl; // IPv6
    cout << sol.validIPAddress("256.256.256.256") << endl;    // Neither
    return 0;
}