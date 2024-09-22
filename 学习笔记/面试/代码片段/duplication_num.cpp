/**
 * @file duplication_num.cpp
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
 * <td>本文件实现两种在数组中寻找重复数字的方法
 * （1） 需要改变数组，但是不需要辅助空间
 * （2） 不需要改变数组，但是需要arr[n+1]的辅助空间
 * </table>
 */

#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
void Swap(T& a, T& b) {
    T temp = a;
    a      = b;
    b      = temp;
}
void PrintArr(const std::vector<int>& arr) {
    for (auto iter : arr) {
        std::cout << iter << " ";
    }
    std::cout << std::endl;
}
/**
 * @brief 不适用辅助内存需要修改原内存
 * @param  arr              被查找冲突的数组
 * @param  duplication      冲突值
 * @return true             有冲突
 * @return false            无冲突
 */
bool Duplicate(std::vector<int>& arr, int& duplication) {
    if (arr.size() == 0) {
        return false;
    }
    // 此for循环如果return false，就代表一定没有重复的值
    for (auto iter : arr) {
        if (iter < 0 || iter > arr.size() - 1) {
            return false;
        }
    }
    // 此处表示这个arr中一定会有重复的值否则下面不是死循环就是越界
    while (1) {
        if (arr[0] == arr[arr[0]]) {
            duplication = arr[0];
            return true;
        }
        Swap(arr[0], arr[arr[0]]);
    }
    return false;
}
/**
 * @brief 使用辅助内存，比较方便
 * @param  arr              被查找冲突的数组
 * @param  duplication      冲突值
 * @return true             有冲突
 * @return false            无冲突
 */
bool DuplicateV2(std::vector<int> arr, int& duplication) {
    if (arr.size() == 0) {
        return false;
    }
    // 此for循环如果return false，就代表一定没有重复的值
    for (auto iter : arr) {
        if (iter < 0 || iter > arr.size() - 1) {
            return false;
        }
    }
    std::vector<int> arr_back(arr.size());
    for (auto iter : arr) {
        if (arr_back[iter] == 0) {
            arr_back[iter]++;
        } else {
            duplication = iter;
            return true;
        }
    }
    return false;
}

int main() {
    std::vector<int> arr = {1, 2, 2, 4, 6, 4, 5};
    PrintArr(arr);
    int duplication = -1;
    std::cout << " is duplicate : " << std::boolalpha
              << Duplicate(arr, duplication) << " duplicat is [" << duplication
              << "]" << std::endl;
    PrintArr(arr);
    return 0;
}