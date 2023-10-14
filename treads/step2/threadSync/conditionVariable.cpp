#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

std::mutex mut;
std::condition_variable cond;

bool dataReady = false;

void worker(){
    std::cout << "processing sharing data... \n";
}

void waitWork(){
    std::cout << "waiting for work\n";
    std::unique_lock<std::mutex> lck(mut);
    cond.wait(lck, []{
        return dataReady;
    });
    worker();
    std::cout << "work done\n";
}

void setDataReady(){
    {
    std::lock_guard<std::mutex> lck(mut);
    dataReady = true;
    }
    std::cout << "data is ready!\n";
    cond.notify_one();
}

int main(){
    std::thread t1(waitWork);
    std::thread t2(setDataReady);

    t1.join();
    t2.join();
}