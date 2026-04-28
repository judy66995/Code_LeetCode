#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


// 交换两个整数的值
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


// 快排分区函数：把大的放左边，小的放右边
int partition(int nums[], int left, int right) {
    // 1. 选最右边的数当“基准”
    int pivot = nums[right];

    // 2. i 是“左区边界”，一开始指向最左边
    int i = left;

    // 3. 遍历整个区间（除了最后一个基准）
    for (int j = left; j < right; j++) {
         // 如果当前数 ≥ 基准（降序！）
        if (nums[j] >= pivot) {
            // 把它放到左区（i的位置）
            swap(&nums[i], &nums[j]);
            // 左边边界右移
            i++;
        }
    }
    // 4. 最后把基准放到中间，完成分区
    swap(&nums[i], &nums[right]);
    // 5. 返回基准最终位置 → pivotIndex
    return i;
}

// 快速选择：找第 k 大元素（k从1开始）
int findKthLargest(int nums[], int left, int right, int k) {
    int target = k - 1;  // 转成下标
    int pivotIndex = partition(nums, left, right);// 分区后 pivotIndex 是第 pivotIndex 大的元素的下标

    if (pivotIndex == target) {
        return nums[pivotIndex];
    } else if (pivotIndex > target) {
        return findKthLargest(nums, left, pivotIndex - 1, k);
    } else {
        return findKthLargest(nums, pivotIndex + 1, right, k);
    }
}


int main() {
    // 测试数组
    SetConsoleOutputCP(65001); // 设置控制台输出编码为 UTF-8
    int nums[] = {3, 2, 1, 5, 6, 4};
    int n = 6;   // 数组长度
    int k = 2;   // 找第 2 大的数

    // 调用函数
    int result = findKthLargest(nums, 0, n - 1, k);

    // 输出结果
    printf("第 %d 大的数字是：%d\n", k, result);

    return 0;
}