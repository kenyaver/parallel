// синхронизация потоков при помощи std::atomic<bool> X

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

std::vector<int> sharvec;
std::atomic<bool> dataReady(false);

void waitingForWork(){
    std::cout << "waiting\n";
    while(!dataReady.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    sharvec[1] = 2;
    std::cout << "work Done\n";
}

void setDataReady(){
    sharvec = {1, 0, 3};
    dataReady = true;
    std::cout << "data prepared\n";
}

int main(){
    std::cout << "\n";
    
    std::thread t1(waitingForWork);
    std::thread t2(setDataReady);

    t1.join();
    t2.join();

    for(auto i: sharvec){
        std::cout << i << ' ';
    }
    std::cout << '\n';
}