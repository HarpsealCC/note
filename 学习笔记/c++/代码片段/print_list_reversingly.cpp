/**
 * @file print_list_reversingly.cpp
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
 * <td>练习题6 从尾到头打印链表
 * 题目：
 *输入一个链表的头节点，从尾到头反过来打印出每个节点的值，链表节点定义如下:
    struct ListNode {
        int       nkey;
        ListNode* pnext;
    }
 * </table>
 */

#include <iostream>
#include <vector>
struct ListNode {
    int       nkey;
    ListNode* pnext;
    ListNode(int key) : nkey(key), pnext(nullptr) {}
};
void PrintListReversinglyItor(ListNode* node) {
    if (node->pnext == nullptr) {
        std::cout << node->nkey << std::endl;
    } else {
        PrintListReversinglyItor(node->pnext);
        std::cout << node->nkey << std::endl;
    }
}
void PrintListReversingly(ListNode* head) {
    if (head == nullptr) {
        return;
    }
    PrintListReversinglyItor(head);
}
ListNode* CreateNodeList(std::vector<int>& node_values) {
    ListNode* node = nullptr;
    ListNode* head = nullptr;
    for (auto iter : node_values) {
        ListNode* new_node = new ListNode(iter);
        if (head == nullptr) {
            head = new_node;
            node = new_node;
        } else {
            node->pnext = new_node;
            node        = node->pnext;
        }
    }
    return head;
}
void DestoryNodeList(ListNode* head) {
    if (head == nullptr) {
        return;
    }
    while (head != nullptr) {
        ListNode* node = head;
        head           = head->pnext;
        delete node;
    }
}
int main() {
    std::vector<int> arr      = {1, 2, 3, 4, 5, 6};
    ListNode*        nodelist = CreateNodeList(arr);
    PrintListReversingly(nodelist);
    DestoryNodeList(nodelist);
    return 0;
}
