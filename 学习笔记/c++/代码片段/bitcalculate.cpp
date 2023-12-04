/**
 * @file bitcalculate.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-12-04
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-12-04 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>内容
 * 面试题15 二进制中1的个数
 * 题目：
 * 请实现一个函数，输入一个整数，输出该数二进制表示中1的个数。
 * 例如，把9表示成二进制是1001，有2位是1。因此，如果输入为9，则该函数输出为2
 * </table>
 */

#include <iostream>
/**
 * @brief 不能改变输入的数字，让其右移
 * @param  n                My Param doc
 * @return int
 */
int NumberOf1(int n) {
    int      count = 0;
    uint32_t flag  = 1;
    while (flag) {
        if (n & flag) {
            count++;
        }
        flag = flag << 1;
    }
    return count;
}
/**
 * @brief
 * 把一个整数减1，并与它本身&，那么这个数的最右边的1会变成0，有多少个1，就可以做多少次这个计算
 * 例如
 * 1101 --> 1101-1 = 1100  --> 1100 & 1101 = 1100 --> 1100 -1 = 1011
 * --> 1011 & 1100 = 1000
 * @param  n                My Param doc
 * @return int
 */
int Numberof1V2(int n) {
    int count = 0;

    while (n) {
        ++count;
        n = (n - 1) & n;
    }
    return count;
}
int main() {
    std::cout << NumberOf1(9) << std::endl;
    return 0;
}