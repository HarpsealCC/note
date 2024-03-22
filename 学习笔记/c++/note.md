# 阅读记录

## <<c++ templates 第二版>>

### typedef #define与 using的区别于关系

typedef、#define 和 using 是 C++ 中用于定义类型别名和符号常量的三种不同机制，它们在功能上有所重叠，但也有一些区别。

- typedef：

typedef 用于为现有的类型创建一个新的名称。
它是 C 和 C++ 共有的特性。
可以用于定义新的类型别名，例如：typedef int Integer; 将 Integer 定义为 int 的别名。

- \#define：

\#define 是 C/C++ 预处理器指令，用于创建符号常量。
它是在预处理阶段进行文本替换的，没有类型检查，可能会导致一些问题。
例如：\#define MAX_SIZE 100 定义了一个名为 MAX_SIZE 的符号常量，其值为 100。

- using：

using 是 C++ 中引入的关键字，用于引入命名空间、声明别名等。
using 也可以用于定义类型别名，但相比于 typedef 更加灵活，并且可以用于**模板别名声明**。
例如：using Integer = int; 和 typedef int Integer; 两者功能相同，都是定义 Integer 作为 int 的别名。

#### 关系和区别：

typedef 是 C 和 C++ 中都支持的，用于定义类型别名。
\#define 是 C/C++ 预处理器指令，用于创建符号常量，没有类型信息。
using 是 C++11 引入的，用于引入命名空间、声明别名等，也可以用于定义类型别名，并且更加灵活。

### 原始数组与字符串常量变换
```
#include <iostream>

template<typename T>
struct MyClass;             // primary template

template<typename T, std::size_t SZ>
struct MyClass<T[SZ]>       // partial specialization for arrays of known bounds
{
  static void print() { std::cout << "print() for T[" << SZ << "]\n"; }
};

template<typename T, std::size_t SZ>
struct MyClass<T(&)[SZ]>    // partial spec. for references to arrays of known bounds
{
  static void print() { std::cout << "print() for T(&)[" << SZ << "]\n"; }
};

template<typename T>
struct MyClass<T[]>         // partial specialization for arrays of unknown bounds
{
  static void print() { std::cout << "print() for T[]\n"; }
};

template<typename T>
struct MyClass<T(&)[]>      // partial spec. for references to arrays of unknown bounds
{
  static void print() { std::cout << "print() for T(&)[]\n"; }
};

template<typename T>
struct MyClass<T*>          // partial specialization for pointers
{
  static void print() { std::cout << "print() for T*\n"; }
};

=====================

#include "arrays.hpp"

template<typename T1, typename T2, typename T3>
void foo(int a1[7], int a2[],    // pointers by language rules
         int (&a3)[42],          // reference to array of known bound
         int (&x0)[],            // reference to array of unknown bound
         T1 x1,                  // passing by value decays
         T2& x2, T3&& x3)        // passing by reference
{
  MyClass<decltype(a1)>::print();     // uses MyClass<T*>
  MyClass<decltype(a2)>::print();     // uses MyClass<T*>
  MyClass<decltype(a3)>::print();     // uses MyClass<T(\&)[SZ]>
  MyClass<decltype(x0)>::print();     // uses MyClass<T(\&)[]>
  MyClass<decltype(x1)>::print();     // uses MyClass<T*>
  MyClass<decltype(x2)>::print();     // uses MyClass<T(\&)[]>
  MyClass<decltype(x3)>::print();     // uses MyClass<T(\&)[]>
}

int main()
{
  int a[42];
  MyClass<decltype(a)>::print();      // uses MyClass<T[SZ]>

  extern int x[];                     // forward declare array
  MyClass<decltype(x)>::print();      // uses MyClass<T[]>

  foo(a, a, a, x, x, x, x);
}

```