#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>

using namespace std::literals;

auto func = [](std::stop_token stoken){
    std::atomic<int> count{0};
    auto thread_id = std::this_thread::get_id();
    std::stop_callback callBack(stoken, [&count, thread_id]{
        std::cout << "Thread id: " << thread_id 
                  << ";\ncounter: " << count << '\n';
    });
    while(count < 10){
        std::this_thread::sleep_for(0.2s);
        count++;
    }
};

int main(){
    std::vector<std::jthread> vecThread(10);

    for(auto& thr: vecThread){
        thr = std::jthread(func);
    }

    std::this_thread::sleep_for(1s);

    for(auto& thr: vecThread){
        thr.request_stop();
    }
    }

