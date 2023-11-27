/**
 * @file replace_blank.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-11-27
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-11-27 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>第5题： 替换空格
 * 题目：请实现一个函数，把字符串中的每个空格替换成"%20"。例如，输入"We are
 * happy.", 则输出 "We%20are%20happy."。
 * </table>
 */

#include <cstring>
#include <iostream>
void ReplaceBlank(char str[], int length) {
    if (str == nullptr || length <= 0) {
        return;
    }
    int blank_num = 0;
    for (int i = 0; i < length; i++) {
        if (str[i] == ' ') {
            blank_num++;
        }
    }
    if (blank_num == 0) {
        std::cout << str << std::endl;
        return;
    }
    int   length_replace          = length + 2 * blank_num + 1;
    char* str_replace             = new char[length_replace];
    str_replace[--length_replace] = '\0';
    for (int i = 1; i <= length; i++) {
        if (str[length - i] == ' ') {
            str_replace[--length_replace] = '0';
            str_replace[--length_replace] = '2';
            str_replace[--length_replace] = '%';
        } else {
            str_replace[--length_replace] = str[length - i];
        }
    }
    std::cout << str_replace << std::endl;
    delete[] str_replace;
}

int main() {
    char str[] = "We are happy";
    ReplaceBlank(str, strlen(str));
    // 无空格字符串
    char str1[] = "wearehappy";
    ReplaceBlank(str1, strlen(str1));
    // 有连续空格的字符串
    char str2[] = "w   ppy";
    ReplaceBlank(str2, strlen(str2));
    // 空字符串
    char str3[] = "";
    ReplaceBlank(str3, strlen(str3));
    // 只有一个空格的字符串
    char str4[] = " ";
    ReplaceBlank(str4, strlen(str4));
    return 0;
}