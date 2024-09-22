/**
 * @file merge_to_list.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-12-18
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-12-18 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>内容
 * 面试题25
 * 题目：输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然时递增排序的
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

ListNode* MergeToList(ListNode* nodelist1, ListNode* nodelist2) {
    // 参数检查
    if (nodelist1 == nullptr && nodelist2 == nullptr) {
        return nullptr;
    }
    // 递归边界
    if (nodelist1 == nullptr) {
        return nodelist2;
    }
    if (nodelist2 == nullptr) {
        return nodelist1;
    }
    ListNode* mergelist = nullptr;
    if (nodelist1->nkey >= nodelist2->nkey) {
        mergelist        = nodelist2;
        mergelist->pnext = MergeToList(nodelist1, nodelist2->pnext);
    } else {
        mergelist        = nodelist1;
        mergelist->pnext = MergeToList(nodelist1->pnext, nodelist2);
    }
    return mergelist;
}

int main() {
    std::vector<int> arr1  = {1, 3, 5, 7, 9};
    std::vector<int> arr2  = {2, 4, 6, 8, 9, 10};
    ListNode*        list1 = CreateNodeList(arr1);
    ListNode*        list2 = CreateNodeList(arr2);
    ListNode*        list3 = MergeToList(list1, list2);
    while (list3 != nullptr) {
        std::cout << list3->nkey << std::endl;
        list3 = list3->pnext;
    }
}