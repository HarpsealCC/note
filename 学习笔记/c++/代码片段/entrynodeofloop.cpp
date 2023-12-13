/**
 * @file entrynodeofloop.cpp
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
 * 面试题23： 链表中环的入口节点
 * 如果一个链表中包含环，如何找出环的入口节点？
 * </table>
 */

#include <iostream>
#include <vector>

struct ListNode {
    int       nkey;
    ListNode* pnext;
    ListNode(int key) : nkey(key), pnext(nullptr) {}
};

ListNode* MeetingNode(ListNode* phead) {
    if (phead == nullptr) {
        return nullptr;
    }
    ListNode* node1 = phead->pnext;
    if (node1 == nullptr) {
        return nullptr;
    }
    ListNode* node2 = node1->pnext;
    if (node2 == nullptr) {
        return nullptr;
    }
    while (node1 != nullptr && node2 != nullptr) {
        if (node1 == node2) {
            return node1;
        }
        node1 = node1->pnext;
        node2 = node2->pnext;
        if (node2 != nullptr) {
            node2 = node2->pnext;
        }
    }
    return nullptr;
}

ListNode* EntryNodeOfLoop(ListNode* phead) {
    ListNode* meetingnode = MeetingNode(phead);
    if (meetingnode == nullptr) {
        return meetingnode;
    }
    int       cycle_num       = 1;  // 记录环中节点的数量
    ListNode* meetingnode_bak = meetingnode;
    meetingnode               = meetingnode->pnext;
    while (meetingnode_bak != meetingnode) {
        cycle_num++;
        meetingnode = meetingnode->pnext;
    }

    ListNode* pnode1 = phead;
    // 先移动node1，次数为环中节点的数目
    for (int i = 0; i < cycle_num; i++) {
        pnode1 = pnode1->pnext;
    }
    ListNode* pnode2 = phead;
    while (pnode1 != pnode2) {
        pnode1 = pnode1->pnext;
        pnode2 = pnode2->pnext;
    }
    return pnode1;
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
    ListNode* tail      = head;
    ListNode* loop_head = nullptr;
    while (tail->pnext != nullptr) {
        tail = tail->pnext;
        if (tail->nkey == 5) {
            loop_head = tail;
        }
    }
    tail->pnext = loop_head;
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

    ListNode* ret = EntryNodeOfLoop(nodelist);

    std::cout << ret->nkey << std::endl;
    return 0;
}