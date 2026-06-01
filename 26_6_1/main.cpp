#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int total = 0; // 全局净油量
        int tank  = 0; // 当前油箱油量
        int start = 0; // 候选起点

        for (int i = 0; i < gas.size(); ++i) {
            int net = gas[i] - cost[i]; // 每一段的净油量
            total += net;// 累积净油量
            tank  += net;// 累积当前油箱油量

            // 油箱空了，说明从start到i这段路走不通
            if (tank < 0) {
                start = i + 1; // 跳到下一个候选起点
                tank  = 0;     // 重置油箱
            }
        }

        // 总油量够就返回start，否则-1
        return total >= 0 ? start : -1;
    }
};

int main() {
    Solution sol;
    vector<int> gas  = {1,2,3,4,5};
    vector<int> cost = {3,4,5,1,2};
    cout << sol.canCompleteCircuit(gas, cost) << endl; // 输出 3
    return 0;
}