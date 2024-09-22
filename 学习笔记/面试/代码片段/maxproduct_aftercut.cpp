/**
 * @file maxproduct_aftercut.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-12-03
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-12-03 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>内容
 * 面试题14 剪绳子
 * 给你一根长度为n的绳子，请把绳子剪成m段（m，n都是整数，且m > 1, n >
 * 1）,每段绳子的长度记为k[0],k[1]...k[m]。
 * 请问k[0]*k[1]*...*k[m]的最大乘积可能是多少？
 * 例如，当绳子的最大长度是8时，我们把它剪成长度为2*3*3的三段，此时最大的乘积为18
 * </table>
 */

#include <algorithm>
#include <iostream>
#include <vector>
/**
 * @brief 如果考虑递归的思想  f(n) = max(f[n-i]*f(i))  (0 < i < n)
 * 自上而下的话，使用递归是无法进行计算的，因为局部最优，不一定是全局最优
 *
 * @param  length           My Param doc
 * @return int
 */
int MaxProductAfterCuttingSolution1(int length) {
    int max = 0;
    // 先列出基本长度
    if (length <= 0) {
        return 0;
    }
    if (length == 1) {
        return 0;
    }
    if (length == 2) {
        return 1;
    }
    if (length == 3) {
        return 2;
    }
    std::vector<int> max_var(length + 1);
    // 再基于基本长度，列出几种情况下的长度
    max_var[0] = 0;
    max_var[1] = 1;
    max_var[2] = 2;
    max_var[3] = 3;
    // 继续计算一般长度时候的数值
    for (int i = 4; i <= length; i++) {
        max = 0;
        // 从短到长，逐步计算最大值
        for (int j = 1; j <= i / 2; j++) {
            max_var[i] = max_var[i - j] * max_var[j];
            if (max < max_var[i]) {
                max = max_var[i];
            }
            max_var[i] = max;
        }
    }
    max = max_var[length];
    return max;
}

int main() {
    std::cout << MaxProductAfterCuttingSolution1(8) << std::endl;
    return 0;
}