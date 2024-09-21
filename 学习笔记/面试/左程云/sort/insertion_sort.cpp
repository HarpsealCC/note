#include <iostream>
#include <vector>

using namespace std;

void insertion_sort(vector<int>& arr) {
    int n = arr.size();
    if (n < 2)
        return;
    //
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j >= 0; j--) {
            if (arr[j] < arr[j - 1]) {
                swap(arr[j],
                     arr[j - 1]);  // 使用交换的方式将不满足条件的数据右移
            } else {
                break;
            }
        }
    }
}

void insertion_sort_1(vector<int>& arr) {
    int n = arr.size();
    if (n < 2)
        return;
    //
    for (int i = 1; i < n; i++) {
        int key = arr[i];                 // 记录i位置的数据
        int j   = i - 1;                  // i左侧的末尾
        while (j >= 0 && arr[j] > key) {  // 循环比较j位置的数与key
            arr[j + 1] = arr[j];  // 如果比key大，就需要给key挪地方
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6};

    std::cout << "Unsorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    insertion_sort(arr);

    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}