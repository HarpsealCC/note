/**
 * @file fibonacci.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-11-30
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-11-30 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>内容
 * 面试题10 斐波那契数列
 * 题目一 求斐波那契数列的第n项
 * 写一个函数，输入n，求斐波那契数列的第n项，斐波那契数列定义如下
 *       |0              (n=0)
 * f(n)= |1              (n=1)
 *       |f(n-1)+f(n-2)  (n>1)
 *
 * 题目二：青蛙跳台阶问题
 * 一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个n级的台阶共有多少中跳法
 * 分析，如果有一个台阶，就只有一个跳法，如果有2个台阶，就有两个跳法，
 * 那就是初值为（1，2）的Fibonacci函数了
 * </table>
 */

#include <iostream>

// 递归实现太慢
long long Fibonacci(uint32_t num) {
    if (num == 0) {
        return 0;
    } else if (num == 1) {
        return 1;
    } else {
        return Fibonacci(num - 1) + Fibonacci(num - 2);
    }
}
// 存中间值比较快，面试时候需要使用这个
long long FibonacciV2(uint32_t num) {
    if (num < 2) {
        return num;
    }
    long long result1 = 0;
    long long result2 = 1;
    long long result3;
    for (uint32_t i = 2; i <= num; i++) {
        result3 = result1 + result2;
        result1 = result2;
        result2 = result3;
    }
    return result3;
}

int main() {
    std::cout << FibonacciV2(50) << std::endl;  // 12586269025
    return 0;
}