/**
 * @file singleton.cpp
 * @brief
 * @author liuchengzhuo (844291270@qq.com)
 * @version 1.0
 * @date 2023-11-25
 *
 * @copyright Copyright (c) 2023
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author
 * <tr><td>2023-11-25 <td>1.0     <td>liuchengzhuo
 * <th>Description
 * <td>c++单例的各种实现方法
 * </table>
 */
#include <iostream>
#include <mutex>
#include <typeinfo>
template <typename T>
void PrintObjName(const T& obj) {
    std::cout << typeid(obj).name() << std::endl;
}

/**
 * @brief 懒汉模式的单例，在需要的时候才创建，可能会有并发的问题
 */
class Singleton1 {
public:
    Singleton1(const Singleton1&)                   = delete;
    Singleton1&        operator=(const Singleton1&) = delete;
    static Singleton1& getInstance() {
        static Singleton1* instance = nullptr;
        if (nullptr == instance) {
            instance = new Singleton1();
        }
        return *instance;
    }

private:
    Singleton1() {}
};
/**
 * @brief 饿汉模式的单例，在类加载的时候才创建，资源会浪费的
 */
class Singleton2 {
public:
    Singleton2(const Singleton2&)                   = delete;
    Singleton2&        operator=(const Singleton2&) = delete;
    static Singleton2& getInstance() {
        return instance;
    }

private:
    static Singleton2 instance;
    Singleton2() {}
};
Singleton2 Singleton2::instance;
/**
 * @brief 双重检查锁模式，兼顾并发与资源情况
 */
class Singleton3 {
public:
    Singleton3(const Singleton3&)                   = delete;
    Singleton3&        operator=(const Singleton3&) = delete;
    static Singleton3& getInstance() {
        static std::mutex  mux;
        static Singleton3* instance = nullptr;
        // 这里使用双重检查锁，是为了避免之后调用接口时都需要进行上锁
        if (nullptr == instance) {
            // 其实在这儿就可以直接上锁的
            std::lock_guard<std::mutex> lock(mux);
            if (nullptr == instance) {
                instance = new Singleton3();
            }
        }
        return *instance;
    }

private:
    Singleton3() {}
};
/**
 * @brief Meyers单例，c++11之后最普遍的单例模式
 */
class Singleton4 {
public:
    Singleton4(const Singleton4&)                   = delete;
    Singleton4&        operator=(const Singleton4&) = delete;
    static Singleton4& getInstance() {
        static Singleton4 instance;
        return instance;
    }

private:
    Singleton4() {}
};
int main() {
    PrintObjName(Singleton1::getInstance());
    PrintObjName(Singleton2::getInstance());
    PrintObjName(Singleton3::getInstance());
    PrintObjName(Singleton4::getInstance());
}