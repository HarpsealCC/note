/*** 
 * @FilePath: /github/harpseal/学习笔记/c++/代码片段/typename.cpp
 * @Author: harpseal
 * @Date: 2023-03-17 11:06:10
 * @LastEditTime: 2023-03-17 11:26:06
 * @email: 844291270@qq.com
 */
/*  1、使用vscode cmake工具进行编译
    2、set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17") 使用 c++17 进行编译 */

#include <iostream>
#include <string_view>
#include <cstring>
#include <algorithm>

template <typename T>
constexpr auto type_name() {
    std::string_view name, prefix, suffix;
#ifdef __clang__
    name = __PRETTY_FUNCTION__;
    prefix = "auto type_name() [T = ";
    suffix = "]";
#elif defined(__GNUC__)
    name = __PRETTY_FUNCTION__;
    prefix = "constexpr auto type_name() [with T = ";
    suffix = "]";
#elif defined(_MSC_VER)
    name = __FUNCSIG__;
    prefix = "auto __cdecl type_name<";
    suffix = ">(void)";
#endif
    name.remove_prefix(prefix.size());
    name.remove_suffix(suffix.size());
    return name;
}

int main() {
    int a;
    std::cout << type_name<decltype(a)>() << std::endl;
}