#include <iostream>
#include <vector>

using namespace std;

void bubble_sort(vector<int>& arr) {
    int n = arr.size();
    if (n < 2)
        return;
    // 内部循环从第一个数开始，循环向后比较，如果大于后面的数字，就交换，保证末尾数最大
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 优化版本
void bubble_sort_optim(vector<int>& arr) {
    int n = arr.size();
    if (n < 2)
        return;
    // 用于表示是否发生交换
    bool swapped = false;
    for (int i = n - 1; i >= 0; i--) {
        swapped = false;
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // 某次内部循环没有发生交换，就认为已经全部排好序可以提前结束循环
        if (!swapped) {
            break;
        }
    }
}

int main() {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

    std::cout << "Unsorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    bubble_sort_optim(arr);

    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}