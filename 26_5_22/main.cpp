#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 保证nums1更短，减少二分次数
        if(nums1.size() > nums2.size()) return findMedianSortedArrays(nums2, nums1);
        int m = nums1.size(), n = nums2.size();
        int left = 0, right = m;// nums1分割位置范围[0,m]，可以切在最左边（0）或最右边（m）
        int totalLen = m + n;// 总长度
        int halfLen = (totalLen + 1) / 2;// 中位数位置

        while(left <= right) {
            // i：nums1分割位置，j：nums2分割位置
            int i = left + (right - left) / 2;
            int j = halfLen - i;

            // 边界处理：超出数组视为无穷小/无穷大
            int nums1Left = (i == 0) ? INT_MIN : nums1[i-1];//nums1切分的【左边】最后一个数字
            int nums1Right = (i == m) ? INT_MAX : nums1[i];//nums1切分的【右边】第一个数字
            int nums2Left = (j == 0) ? INT_MIN : nums2[j-1];//nums2切分的【左边】最后一个数字
            int nums2Right = (j == n) ? INT_MAX : nums2[j];//nums2切分的【右边】第一个数字

            // 划分正确：左边最大值 ≤ 右边最小值
            if(nums1Left <= nums2Right && nums2Left <= nums1Right) {
                if(totalLen % 2 == 1) {
                    return max(nums1Left, nums2Left);
                } else {
                    return (max(nums1Left, nums2Left) + min(nums1Right, nums2Right)) / 2.0;
                }
            }
            // nums1切太靠右，往左缩
            else if(nums1Left > nums2Right) {
                right = i - 1;
            }
            // nums1切太靠左，往右扩
            else {
                left = i + 1;
            }
        }
        return 0.0;
    }
};

int main() {
    Solution sol;
    vector<int> n1 = {1,3}, n2 = {2};
    cout << sol.findMedianSortedArrays(n1, n2) << endl; // 2.0
    vector<int> n3 = {1,2}, n4 = {3,4};
    cout << sol.findMedianSortedArrays(n3, n4) << endl; // 2.5
    return 0;
}