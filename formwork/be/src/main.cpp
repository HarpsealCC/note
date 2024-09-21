#include <iostream>
#include <mutex>
#include <thread>

std::mutex mutex1;
std::mutex mutex2;

void thread1() {
    std::lock_guard<std::mutex> lock1(mutex1);
    std::cout << "Thread 1 acquired lock on mutex1" << std::endl;

    // 模拟一些工作
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::cout << "Thread 1 waiting for lock on mutex2" << std::endl;
    std::lock_guard<std::mutex> lock2(mutex2);  // 这里等待 mutex2，死锁发生
    std::cout << "Thread 1 acquired lock on mutex2" << std::endl;
}

void thread2() {
    std::lock_guard<std::mutex> lock2(mutex2);
    std::cout << "Thread 2 acquired lock on mutex2" << std::endl;

    // 模拟一些工作
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::cout << "Thread 2 waiting for lock on mutex1" << std::endl;
    std::lock_guard<std::mutex> lock1(mutex1);  // 这里等待 mutex1，死锁发生
    std::cout << "Thread 2 acquired lock on mutex1" << std::endl;
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}
