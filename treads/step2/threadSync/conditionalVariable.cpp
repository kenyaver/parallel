// синхронизация потоков при помощи std::condition_variable

#include <vector>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <iostream>

std::vector<int> sharvec;
std::mutex mut;
std::condition_variable conVar;

bool dataReady = false;

void waitingForWork(){
    std::cout << "waiting\n";
    std::unique_lock<std::mutex> lck(mut);
    conVar.wait(lck, []{return dataReady; });
    sharvec[1] = 2;
    std::cout << "work done\n";
}

void setDataReady(){
    sharvec = {1, 0, 3};
    {
        std::lock_guard<std::mutex> lck(mut);
        dataReady = true;
    }
    std::cout << "data prepared\n";
    conVar.notify_one();
}

int main(){
    std::cout << '\n';

    std::thread t1(waitingForWork);
    std::thread t2(setDataReady);

    t1.join();
    t2.join();

    for(auto i: sharvec){
        std::cout << i << ' ';
    }
    std::cout << std::endl << std::endl;
}