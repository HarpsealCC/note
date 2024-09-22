#include <iostream>
#include <limits>
template<typename T>
constexpr bool isSigned = std::numeric_limits<T>::is_signed;
int main()
{
    std::cout << isSigned<uint8_t> << std::endl;
    return 0;
}