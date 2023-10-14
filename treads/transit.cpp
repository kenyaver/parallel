#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::vector<int> vec;
std::atomic<bool> produce = false;
std::atomic<bool> consume = false;

void producer(){
    vec.insert(vec.end(), {1, 0, 3});
    produce.store(true, std::memory_order_release);
}

void deliveryBoy(){
    while(!produce.load(std::memory_order_acquire));
    consume.store(true, std::memory_order_release);
}

void consumer(){
    while(!consume.load(std::memory_order_acquire));
    vec[1] = 2;
}

int main(){
    std::thread t1(producer);
    std::thread t2(deliveryBoy);
    std::thread t3(consumer);

    t1.join();
    t2.join();
    t3.join();

    for(auto i: vec){
        std::cout << i << ' ';
    }

    std::cout << '\n';
}