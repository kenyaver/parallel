#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

std::vector<int> vec;
std::atomic<bool> produce = false;

void producer(){
    vec = {1, 0, 3};
    produce.store(true, std::memory_order_release);
}

void consumer(){
    while(!produce.load(std::memory_order_acquire));
    // produce.load(std::memory_order_acquire);
    vec[1] = 2;
}

int main(){
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    for(auto i: vec){
        std::cout << i << ' ';
    }

    std::cout << '\n';
}