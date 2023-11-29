/**
 * @file build_tree.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-11-28
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-11-28 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>内容
 * 面试题7 ：重建二叉树
 * 输入某二叉树的前序遍历与中序遍历的结果，请重建该二叉树，假设输入的前序与中序遍历结果都不含有重复的数字
 * 前序遍历序列{1，2，3，7，3，5，6，8} 中序遍历的序列{4，7，2，1，5，3，8，6}
 * 重建该二叉树并输出头节点
 * 面试题8 ：二叉树的下一个节点
 * 给定一个二叉树和其中的一个节点，如何找出中序遍历序列的下一个节点？
 * 树中的节点除了有两个分别指向左右子节点的指针
 * 还有一个指向父节点的指针
 * BinaryTreeNode* GetNext(BinaryTreeNode* pnode)
 * </table>
 */

#include <exception>
#include <iostream>
#include <queue>

struct BinaryTreeNode {
    int             value;
    BinaryTreeNode* pleft;
    BinaryTreeNode* pright;
    BinaryTreeNode* pparent;
    BinaryTreeNode()
        : value(0), pleft(nullptr), pright(nullptr), pparent(nullptr) {}
    BinaryTreeNode(int mvalue)
        : value(mvalue), pleft(nullptr), pright(nullptr), pparent(nullptr) {}
};
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

// 格式化输出二叉树
void PrintBinaryTree(BinaryTreeNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }

    std::queue<BinaryTreeNode*> nodeQueue;
    nodeQueue.push(pRoot);

    while (!nodeQueue.empty()) {
        int levelSize = nodeQueue.size();

        for (int i = 0; i < levelSize; ++i) {
            BinaryTreeNode* pnode = nodeQueue.front();
            nodeQueue.pop();

            // 输出节点的值
            std::cout << pnode->value;

            // 如果有左子节点，则将左子节点加入队列
            if (pnode->pleft) {
                nodeQueue.push(pnode->pleft);
            }

            // 如果有右子节点，则将右子节点加入队列
            if (pnode->pright) {
                nodeQueue.push(pnode->pright);
            }

            if (!nodeQueue.empty()) {
                std::cout << " ";
            }
        }

        std::cout << std::endl;
    }
}

BinaryTreeNode* ReBuildBinaryTreeCore(int* preorder_start,
                                      int* preorder_end,
                                      int* inorder_start,
                                      int* inorder_end) {
    // 前序遍历的第一个节点就是根节点
    int             root_value = preorder_start[0];
    BinaryTreeNode* root       = new BinaryTreeNode(root_value);
    // 前序遍历只剩一个节点，可能就是叶节点
    if (preorder_start == preorder_end) {
        // 如果中序遍历也是只剩一个节点,那就是叶节点
        if (inorder_start == inorder_end && *inorder_start == *preorder_start) {
            return root;
        } else {
            throw MyException("Invalid input");
        }
    }
    // 进行中序遍历
    // 首先需要根据前序遍历的根节点的值，确认在中序遍历中的位置
    int* inoder_iter = inorder_start;
    while (inoder_iter != inorder_end) {
        if (*inoder_iter == root_value) {
            break;
        } else {
            inoder_iter++;
        }
    }
    if (inoder_iter == inorder_end && *inoder_iter != root_value) {
        throw MyException("Invalid input");
    }
    // 在找到值的位置之后，需要根据位置计算左右子树的长度，并进行递归调用
    int left_tree_length = inoder_iter - inorder_start;
    if (left_tree_length > 0) {
        // 构建左子树
        root->pleft = ReBuildBinaryTreeCore(
            preorder_start + 1, preorder_start + left_tree_length,
            inorder_start, inorder_start + left_tree_length - 1);
    }
    int right_tree_length = inorder_end - inoder_iter;
    if (right_tree_length > 0) {
        // 构建右子树
        root->pright =
            ReBuildBinaryTreeCore(preorder_start + left_tree_length + 1,
                                  preorder_end, inoder_iter + 1, inorder_end);
    }
    return root;
}

BinaryTreeNode* ReBuildBinaryTree(int* preorder, int* inorder, int length) {
    if (preorder == nullptr || inorder == nullptr || length <= 0) {
        return nullptr;
    }
    return ReBuildBinaryTreeCore(preorder, preorder + length - 1, inorder,
                                 inorder + length - 1);
}

BinaryTreeNode* GetNext(BinaryTreeNode* pnode) {
    if (pnode == nullptr) {
        return nullptr;
    }
    BinaryTreeNode* pnext = nullptr;
    // 如果一个节点有右子树，那么它的下一个节点就是右子树的最左节点
    if (pnode->pright != nullptr) {
        BinaryTreeNode* pright = pnode->pright;
        while (pright->pleft != nullptr) {
            pright = pright->pleft;
        }
        pnext = pright;
    } else if (pnode->pparent != nullptr) {
        // 如果一个节点没有右子树，而且它是它的父节点的左子节点，那它的下一个节点就是它的父节点
        if (pnode->pparent->pleft == pnode) {
            pnext = pnode->pparent;
        } else {
            // 如果它是父节点的右子节点，就需要一直向父节点回溯，直到有一个节点是它的父节点的左节点，它的父节点就是下一个节点
            while (pnode->pparent != nullptr) {
                if (pnode->pparent->pleft == pnode) {
                    pnext = pnode->pparent;
                    break;
                } else {
                    pnode = pnode->pparent;
                }
            }
            // 直到根节点都没有找到，那该节点就是中序遍历的最后一个节点了
            // return nullptr
        }
    }
    return pnext;
}

int main() {
    int             preorder[] = {1, 2, 4, 7, 3, 5, 6, 8};
    int             inorder[]  = {4, 7, 2, 1, 5, 3, 8, 6};
    BinaryTreeNode* proot =
        ReBuildBinaryTree(preorder, inorder, sizeof(inorder) / sizeof(int));
    PrintBinaryTree(proot);
    return 0;
}