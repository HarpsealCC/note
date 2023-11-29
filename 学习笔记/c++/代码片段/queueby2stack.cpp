/**
 * @file queueby2stack.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-11-29
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-11-29 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>内容
 * 面试题9 用两个栈实现队列
 * 用两个栈实现一个队列。队列的声明如下，请实现它的两个函数appendTail和deleteHead，
 * 分别完成在队列尾部插入节点和在队列头部删除节点的功能
 * </table>
 */
#include <exception>
#include <iostream>
#include <stack>
#include <vector>

class MyException : public std::exception {
public:
    explicit MyException(const std::string& errorMessage)
        : errorMessage_(errorMessage) {}

    const char* what() const noexcept override {
        return errorMessage_.c_str();
    }

private:
    std::string errorMessage_;
};
void PrintArr(const std::vector<int>& arr) {
    for (auto iter : arr) {
        std::cout << iter << " ";
    }
    std::cout << std::endl;
}

template <typename T>
class CQueue {
public:
    CQueue(void) {}
    ~CQueue(void) {}

    void AppendTail(const T& node);
    T    DeleteHead();

private:
    std::stack<T> stack1;
    std::stack<T> stack2;
};

template <typename T>
void CQueue<T>::AppendTail(const T& node) {
    this->stack1.push(node);
}

template <typename T>
T CQueue<T>::DeleteHead() {
    if (stack1.empty() && stack2.empty()) {
        throw MyException("Empty queue!");
    }
    if (stack2.empty()) {
        while (stack1.size() != 0) {
            stack2.push(stack1.top());
            stack1.pop();
        }
    }
    T ret = stack2.top();
    stack2.pop();
    return ret;
}

int main() {
    std::vector<int> arr2 = {1, 2, 3};
    std::vector<int> arr1 = {5, 6, 7};
    CQueue<int>      my_queue;
    for (auto iter : arr1) {
        my_queue.AppendTail(iter);
    }
    for (auto iter : arr2) {
        my_queue.AppendTail(iter);
    }
    for (int i = 0; i < arr1.size() + arr2.size(); i++) {
        std::cout << my_queue.DeleteHead() << " ";
    }
    std::cout << std::endl;
    return 0;
}
