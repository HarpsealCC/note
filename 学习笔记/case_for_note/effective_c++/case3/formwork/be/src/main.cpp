#include <iostream>
#include <vector>

void f1(const char* pw);
void f2(char const * pw);  // 只要不越过*,以上两种写法是一样的

// const修饰常量
void show_const_usage_outof_class() {
    // 普通类型const
    char greeting[] = "Hello";
    char* p1 = greeting;  // non-const pointer, non-const data
    const char* p2 = greeting;  // non-const pointer, const data
    char* const p3 = greeting;  // const pointer, non-const data
    const char* const p4 = greeting;  // const pointer, const data

    // 迭代器const
    std::vector<int> vec(10);
    std::cout << "size " << vec.size() << std::endl;

    const std::vector<int>::iterator iter = vec.begin();
    *iter = 10; // OK
    // ++iter; // error

    std::vector<int>::const_iterator citer = vec.begin();
    // *citer = 11; // error
    ++citer; // OK
}

// const修饰函数声明

//返回值
class Rational {};
Rational operator* (const Rational& lhs, const Rational& rhs) {
    Rational ab;
    return ab;
}

class TextBlock {
public:
    TextBlock(char* str) : text(str) {}
    const char& operator[](std::size_t postition) const {  
        return text[postition];
    }
    char& operator[](std::size_t position) {
        return  // 应当这么写
            const_cast<char&>(
                static_cast<const TextBlock&>(*this)[position]);
    }
    // char& operator[](std::size_t postition) {
    //     a = 2;  // 这会导致const接口效用消失，且不容易debuf
    //     return text[postition];
    // }
    // const char& operator[](std::size_t postition) const {
    //     // 这会导致const接口效用消失，且不容易debuf
    //     return static_cast<const char&>(const_cast<TextBlock&>(*this)[postition]);
    // }

    void print(std::size_t position) const  {
        std::cout << text[position] << std::endl;
        // a = 1;
    }
private:
    std::string text;
    int a;
};

int main(int argc, char* argv) {
    show_const_usage_outof_class();
    Rational a,b,c;
    (a*b) = c;  // 诡异的问题

    TextBlock tb("Hello");
    std::cout << tb[0] << std::endl;

    const TextBlock ctb("World");
    std::cout << ctb[0] << std::endl;
    char* pc = (char*)&ctb[0];
    *pc = 'J';
    tb.print(0);
    ctb.print(0);
    return 0;
}