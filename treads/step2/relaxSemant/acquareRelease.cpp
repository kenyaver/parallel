#include <iostream>
#include <thread>
#include <string>
#include <atomic>

std::atomic<std::string*> ptr;
std::atomic<int> atomData = 0;
int data = 0;

void producer(){
    std::string* p = new std::string("C++11");
    data = 2011;
    atomData.store(2014, std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_release);
    ptr.store(p, std::memory_order_relaxed);
}

void consumer(){
    std::string* p2;
    while(!(p2 = ptr.load(std::memory_order_acquire))){}
    std::atomic_thread_fence(std::memory_order_acquire);
    std::cout << *p2 << '\n';
    std::cout << data << '\n';
    std::cout << atomData.load(std::memory_order_relaxed);
}

int main(){
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    std::cout << std::endl;
    return 0;
}