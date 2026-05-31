#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {

        //二分法查找公式写法
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2; // 防溢出写法
            if (nums[mid] == target) {
                return mid;
            }

            // 判断左半部分是否有序
            if (nums[left] <= nums[mid]) {
                // 左半部分有序，判断target是否在左半部分
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                // 右半部分有序，判断target是否在右半部分
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {4,5,6,7,0,1,2};
    cout << sol.search(nums, 0) << endl;  // 输出4
    cout << sol.search(nums, 3) << endl;  // 输出-1
    return 0;
}
