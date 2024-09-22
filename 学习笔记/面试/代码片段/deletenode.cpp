/**
 * @file deletenode.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-12-07
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-12-07 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>内容
 * 面试题18 删除链表的节点
 * 题目一：在O(1)时间内删除链表的节点。
 * 给定单向链表的头指针和一个节点指针，定义一个函数在O(1)时间内删除该节点。链表节点与函数的定义如下：
 *struct ListNode {
    int       nkey;
    ListNode* pnext;
    ListNode(int key) : nkey(key), pnext(nullptr) {}
    };
    void DeleteNode(ListNode** plisthead, ListNode* ptobedeleted);
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
/**
 * @brief 如果想在O(1)时间内删除一个节点，那就不能是遍历的方法
 * @param  plisthead        My Param doc
 * @param  ptobedeleted     My Param doc
 */
void DeleteNode(ListNode** plisthead, ListNode* ptobedeleted) {
    if (plisthead == nullptr || *plisthead == nullptr ||
        ptobedeleted == nullptr) {
        return;
    }
    // 如果删除的不是最后一个节点，可以使用“覆盖”的方案
    if (ptobedeleted->pnext != nullptr) {
        // 找到被删除节点的下一个节点，使用它的值覆盖被删除的节点
        ListNode* next_node = ptobedeleted->pnext;
        ptobedeleted->nkey  = ptobedeleted->pnext->nkey;
        // 可以把下一个节点删掉了
        ptobedeleted->pnext = ptobedeleted->pnext->pnext;
        delete next_node;
        next_node = nullptr;
    } else {  // 如果是被删除的节点是最后一个节点，只能使用遍历的方案了
        // 如果头节点是就是尾节点
        if (*plisthead = ptobedeleted) {
            delete *plisthead;
            *plisthead = nullptr;
        } else {
            ListNode* plistiter = *plisthead;
            // 找到被删的节点之前的一个节点
            while (plistiter->pnext != ptobedeleted) {
                plistiter = plistiter->pnext;
            }
            delete ptobedeleted;
            ptobedeleted     = nullptr;
            plistiter->pnext = nullptr;
        }
    }
}

int main() {
    std::vector<int> arr      = {1, 2, 3, 4, 5, 6};
    ListNode*        nodelist = CreateNodeList(arr);
    DestoryNodeList(nodelist);
    return 0;
}
