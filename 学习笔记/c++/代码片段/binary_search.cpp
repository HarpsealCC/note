/**
 * @file binary_search.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-11-22
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-11-22 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>内容
 * 本文件用于练习二分查找
 * (1) 使用递归
 * (2) 不使用递归
 * </table>
 */

#include <iostream>
#include <algorithm>
#include <vector>

void PrintArr(const std::vector<int> &arr)
{
    for (auto iter : arr)
    {
        std::cout << iter << " ";
    }
    std::cout << std::endl;
}
/**
 * @brief 二分法的递归查找，需要注意数组有序与非法情况
 * @param  arr              有序数组
 * @param  low              下限下标
 * @param  high             上限下标
 * @param  key              待查询的值
 * @return int >=0为数据位置，-1为找不到
 */
int BinarySearch(std::vector<int> &arr, int low, int high, int key)
{
    if (low > high)
        return -1;
    int mid = low + (high - low) / 2;
    if (key == arr[mid])
    {
        return mid;
    }
    else if (key < arr[mid])
    {
        return BinarySearch(arr, low, mid - 1, key);
    }
    else
    {
        return BinarySearch(arr, mid + 1, high, key);
    }
}
/**
 * @brief 二分法的非递归查找方法
 * @param  arr              有序数组
 * @param  key              待查询的值
 * @return int >=0为数据位置，-1为找不到
 */
int BinarySearch(std::vector<int> &arr, int key)
{
    int low = 0;
    int high = arr.size() - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (key == arr[mid])
        {
            return mid;
        }
        else if (key < arr[mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return -1;
}
int main()
{
    std::vector<int> arr = {57, 68, 59, 52, 72, 28, 96, 33, 24};
    std::sort(arr.begin(), arr.end());
    PrintArr(arr);
    std::cout << " key pos is " << BinarySearch(arr, -1);
    std::cout << std::endl;
    return 0;
}
