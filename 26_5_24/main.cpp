#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // 如果区间为空，直接返回空
        if (intervals.empty()) {
            return {};
        }

        // 按区间的起点从小到大排序
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> res;
        // 先把第一个区间放进去
        res.push_back(intervals[0]);

        // 从第二个开始遍历
        for (int i = 1; i < intervals.size(); i++) {
            // 拿到结果里最后一个区间
            vector<int>& last = res.back();

            // 当前区间的起点 <= 最后一个区间的终点 → 重叠，要合并
            if (intervals[i][0] <= last[1]) {
                // 合并：终点更新成两个终点的最大值
                last[1] = max(last[1], intervals[i][1]);
            } else {
                // 不重叠，直接加入结果
                res.push_back(intervals[i]);
            }
        }

        return res;
    }
};


int main() {
    SetConsoleOutputCP(CP_UTF8); // 设置控制台输出为 UTF-8 编码
    Solution sol;

    // 测试用例 1
    vector<vector<int>> intervals1 = {{1,3},{2,6},{8,10},{15,18}};
    vector<vector<int>> ans1 = sol.merge(intervals1);

    cout << "合并结果 1：" << endl;
    for (auto& interval : ans1) {
        cout << "[" << interval[0] << "," << interval[1] << "] ";
    }
    cout << endl;

    // 测试用例 2
    vector<vector<int>> intervals2 = {{1,4},{4,5}};
    vector<vector<int>> ans2 = sol.merge(intervals2);

    cout << "合并结果 2：" << endl;
    for (auto& interval : ans2) {
        cout << "[" << interval[0] << "," << interval[1] << "] ";
    }
    cout << endl;

    return 0;
}