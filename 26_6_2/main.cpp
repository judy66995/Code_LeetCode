#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> res;
        string path;
        backtrack(s, 0, 0, path, res);
        return res;
    }

private:
    // 回溯函数
    void backtrack(const string& s, int pos, int cnt, string& path, vector<string>& res) {
        int n = s.size();// 字符串长度
        
        // 终止条件：分成 4 段，并且刚好用完所有字符
        if (cnt == 4) {
            if (pos == n) {
                res.push_back(path);
            }
            return;
        }

        // 每一段最多 3 个字符
        for (int i = pos; i < pos + 3 && i < n; ++i) {
            string sub = s.substr(pos, i - pos + 1);

            // 检查是否合法
            if (!isValid(sub)) continue;

            // 拼接
            int oldLen = path.size();
            if (cnt != 0) path += ".";
            path += sub;

            // 递归
            backtrack(s, i + 1, cnt + 1, path, res);

            // 回溯（撤销）
            path.resize(oldLen);
        }
    }

    // 判断一段是否合法
    bool isValid(const string& sub) {
        // 长度超过 3 不行
        if (sub.size() > 3) return false;

        // 前导 0 不行（除非只有一个 0）
        if (sub.size() > 1 && sub[0] == '0') return false;

        // 数值必须 0~255
        int num = stoi(sub);
        return num >= 0 && num <= 255;
    }
};


int main() {
    SetConsoleOutputCP(CP_UTF8); // 设置控制台输出为 UTF-8 编码

    Solution sol;
    
  
    string input = "25525511135";  
    
    vector<string> result = sol.restoreIpAddresses(input);

    // 输出结果
    cout << "输入字符串：" << input << endl;
    cout << "合法的 IP 地址：" << endl;
    for (auto& ip : result) {
        cout << "  " << ip << endl;
    }

    return 0;
}