#include <iostream>
#include <vector>
#include <deque>// 双端队列,头尾均可O(1)插入和删除
#include <windows.h>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;// 存储结果
        deque<int> dq; // 存储数组下标，维护单调递减队列
        for(int i = 0; i < nums.size(); ++i)// 从左到右，一个一个遍历数字
        {
            // 1. 清理队尾：比我小的都滚，我要进来
            while(!dq.empty() && nums[i] >= nums[dq.back()])// 只要队列不为空，并且 当前数字 >= 队列最后一个数字
                dq.pop_back();// 删掉队尾
            dq.push_back(i); // 把当前下标加入队列

            // 2. 清理队首：出了窗口的滚，过期了
            while(dq.front() <= i - k)
                dq.pop_front();// 删掉队首

            // 3. 窗口满了，就记录最大值
            if(i >= k - 1)
                res.push_back(nums[dq.front()]);
        }
        return res;
    }
};


int main()
{
    SetConsoleOutputCP(CP_UTF8); // 设置控制台输出编码为UTF-8
    Solution sol;
    // 测试用例
    vector<int> nums = {1,3,-1,-3,5,3,6,7};
    int k = 3;

    vector<int> ans = sol.maxSlidingWindow(nums, k);

    // 打印结果
    cout << "滑动窗口最大值：";
    for(int val : ans)
    {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}