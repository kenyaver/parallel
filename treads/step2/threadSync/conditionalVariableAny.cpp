#include <condition_variable>
#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>

using namespace std::literals;

std::mutex mut;
std::condition_variable_any condVAr;

bool dataReady;

void receiver(std::stop_token stoken){
    std::cout << "waiting\n";

    std::unique_lock<std::mutex> lck(mut);
    bool ret = condVAr.wait(lck, stoken, []{ return dataReady; });
    if(ret){
        std::cout << "Notification received\n";
    } else {
        std::cout << "stop request received\n";
    }
}

void sender(){
    std::this_thread::sleep_for(5ms);
    {
        std::lock_guard<std::mutex> lck(mut);
        dataReady = true;
        std::cout << "send notification\n";
    }
    condVAr.notify_one();
}

int main(){
    std::jthread t1(receiver);
    std::jthread t2(sender);
    
    t1.request_stop();

    t1.join();
    t2.join();
}