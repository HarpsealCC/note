#include <iostream>
template <typename T>
void printBinary(T num) {
    for (int i = sizeof(T) * 8 - 1; i >= 0; i--) {
        std::cout << (num & ((T)1 << i) ? 1 : 0);
    }
    std::cout << std::endl;
}

int main() {
    int num = 18;
    std::cout << "Binary representation of " << num << " is: ";
    printBinary(num);  // 输出：00000000000000000000000000010010
    return 0;
}
