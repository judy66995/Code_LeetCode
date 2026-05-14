#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stack; // 用vector模拟栈，方便遍历拼接
        string dir_name;      // 临时保存当前解析到的目录名
        path += "/";          // 统一处理末尾，避免最后一个目录漏处理
        
        for (char c : path) {
            if (c == '/') {
                // 遇到'/'，说明当前目录名解析完成
                if (!dir_name.empty()) {// 只有当dir_name非空时才处理，避免连续'/'导致的空目录名
                    if (dir_name == "..") {
                        // 上一级目录：栈非空则弹出
                        if (!stack.empty()) {// 栈非空才弹出，避免越界
                            stack.pop_back();
                        }
                    } else if (dir_name != ".") {
                        // 普通目录名：压栈
                        stack.push_back(dir_name);
                    }
                    dir_name.clear(); // 重置，准备解析下一个目录名
                }
            } else {
                // 拼接目录名（支持带点的目录名，比如"abc.def"）
                dir_name += c;
            }
        }
        
        // 拼接最终路径
        string result = "/";// 根目录
        for (size_t i = 0; i < stack.size(); ++i) {
            if (i > 0) {// 不是第一个目录，前面需要加'/'
                result += "/";
            }
            result += stack[i];// 添加目录名
        }
        return result;
    }
};


int main() {
    Solution sol;
    cout << sol.simplifyPath("/home/") << endl;          // /home
    cout << sol.simplifyPath("/a/./b/../../c/") << endl; // /c
    cout << sol.simplifyPath("/../") << endl;             // /
    cout << sol.simplifyPath("/home//foo/") << endl;     // /home/foo
    return 0;
}