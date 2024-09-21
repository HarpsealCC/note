#include <iostream>
#include <random>
#include <vector>

using namespace std;

void selection_sort(vector<int>& arr) {
    int n = arr.size();
    if (n < 2)
        return;
    //
    for (int i = 0; i < n - 1; i++) {  // n-1 用于控制 j = i+1
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        swap(arr[i], arr[min]);
    }
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6};

    std::cout << "Unsorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    selection_sort(arr);

    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}