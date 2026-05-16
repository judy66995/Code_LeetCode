#include <iostream>
#include <vector>
#include <climits> // <climits> 是 C++ 里用来获取「整数类型极值」的头文件
using namespace std;

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();// 获取数组长度
        // 边界处理：数组长度为0或1，直接返回0
        if (n <= 1) return 0;// 因为长度为0或1的数组本身就是有序的，无需排序
        
        int left = -1, right = -1;// 初始化左右边界为-1，表示尚未找到无序子数组
        int max_val = INT_MIN;// 找最大值 → 初始值设为【最小的数】
        int min_val = INT_MAX;// 找最小值 → 初始值设为【最大的数】
        
        // 1. 从左到右找右边界
        for (int i = 0; i < n; ++i) {
            if (nums[i] < max_val) {
                // 当前值比之前的最大值小，说明这里是无序的，更新右边界
                right = i;
            } else {
                // 更新当前最大值
                max_val = nums[i];
            }
        }
        
        // 2. 从右到左找左边界
        for (int i = n - 1; i >= 0; --i) {
            if (nums[i] > min_val) {
                // 当前值比之后的最小值大，说明这里是无序的，更新左边界
                left = i;
            } else {
                // 更新当前最小值
                min_val = nums[i];
            }
        }
        
        // 数组本身有序，left和right都没被更新，返回0
        if (left == -1) return 0;
        // 计算无序子数组长度
        return right - left + 1;
    }
};


int main() {
    Solution sol;
    // 示例1
    vector<int> nums1 = {2,6,4,8,10,9,15};
    cout << sol.findUnsortedSubarray(nums1) << endl; // 输出5
    
    // 示例2
    vector<int> nums2 = {1,2,3,4};
    cout << sol.findUnsortedSubarray(nums2) << endl; // 输出0
    
    // 示例3
    vector<int> nums3 = {1};
    cout << sol.findUnsortedSubarray(nums3) << endl; // 输出0
    
    return 0;
}