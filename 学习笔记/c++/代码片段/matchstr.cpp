/**
 * @file matchstr.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-12-09
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-12-09 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>内容
 * 面试题 19 正则表达式匹配
 * 题目：请实现一个函数用来匹配包含'.'和'*'的正则表达式，模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以
 * 出现任意次（含0次）。在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串“aaa”与模式
 * "a.a"和"ab*ac*a"匹配 但是与"aa.a"和"ab*a"均不匹配
 * </table>
 */

#include <iostream>

bool MatchCore(char* str, char* pattern) {
    if (*str == '\0' && *pattern == '\0') {
        return true;
    }
    if (*str != '\0' && *pattern == '\0') {
        return false;
    }

    if (*(pattern + 1) == '*') {
        if (*pattern == *str || (*pattern == '.' && *str != '\0')) {
            return MatchCore(str + 1, pattern + 2) ||
                   MatchCore(str + 1, pattern) || MatchCore(str, pattern + 2);
        } else {
            return MatchCore(str, pattern + 2);
        }
    }
    if (*pattern == *str || (*pattern == '.' && *str != '\0')) {
        return MatchCore(str + 1, pattern + 1);
    }
    return false;
}

bool Match(char* str, char* pattern) {
    if (str == nullptr || pattern == nullptr) {
        return false;
    }
    return MatchCore(str, pattern);
}

int main() {
    char* str    = "aaa";
    char* patter = "ab*aa";
    std::cout << std::boolalpha << Match(str, patter) << std::endl;
}