/**
 * @file power.cpp
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
 * 面试题 16 ： 数值的整数次方
 * 题目：实现函数double Power(double base, int exponent) ,求base
 * 的exponent次方。 不得使用库函数，同时不需要考虑大数问题
 * </table>
 */
#include <algorithm>
#include <cmath>
#include <iostream>

double PowerWithUnSignedExp(double base, int exponent) {
    double result = base;
    for (int i = 1; i < exponent; i++) {
        result *= base;
    }
    return result;
}
/**
 * @brief 也可使用递归的思想实现乘方的计算
 *       | a(n/2) * a(n/2)   [n为偶数]
 *a(n) = | a((n-1)/2) * a((n-1)/2)* a [n为奇数]
 * @param  base             My Param doc
 * @param  exponent         My Param doc
 * @return double
 */
double PowerWithUnSignedExpV2(double base, int exponent) {
    if (exponent == 0) {
        return 0;
    }
    if (exponent == 1) {
        return base;
    }
    double result = 0.0;

    if (exponent & 0x01) {  // 奇数
        result = PowerWithUnSignedExpV2(base, (exponent - 1) >> 1);
        result *= result;
        result *= base;
    } else {  // 偶数
        result = PowerWithUnSignedExpV2(base, exponent >> 1);
        result *= result;
    }

    return result;
}

double Power(double base, int exponent) {
    if (exponent == 0) {
        if (base == 0) {
            return 0;
        }
        return 1;
    }
    if (exponent == 1) {
        return base;
    }
    uint32_t unsigned_exponent = 0;
    if (exponent < 0) {
        if (base == 0) {
            return 0;  // 未被定义的行为
        }
        unsigned_exponent = -(exponent);
    } else {
        unsigned_exponent = exponent;
    }
    double result = PowerWithUnSignedExpV2(base, unsigned_exponent);
    if (exponent < 0) {
        result = 1.0 / result;
    }
    return result;
}

int main() {
    std::cout << Power(2.5, 11) << " " << pow(2.5, 11) << std::endl;
    return 0;
}