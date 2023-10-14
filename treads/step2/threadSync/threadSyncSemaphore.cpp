#include <iostream>
#include <semaphore>
#include <thread>
#include <vector>

std::vector<int> vec{};

std::counting_semaphore<1> prepareSignal(0);

void prepareWork(){
    vec.insert(vec.end(), {0, 1, 0, 3});
    std::cout <<"data prepared\n";
    prepareSignal.release();
}

void completeWork(){
    std::cout << "waiting for data\n";
    prepareSignal.acquire();
    vec[2] = 2;
    std::cout << "waiter completed work\n";
    for(auto i: vec){
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

int main(){
    std::thread t1(prepareWork);
    std::thread t2(completeWork);
    

    t1.join();
    t2.join();
}