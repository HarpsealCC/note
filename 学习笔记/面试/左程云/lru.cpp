#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        // 如果 key 不存在，返回 -1
        if (cacheMap.find(key) == cacheMap.end()) {
            return -1;
        }

        // 如果 key 存在，将其对应的节点移到链表前端
        auto it = cacheMap[key];
        cacheItems.splice(cacheItems.begin(), cacheItems, it);

        return it->second;  // 返回 key 对应的值
    }

    void put(int key, int value) {
        // 如果 key 已存在，更新值并将节点移到链表前端
        if (cacheMap.find(key) != cacheMap.end()) {
            auto it    = cacheMap[key];
            it->second = value;
            cacheItems.splice(cacheItems.begin(), cacheItems, it);
        } else {
            // 如果 key 不存在，检查缓存是否已满
            if (cacheItems.size() == capacity) {
                // 删除链表最后一个节点（最久未使用的节点）
                auto last = cacheItems.back();
                cacheMap.erase(last.first);
                cacheItems.pop_back();
            }

            // 插入新节点到链表前端
            cacheItems.emplace_front(key, value);
            cacheMap[key] = cacheItems.begin();
        }
    }

private:
    int                  capacity;  // 缓存容量
    list<pair<int, int>> cacheItems;  // 双向链表存储缓存的 (key, value) 对
    unordered_map<int, list<pair<int, int>>::iterator>
        cacheMap;  // 哈希表：key -> 链表迭代器
};

int main() {
    LRUCache cache(2);  // 缓存容量为 2

    cache.put(1, 1);
    cache.put(2, 2);
    cout << "Get 1: " << cache.get(1) << endl;  // 返回 1

    cache.put(3, 3);                            // 删除键 2
    cout << "Get 2: " << cache.get(2) << endl;  // 返回 -1 (未找到)

    cache.put(4, 4);                            // 删除键 1
    cout << "Get 1: " << cache.get(1) << endl;  // 返回 -1 (未找到)
    cout << "Get 3: " << cache.get(3) << endl;  // 返回 3
    cout << "Get 4: " << cache.get(4) << endl;  // 返回 4

    return 0;
}
