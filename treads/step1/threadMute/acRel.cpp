#include <iostream>
#include <thread>
#include <atomic>
#include <string>
#include <memory>

std::atomic<std::string*> ptr;
int data = 0;
std::atomic<int> atomData = 0;

void producer(){
    // std::shared_ptr<std::string> p = std::make_shared<std::string>("C++11");
    std::string* p = new std::string("C++11");
    data = 2011;
    atomData.store(2014, std::memory_order_relaxed);
    ptr.store(p, std::memory_order_release);
    // delete p;
}

void consumer(){
    std::string* p2;
    while(!(p2 = ptr.load(std::memory_order_acquire)));
    std::cout << "p2 = " << *p2 << '\n';
    std::cout << "data = " << data << '\n';
    std::cout << "atomData = " << atomData << '\n';
}

int main(){
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
}