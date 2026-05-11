#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

// 前缀树节点
struct TrieNode {
    bool isEnd;// 是否是单词结尾
    TrieNode* next[26];// 26个字母的子节点指针

    //结构体TrieNode的构造函数TrieNode()，它的作用是初始化一个TrieNode对象。
    //当我们创建一个TrieNode对象时，这个构造函数会被自动调用，来设置这个节点的初始状态。
    TrieNode() : isEnd(false) {// 1. 新建节点时：isEnd 默认为 false
        for (int i = 0; i < 26; ++i)// 2. 循环 26 次（对应 a~z）
            next[i] = nullptr;// 3. 每个指针都设为空
    }
};

class Trie {
private:
    TrieNode* root;// 根节点
public:
    Trie() {
        root = new TrieNode();// 初始化根节点
    }

    // 插入单词
    void insert(string word) {
        TrieNode* cur = root;// 从根节点开始
        for (char c : word) {// 遍历单词的每个字符
            int idx = c - 'a';// 计算字符对应的索引（0~25）
            if (!cur->next[idx]) {// 如果对应的子节点不存在
                cur->next[idx] = new TrieNode();// 创建新节点
            }
            cur = cur->next[idx];// 移动到子节点继续处理下一个字符
        }
        cur->isEnd = true;// 最后一个节点标记为单词结尾
    }

    // 精确搜索单词
    bool search(string word) {
        TrieNode* cur = root;// 从根节点开始
        for (char c : word) {// 遍历单词的每个字符
            int idx = c - 'a';// 计算字符对应的索引（0~25）
            if (!cur->next[idx]) return false;// 如果对应的子节点不存在，说明单词不存在
            cur = cur->next[idx]; // 移动到子节点继续处理下一个字符
        }
        return cur->isEnd;// 最后一个节点必须是单词结尾才算找到单词
    }

    // 判断是否有前缀
    bool startsWith(string prefix) {
        TrieNode* cur = root;// 从根节点开始
        for (char c : prefix) {// 遍历前缀的每个字符
            int idx = c - 'a';// 计算字符对应的索引（0~25）
            if (!cur->next[idx]) return false;// 如果对应的子节点不存在，说明前缀不存在
            cur = cur->next[idx];// 移动到子节点继续处理下一个字符
        }
        return true;// 前缀存在，返回 true
    }
};

int main() {
    SetConsoleOutputCP(65001); // 设置控制台输出编码为 UTF-8

    Trie trie;
    trie.insert("apple");
    cout << trie.search("apple") << endl;   // 1
    cout << trie.search("app") << endl;     // 0
    cout << trie.startsWith("app") << endl; // 1
    trie.insert("app");
    cout << trie.search("app") << endl;     // 1
    return 0;
}