/**
 * @file reverselist.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-12-13 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>内容
 * 面试题24 反转链表
 * 定义一个函数，输入一个链表的头节点，反转该链表并输出反转后的链表的头节点
 * </table>
 */

#include <iostream>
#include <vector>

struct ListNode {
    int       nkey;
    ListNode* pnext;
    ListNode(int key) : nkey(key), pnext(nullptr) {}
};
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

ListNode* ReverseList(ListNode* phead) {
    if (phead == nullptr) {
        return nullptr;
    }
    if (phead->pnext == nullptr) {
        return phead;
    }
    ListNode* pbefore = phead;
    ListNode* pcur    = phead->pnext;
    ListNode* pafter  = pcur->pnext;

    while (pcur->pnext != nullptr) {
        pcur->pnext = pbefore;
        pbefore     = pcur;
        pcur        = pafter;
        pafter      = pafter->pnext;
    }
    pcur->pnext  = pbefore;
    phead->pnext = nullptr;
    return pcur;
}

int main() {
    std::vector<int> arr      = {1, 2, 3, 4, 5, 6};
    ListNode*        nodelist = CreateNodeList(arr);
    ListNode*        ret      = ReverseList(nodelist);
    while (ret != nullptr) {
        std::cout << ret->nkey << std::endl;
        ret = ret->pnext;
    }
    return 0;
}