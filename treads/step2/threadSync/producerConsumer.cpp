#include <iostream>
#include <atomic>
#include <string>
#include <thread>

std::string work;
std::atomic<bool> ready = false;

void consumer(){
    while(!ready.load()){  }
    std::cout << work << '\n';
}

void producer(){
    work = "done";
    ready.store(true);
}

int main(){
    std::cout << '\n';

    std::thread t1(consumer);
    std::thread t2(producer);

    t1.join();
    t2.join();
}