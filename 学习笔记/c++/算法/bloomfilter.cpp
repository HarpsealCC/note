
#include <iostream>
#include <vector>

using namespace std;
class bloomfilter {
private:
    vector<uint8_t> bitarray;
    int             hash_size_;
    int             size_;

public:
    bloomfilter(int size, int hash_size) : size_(size), hash_size_(hash_size) {
        bitarray.resize(size);
    }
    void insert(const string& value) {
        for (int i = 0; i < hash_size_; i++) {
            int pos               = hasher(value, i);
            bitarray[pos % size_] = 1;
        }
    }

    bool contains(const string& value) {
        for (int i = 0; i < hash_size_; i++) {
            int pos = hasher(value, i);
            if (bitarray[pos % size_] != 1) {
                return false;
            }
        }
        return true;
    }

private:
    int hasher(const string& value, int seed) {
        std::hash<string> hasher;
        return hasher(value) + seed * 0x9e3779b9;
    }
};

// 测试 Bloom Filter
int main() {
    // 初始化 Bloom Filter，位数组大小为 1000，使用 3 个哈希函数
    bloomfilter bf(1000, 3);

    // 插入元素
    bf.insert("hello");
    bf.insert("world");

    // 查询元素
    std::cout << "Contains 'hello': " << bf.contains("hello") << std::endl;
    std::cout << "Contains 'world': " << bf.contains("world") << std::endl;
    std::cout << "Contains 'foo': " << bf.contains("foo") << std::endl;

    return 0;
}