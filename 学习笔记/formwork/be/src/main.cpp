#include <iostream>
#include <limits>
#include <cstring>

const __int128_t INT128_MIN_VALUE = (__int128_t)1 << 127;
const __int128_t INT128_MAX_VALUE = -(INT128_MIN_VALUE + 1);
std::ostream& operator<<(std::ostream& os, __int128_t T) {
    if (T<0) os<<"-";if (T>=10 ) os<<T/10;if (T<=-10) os<<(-(T/10));
    return os<<( (int) (T%10) >0 ? (int) (T%10) : -(int) (T%10) ) ;
}
class B {
public:
void print_func (const int64_t a) {
    std::cout << "B" << a << std::endl;
}

};
class A {
public:
static void print_func (B b) {
    b.print_func(12);
}
};

int main() {
//    __int128_t a = std::numeric_limits<__int128_t>::min();
    // __int128_t val = -1 - ((__int128_t)1 << 127);
    // std::cout << " " <<  INT128_MIN_VALUE << std::endl;
    // std::cout << " " <<  val << std::endl;
    B b;
    int a = 12;
    A::print_func(b);
    return 0;
}
