/**
 * @file isnumberic.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-12-10
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-12-10 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>内容
 * 面试题20： 表示数值的字符串
 * 题目：请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，字符串"+100"，"5e2","3.1415"及"-1E-16"都表示数值
 * 但是"12e","1a3.14","1.2.3","+-5"及"12e+5,4"都不是
 * </table>
 */

#include <iostream>

bool ScanUnsignedInterger(const char** str) {
    const char* before = *str;
    // 查找出第一个非0-9字符的位置
    while (**str != '\0' && **str >= '0' && **str <= '9') {
        ++(*str);
    }
    return *str > before;
}

bool ScanInteger(const char** str) {
    if (**str == '+' || **str == '-') {
        ++(*str);
    }
    return ScanUnsignedInterger(str);
}

/**
 * @brief
 * 数字的格式可以用A.[B][e|EC]或者.B[e|EC]表示，其中AC是整数（有无符号均可），B是一个无符号的整数
 * @param  str              My Param doc
 * @return true
 * @return false
 */
bool IsNumberic(const char* str) {
    if (str == nullptr) {
        return false;
    }
    // 找到str中第一个不是0-9字符之前的位置(str会移动)
    bool is_num = ScanInteger(&str);
    if (*str == '.') {
        ++str;
        // 下面代码用||的原因
        // 1. 小数可以没有整数部分
        // 2. 小数点后可以没有整数部分
        // 3. 当然，小数前后都可以有整数部分
        is_num = ScanUnsignedInterger(&str) || is_num;
    }
    // 如果出现e|E,则接下来是指数部分
    if (*str == 'e' || *str == 'E') {
        ++str;
        // 下面代码用&&的原因
        // 1. 当e|E前面没有数字时，整个字符串不能表示数字
        // 2. 当e|E后面没有整数时，整个字符串不能表示数字
        is_num = ScanInteger(&str) && is_num;
    }
    // 如果含有其他非法字符的话，str不会等于'\0'
    return is_num && *str == '\0';
}

int main() {
    std::cout << std::boolalpha << IsNumberic("3.1415") << std::endl;
}