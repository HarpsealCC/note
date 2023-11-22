/**
 * @file quick_sort.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-11-20
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-11-20 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>本文件用于练习快速排序的编码
 * (1) 实现普通的快速排序，可以使用第一个，最后一个数组元素作为key值
 * (2) 使用三数取中法进行优化
 * (3) 可以不使用递归实现快排
 * </table>
 */
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void Swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
void PrintArr(const std::vector<int> &arr)
{
    for (auto iter : arr)
    {
        std::cout << iter << " ";
    }
    std::cout << std::endl;
}
/**
 * @brief 以数组中第一个数为key，进行分组排序
 * 要点：
 * 当使用第一个数key，此位置就必须不参与后续的比较，仅在所有元素遍历之后，将其与小于key组的最后一个数据进行交换
 * 这样可以保证key值交换之后，key左边的都是小于（等于）key的值
 * @param  arr              待排数组
 * @param  low              数组起始下标
 * @param  high             数组终止下标
 * @return int key值排序后在数组中的下标
 */
int PartitionBeginKey(vector<int> &arr, int low, int high)
{
    int key = arr[low];
    int start_pos = low;
    for (int end_pos = low + 1; end_pos <= high; end_pos++)
    {
        if (arr[end_pos] < key)
        {
            start_pos++;
            Swap(arr[start_pos], arr[end_pos]);
        }
    }
    Swap(arr[start_pos], arr[low]);
    return start_pos;
}
/**
 * @brief 以数组中最后数为key，进行分组排序
 * 要点：同PartitionBeginKey，注意最后的key
 * @param  arr              待排数组
 * @param  low              数组起始下标
 * @param  high             数组终止下标
 * @return int key值排序后在数组中的下标
 */
int PartitionEndKey(vector<int> &arr, int low, int high)
{
    int key = arr[high];
    int start_pos = low;
    for (int end_pos = low; end_pos < high; end_pos++)
    {
        if (arr[end_pos] < key)
        {
            Swap(arr[start_pos], arr[end_pos]);
            start_pos++;
        }
    }
    swap(arr[start_pos], arr[high]);
    return start_pos;
}

/**
 * @brief ChoosePivot需要实现 low < mid < high
 *        最后要swap low 与 mid，也可以在快排中进行swap
 * @param  arr              待排数组
 * @param  low              数组起始下标
 * @param  high             数组终止下标
 */
void ChoosePivot(vector<int> &arr, int low, int high)
{
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[high])
    {
        Swap(arr[low], arr[high]);
    }
    if (arr[low] > arr[mid])
    {
        Swap(arr[low], arr[mid]);
    }
    if (arr[mid] > arr[high])
    {
        Swap(arr[high], arr[mid]);
    }
    // 此时arr[low] <= arr[mid] <= arr[high]
    Swap(arr[low], arr[mid]);
}
/**
 * @brief 使用ChoosePivot选择之后，low所在表示的值为选择之后的值，使用PartitionBeginKey排序
 */
int PartitionChoosePivot(vector<int> &arr, int low, int high)
{
    ChoosePivot(arr, low, high);
    return PartitionBeginKey(arr, low, high);
}

void quick_sort_func(std::vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int index = PartitionBeginKey(arr, low, high);
        quick_sort_func(arr, low, index - 1);
        quick_sort_func(arr, index + 1, high);
    }
}
/**
 * @brief 如果不用递归来做的话，其实可以使用stack来模拟一个递归出来，就是把每次计算的index存起来，循环计算
 * 本质上还是个递归
 */
void quick_sort_func_stack(std::vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        std::stack<std::pair<int, int>> index_stack;

        index_stack.push(std::make_pair(low, high));
        while (!index_stack.empty())
        {
            int start_pos = index_stack.top().first;
            int end_pos = index_stack.top().second;
            index_stack.pop();
            int index = PartitionBeginKey(arr, start_pos, end_pos);
            if (index - 1 > start_pos)
            {
                index_stack.push(std::make_pair(start_pos, index - 1));
            }
            if (index + 1 < end_pos)
            {
                index_stack.push(std::make_pair(index + 1, end_pos));
            }
        }
    }
}
int main()
{
    std::vector<int> arr = {57, 68, 59, 52, 72, 28, 96, 33, 24};
    PrintArr(arr);
    quick_sort_func_stack(arr, 0, arr.size() - 1);
    PrintArr(arr);
    return 0;
}