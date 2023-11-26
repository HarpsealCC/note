/**
 * @file find_num_in2darray.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-11-26
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-11-26 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>在二维数组中寻找一个数
 * </table>
 */
#include <iostream>

bool FindNumIn2DArray(int* arr, int rows, int cols, const int num) {
    if (arr == nullptr || rows <= 0 || cols <= 0) {
        return false;
    }
    int row = 0;
    int col = cols - 1;
    int key = arr[col];  // 选取右上角的值
    while (col >= 0 || row <= rows) {
        if (key != num) {
            if (num > key) {  // num 大于 key，row++查找数组下一行
                row++;
                key = arr[row * cols + col];
            } else {  // num小于key，col-- 查找数组前一列
                col--;
            }
            key = arr[row * cols + col];
            continue;
        } else {
            return true;
        }
    }
    return false;
}

int main() {
    /**
     * 数组从左往右从上到下都是递增
     * 1 2 8 9
     * 2 4 9 12
     * 4 7 10 13
     * 6 8 11 15
     */
    int arr[] = {1, 2, 8, 9, 2, 4, 9, 12, 4, 7, 10, 13, 6, 8, 11, 15};
    std::cout << " is find " << std::boolalpha
              << FindNumIn2DArray(arr, 4, 4, 100) << std::endl;
}