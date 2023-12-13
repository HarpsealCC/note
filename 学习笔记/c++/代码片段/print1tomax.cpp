/**
 * @file print1tomax.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-12-06
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-12-06 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>内容
 * 面试题17
 * 输入数字你，按顺序打印出从1到最大的n位十进制数，比如输入3，则打印出1，2，3一直到999
 * </table>
 */

#include <cstring>
#include <exception>
#include <iostream>
#include <vector>
/**
 * @brief 打印函数需要注意字符串的前导0的过滤
 * @param  num              My Param doc
 */
void PrintNumber(char* num) {
    if (num == nullptr) {
        return;
    }
    bool is0head = true;
    int  len     = strlen(num);
    for (int i = 0; i < len; i++) {
        if (num[i] != '0')
            is0head = false;
        if (!is0head) {
            printf("%c", num[i]);
        }
    }
    printf("\t");
}
/**
 * @brief 使用递归的思想，核心是模拟数字的全排列
 * @param  number           My Param doc
 * @param  length           My Param doc
 * @param  index            My Param doc
 */
void Print1ToMaxCore(char* number, int length, int index) {
    if (index == length - 1) {
        PrintNumber(number);
        return;
    }
    for (int i = 0; i < 10; i++) {
        number[index + 1] = '0' + i;
        Print1ToMaxCore(number, length, index + 1);
    }
}
void Print1toMaxOfDigits(int n) {
    if (n <= 0) {
        return;
    }
    char* number = new char[n + 1];
    number[n]    = '\0';

    for (int i = 0; i < 10; i++) {
        number[0] = '0' + i;
        Print1ToMaxCore(number, n, 0);
    }
}

int main() {
    Print1toMaxOfDigits(3);
    return 0;
}