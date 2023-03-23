/*** 
 * @FilePath: /github/harpseal/学习笔记/c++/代码片段/variadic_template.cpp
 * @Author: harpseal
 * @Date: 2023-03-17 15:05:02
 * @LastEditTime: 2023-03-17 15:06:27
 * @email: 844291270@qq.com
 */

 /*
    变参数模板
 */
#include <iostream>

void Print() {}
template <typename T, typename... Types>
void Print(T firstarg, Types... types) {
    std::cout << firstarg << std::endl;
    Print(types...);
}

int main()
{
    Print(1,2,3,"hello", "world");
    return 0;
}