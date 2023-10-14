// синхронизация потоков при помощи std::atomic_flag

#include <atomic>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>

std::vector<int> vec{};

std::atomic_flag atomicFlag{};

void prepareWork(){
    vec.insert(vec.end(), {1, 0, 0, 3});
    std::cout << "sender: data prepared\n";
    atomicFlag.test_and_set();
    atomicFlag.notify_one();
}

void completeWork(){
    std::cout << "waiter: waiting data\n";
    atomicFlag.wait(false);
    vec[2] = 2;
    std::cout << "waiter: complete the work\n";
    for(auto i: vec){
        std::cout << i << " ";
    }
    std::cout << '\n';
}

int main(){
    std::cout << '\n';
    
    std::thread t1(prepareWork);
    std::thread t2(completeWork);

    t1.join();
    t2.join();

    for(auto i: vec){
        std::cout << i << " ";
    }
    std::cout << '\n';
}