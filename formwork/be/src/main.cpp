#include <functional>
#include <iostream>
#include <vector>
class bloomfilter {
public:
    bloomfilter(int size, int hash_size) : size_(size), hash_size_(hash_size) {
        bv_.resize(size_, 0);
    }

    void insert(const std::string& str) {
        for (int i = 0; i < size_; i++) {
            bv_[hasher(str, i) % size_] = 1;
        }
    }

    bool contain(const std::string& str) {
        for (int i = 0; i < size_; i++) {
            if (bv_[hasher(str, i) % size_] != 1) {
                return false;
            }
        }
        return true;
    }

private:
    int hasher(const std::string str, int seed) {
        std::hash<std::string> hasher;
        return hasher(str) + seed * 0x123456;
    }

private:
    int                 size_;
    int                 hash_size_;
    std::vector<int8_t> bv_;
};