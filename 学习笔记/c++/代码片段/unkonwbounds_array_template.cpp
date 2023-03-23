/*** 
 * @FilePath: /github/harpseal/学习笔记/c++/代码片段/unkonwbounds_array_template.cpp
 * @Author: harpseal
 * @Date: 2023-03-20 15:18:54
 * @LastEditTime: 2023-03-20 15:18:55
 * @email: 844291270@qq.com
 */


#include <iostream>

template <typename T>
struct MyClass;
template <typename T, std::size_t SZ>
struct MyClass<T[SZ]> {
    static void print() {
        std::cout << "print() for T[" << SZ << "]\n";
    }
};
template <typename T, std::size_t SZ>
struct MyClass<T(&)[SZ]> {
    static void print () {
        std::cout << "print() for T(&)[ " << SZ << "]\n";
    }
};
template <typename T>
struct MyClass<T[]> {
    static void print() {
        std::cout << "print() for T[]\n";
    }
};
template <typename T>
struct MyClass<T(&)[]> {
    static void print() {
        std::cout << "print() for T(&)[]\n";
    }
};
template <typename T>
struct MyClass<T*> {
    static void print() {
        std::cout << "print() for T*\n";
    }
};


template <typename T1, typename T2, typename T3>
void foo(int a1[7],int a2[],  // pointers by language rules
        int (&a3)[42],  // reference to array of known bound
        int (&x0)[],  // reference to array of unknown bound
        T1 x1,  // passing by value decays
        T2& x2, T3&& x3) {  // passing by reference
    MyClass<decltype(a1)>::print();  // use MyClass<T*>
    MyClass<decltype(a2)>::print();  // use MyClass<T*> a1, a2 退化成指针
    MyClass<decltype(a3)>::print();  // use MyClass<T(&) [SZ]>
    MyClass<decltype(x0)>::print();  // use MyClass<T(&) []>
    MyClass<decltype(x1)>::print();  // use MyClass<T*>
    MyClass<decltype(x2)>::print();  // use MyClass<T(&) []>
    MyClass<decltype(x3)>::print();  // use MyClass<T(&) []>  // 万能引用,引用折叠
}
int main()
{
    int a[42];
    MyClass<decltype(a)>::print();  // use MyClass<T[SZ]>
    extern int x[]; // forword declare array
    MyClass<decltype(x)>::print();  // use MyClass<T[]>
    foo(a, a, a, x, x, x, x);
    return 0;
}

int x[] = {0, 8, 15};  // define forward-declared array