#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) return 0;

        // 按气球【右边界】从小到大排序
        sort(points.begin(), points.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] < b[1];
        });

        int res = 1;
        int arrowPos = points[0][1]; // 第一支箭射在第一个气球的右端点

        for (int i = 1; i < points.size(); i++) {
            // 当前气球起点 > 箭的位置 → 射不到，需要新箭
            if (points[i][0] > arrowPos) {
                res++;
                arrowPos = points[i][1];
            }
        }
        return res;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> p1 = {{10,16},{2,8},{1,6},{7,12}};
    cout << sol.findMinArrowShots(p1) << endl; // 输出 2
    return 0;
}