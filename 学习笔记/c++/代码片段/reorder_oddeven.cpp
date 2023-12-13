/**
 * @file reorder_oddeven.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-12-12
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-12-12 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>内容
 * 面试题 21 调整数组顺序使奇数位于偶数前面
 * 输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数位于数组的前半部分，所有偶数存在与数组的后半部分
 * </table>
 */

#include <iostream>
#include <vector>

template <typename T>
void Swap(T& a, T& b) {
    T temp;
    temp = a;
    a    = b;
    b    = temp;
}
bool IsOdd(const int num) {
    return num % 2 == 1 ? true : false;
}

void PrintArr(const std::vector<int>& arr) {
    for (auto iter : arr) {
        std::cout << iter << " ";
    }
    std::cout << std::endl;
}

void Reorder(std::vector<int>& arr, bool (*func)(int)) {
    if (arr.size() == 0) {
        return;
    }
    int start_index = 0;
    int end_index   = arr.size() - 1;
    // 两个index，一个是奇数就从头往后，一个是偶数就从后往前
    // 如果都不满足就可以交换
    while (start_index <= end_index) {
        if (func(arr[start_index])) {
            start_index++;
        } else if (!func(arr[end_index])) {
            end_index--;
        } else {
            Swap(arr[start_index], arr[end_index]);
            start_index++;
            end_index--;
        }
    }
}
void ReorderOddEven(std::vector<int>& arr) {
    Reorder(arr, IsOdd);
}
int main() {
    std::vector<int> arr = {57, 68, 59, 52, 72, 28, 96, 33, 24,
                            57, 68, 59, 52, 72, 28, 96, 33, 24};
    PrintArr(arr);
    ReorderOddEven(arr);
    PrintArr(arr);
    return 0;
}