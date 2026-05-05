#include <iostream>
#include <vector>//包含动态数组的头文件
#include <windows.h>

using namespace std;

// 螺旋遍历矩阵函数
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> res;
    if (matrix.empty()) return res;//如果矩阵为空，直接返回空结果

    int top = 0;
    int bottom = matrix.size() - 1;//matrix.size() = 二维数组的行数
    int left = 0;
    int right = matrix[0].size() - 1;//matrix[i].size() = 第 i 行的元素个数（列数）

    while (top <= bottom && left <= right) {
        // 左 → 右
        for (int j = left; j <= right; j++)
            res.push_back(matrix[top][j]);//往res的最后面添加元素matrix[top][j]
        top++;

        // 上 → 下
        for (int i = top; i <= bottom; i++)
            res.push_back(matrix[i][right]);//往res的最后面添加元素matrix[i][right]
        right--;

        // 右 → 左
        if (top <= bottom) {
            for (int j = right; j >= left; j--)
                res.push_back(matrix[bottom][j]);
            bottom--;
        }

        // 下 → 上
        if (left <= right) {
            for (int i = bottom; i >= top; i--)
                res.push_back(matrix[i][left]);
            left++;
        }
    }
    return res;
}


int main() {
    SetConsoleOutputCP(CP_UTF8);
    // 你可以在这里随便改矩阵
    vector<vector<int>> matrix = {//定义一个二维向量，表示一个矩阵
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    vector<int> result = spiralOrder(matrix);//调用螺旋遍历函数，并将结果存储在result向量中

    // 输出结果
    cout << "螺旋遍历结果：";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}