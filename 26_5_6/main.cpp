#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

// 统计小于 n 的质数个数
int countPrimes(int n) {
    if (n <= 2) return 0;

    vector<bool> isPrime(n, true);//创建一个长度为 n 的数组，每个元素都是 bool 类型，并且全部初始化为 true。
    isPrime[0] = isPrime[1] = false;//0 和 1 不是质数，所以将它们对应的值设为 false。

    for (int i = 2; i * i < n; ++i) {//从 2 开始，遍历到 sqrt(n)，因为如果 n 是合数，那么它必定有一个小于或等于 sqrt(n) 的因子。
        if (isPrime[i]) {
            for (int j = i * i; j < n; j += i) {//如果 i 是质数，那么从 i*i 开始，将 i 的倍数标记为非质数。这里 j += i 是为了跳过 i 的倍数，直接跳到下一个 i 的倍数。
                isPrime[j] = false;
            }
        }
    }

    // 统计质数数量
    int count = 0;
    for (bool b : isPrime) {//遍历 isPrime 数组，如果某个元素是 true，说明对应的索引是一个质数，计数器 count 加 1。
        if (b) count++;
    }
    return count;
}

// 主函数：VS Code 运行入口
int main() {
    SetConsoleOutputCP(CP_UTF8);
    int n;
    cout << "请输入一个整数 n：";
    cin >> n;

    int result = countPrimes(n);
    cout << "小于 " << n << " 的质数一共有：" << result << " 个" << endl;

    return 0;
}