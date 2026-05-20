#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0;//窗口左边界，慢指针
        int sum = 0;//窗口内元素和
        int res = INT_MAX;//记录满足条件的最短长度，初始为无穷大。

        for (int right = 0; right < nums.size(); right++)
        {
            sum += nums[right];
            // 总和达标，开始收缩左边界，找更短区间
            while (sum >= target)
            {
                res = min(res, right - left + 1);
                sum -= nums[left];
                left++;
            }
        }
        return res == INT_MAX ? 0 : res;
    }
};

int main()
{
    Solution sol;
    vector<int> arr = {2,3,1,2,4,3};
    int t = 7;
    cout << sol.minSubArrayLen(t, arr) << endl;
    return 0;
}