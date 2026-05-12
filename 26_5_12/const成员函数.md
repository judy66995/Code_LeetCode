
# const 成员函数 = 承诺：这个函数绝对不会修改类/结构体里的任何成员变量

---

## 1. 语法长这样
```cpp
void 函数名(参数) const {
    // 函数体
}
```
**const 写在小括号后面、大括号前面**。

---

## 2. 举例
以之前的 TrieNode 为例，写一个普通函数 和 const 函数对比：

```cpp
struct TrieNode {
    bool isEnd;
    TrieNode* next[26];

    // 普通成员函数：可以修改成员变量
    void setEnd() {
        isEnd = true;   // 允许改
    }

    // const 成员函数：只读，不许改
    void printInfo() const {
        // isEnd = false;  // 这里写了直接报错！不能修改
    }
};
```

### 核心规则
- **普通成员函数**：可读、可改成员变量
- **const 成员函数**：**只能读，不能改**任何成员变量

---

## 3. 为什么要搞这个东西？
1. **防止不小心改错数据**
   你本来只想查数据、打印数据，加个 `const`，编译器帮你把关，写错直接编译报错。

2. **const 对象只能调用 const 成员函数**
```cpp
const TrieNode node; // 只读对象
node.printInfo();    // 合法，printInfo 是 const 函数
node.setEnd();       // 报错！普通函数不能给 const 对象用
```

3. **工程规范、嵌入式/大型项目必备**
   写接口、工具查询函数，一律加 `const`，代码更安全、可读性更高。

---

## 4. 结合 std::string 里的 size()
```cpp
size_t size() const;
```
意思：
`size()` 只是**读取字符串长度**，**绝不修改字符串内容**，所以标成 `const` 成员函数。

---

## 5. 极简总结
- **const 成员函数**：括号后面带 `const`
- **作用**：承诺**不修改对象的任何成员变量**
- **权限**：只能读、不能写
- **好处**：编译器帮你查错、支持只读对象调用、代码更规范安全