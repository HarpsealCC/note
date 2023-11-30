/**
 * @file findpath.cpp
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
 * 面试题12：矩阵中的路径 (需要多加练习)
 * 题目：请设计一个函数，用来判断在一个矩阵中是否存在一条包含字符串所有字符的路径。
 * 路径可以从矩阵中的任意一个格开始，每一步都可以在矩阵中向左右上下移动一格。如果
 * 一条路径经过了矩阵中的某一格，那么该路径不能再次进入该格子。
 * a b t g
 * c f c s
 * j d e h
 * </table>
 */

#include <cstring>
#include <iostream>

bool HasPathCore(char* matrix,
                 int   cols,
                 int   rows,
                 char* str,
                 int   col,
                 int   row,
                 int&  pathlength,
                 bool* visited) {
    if (str[pathlength] == '\0') {
        return true;
    }
    bool haspath = false;
    if (col >= 0 && col <= cols && row >= 0 && row < rows &&
        matrix[row * cols + col] == str[pathlength] &&
        !visited[row * cols + col]) {
        visited[row * cols + col] = true;
        pathlength++;
        haspath = HasPathCore(matrix, cols, rows, str, col + 1, row, pathlength,
                              visited) ||
                  HasPathCore(matrix, cols, rows, str, col, row + 1, pathlength,
                              visited) ||
                  HasPathCore(matrix, cols, rows, str, col - 1, row, pathlength,
                              visited) ||
                  HasPathCore(matrix, cols, rows, str, col, row - 1, pathlength,
                              visited);
        if (!haspath) {
            visited[row * cols + col] = false;
            pathlength--;
        }
    }
    return haspath;
}

bool HasPath(char* matrix, int cols, int rows, char* str) {
    if (matrix == nullptr || cols <= 0 || rows <= 0 || str == nullptr) {
        return false;
    }
    bool* visited = new bool[cols * rows];
    memset(visited, 0, cols * rows);
    int pathlength = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (HasPathCore(matrix, cols, rows, str, col, row, pathlength,
                            visited)) {
                return true;
            }
        }
    }
    delete[] visited;
    return false;
}

int main() {
    char str[]    = "bfcc";
    char matrix[] = "abtgcfcsjdeh";
    std::cout << std::boolalpha << " " << HasPath(matrix, 4, 3, str)
              << std::endl;
    return 0;
}