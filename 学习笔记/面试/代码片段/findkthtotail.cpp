/**
 * @file findkthtotail.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-12-12
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-12-12 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>内容
 * 面试题22 链表中倒数第k个节点
 * 输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，
 * 本题从1开始计数，即链表的尾节点是倒数第一个节点。
 * 例如，一个链表有6个节点，从头节点开始，它们的值分别是1 2 3 4 5
 * 6。这个链表的倒数第三个节点是值为4的节点，链表节点定义如下
 *
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
/**
 * @brief 采用双指针的策略，只需要遍历一次就可以，两个指针间相距k-1
 * @param  head             My Param doc
 * @param  k                My Param doc
 * @return ListNode*
 */
ListNode* FindKthToTail(ListNode* head, uint32_t k) {
    if (head == nullptr || k == 0) {
        return nullptr;
    }
    ListNode* node1   = head;
    uint32_t  k_node1 = k - 1;  // 相距k-1
    while (k_node1) {
        k_node1--;
        node1 = node1->pnext;
        if (node1->pnext == nullptr) {  // 如果链表长度不够，需要提前return
            return nullptr;
        }
    }
    ListNode* node2 = head;
    while (node1->pnext != nullptr) {
        node1 = node1->pnext;
        node2 = node2->pnext;
    }
    return node2;
}

int main() {
    std::vector<int> arr      = {1, 2, 3, 4, 5, 6};
    ListNode*        nodelist = CreateNodeList(arr);
    ListNode*        ret      = FindKthToTail(nodelist, 2);
    std::cout << ret->nkey << std::endl;
    DestoryNodeList(nodelist);
    return 0;
}
