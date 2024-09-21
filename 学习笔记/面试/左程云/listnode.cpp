#include <iostream>

// 定义链表节点
struct ListNode {
    int       value;
    ListNode* next;
    ListNode(int x) : value(x), next(nullptr) {}
};

// 反转单链表函数
ListNode* reverseLinkedList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode* pre  = nullptr;
    ListNode* next = nullptr;
    while (head != nullptr) {
        next       = head->next;
        head->next = pre;
        pre        = head;
        head       = next;
    }
    return pre;
}

// 打印链表
void printList(ListNode* head) {
    ListNode* current = head;
    while (current) {
        std::cout << current->value << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

int main() {
    // 创建链表 1 -> 2 -> 3 -> 4 -> nullptr
    ListNode* head         = new ListNode(1);
    head->next             = new ListNode(2);
    head->next->next       = new ListNode(3);
    head->next->next->next = new ListNode(4);

    std::cout << "原链表:" << std::endl;
    printList(head);

    // 反转链表
    ListNode* reversedHead = reverseLinkedList(head);

    std::cout << "反转后的链表:" << std::endl;
    printList(reversedHead);

    // 释放内存
    while (reversedHead) {
        ListNode* temp = reversedHead;
        reversedHead   = reversedHead->next;
        delete temp;
    }

    return 0;
}
