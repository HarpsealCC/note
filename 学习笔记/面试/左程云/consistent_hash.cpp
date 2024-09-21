#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class ConsistentHash {
public:
    // 构造函数，指定虚拟节点数量
    ConsistentHash(int numOfReplicas) : numOfReplicas_(numOfReplicas) {}

    // 添加一个节点
    void addNode(const std::string& node) {
        for (int i = 0; i < numOfReplicas_; ++i) {
            // 生成虚拟节点的哈希值，并插入到哈希环中
            size_t hash     = hashFunction_(node + std::to_string(i));
            hashRing_[hash] = node;
        }
    }

    // 删除一个节点
    void removeNode(const std::string& node) {
        for (int i = 0; i < numOfReplicas_; ++i) {
            // 根据虚拟节点的哈希值从哈希环中移除
            size_t hash = hashFunction_(node + std::to_string(i));
            hashRing_.erase(hash);
        }
    }

    // 根据数据的 key 获取应该存储的节点
    std::string getNode(const std::string& key) const {
        if (hashRing_.empty()) {
            return "";
        }
        // 计算 key 的哈希值
        size_t hash = hashFunction_(key);
        // 找到第一个不小于该哈希值的节点
        auto it = hashRing_.lower_bound(hash);
        // 如果超出哈希环的范围，取第一个节点（形成环）
        if (it == hashRing_.end()) {
            it = hashRing_.begin();
        }
        return it->second;  // 返回节点名称
    }

    // 打印哈希环信息（用于调试）
    void printHashRing() const {
        for (const auto& entry : hashRing_) {
            std::cout << entry.first << " -> " << entry.second << std::endl;
        }
    }

private:
    std::map<size_t, std::string>
        hashRing_;       // 哈希环，键是哈希值，值是节点名称
    int numOfReplicas_;  // 每个节点的虚拟节点数量
    std::hash<std::string> hashFunction_;  // 哈希函数
};

// 测试代码
int main() {
    // 创建一致性哈希对象，虚拟节点数为 3
    ConsistentHash consistentHash(3);

    // 添加节点
    consistentHash.addNode("NodeA");
    consistentHash.addNode("NodeB");
    consistentHash.addNode("NodeC");

    // 打印当前的哈希环
    std::cout << "Initial Hash Ring:" << std::endl;
    consistentHash.printHashRing();

    // 测试数据存储
    std::string data1 = "data1";
    std::string data2 = "data2";
    std::string data3 = "data3";

    std::cout << "\nData '" << data1
              << "' is stored in: " << consistentHash.getNode(data1)
              << std::endl;
    std::cout << "Data '" << data2
              << "' is stored in: " << consistentHash.getNode(data2)
              << std::endl;
    std::cout << "Data '" << data3
              << "' is stored in: " << consistentHash.getNode(data3)
              << std::endl;

    // 移除一个节点
    consistentHash.removeNode("NodeB");

    std::cout << "\nAfter removing NodeB:" << std::endl;
    consistentHash.printHashRing();

    // 测试数据在移除节点后的存储位置
    std::cout << "\nData '" << data1
              << "' is now stored in: " << consistentHash.getNode(data1)
              << std::endl;
    std::cout << "Data '" << data2
              << "' is now stored in: " << consistentHash.getNode(data2)
              << std::endl;
    std::cout << "Data '" << data3
              << "' is now stored in: " << consistentHash.getNode(data3)
              << std::endl;

    return 0;
}
