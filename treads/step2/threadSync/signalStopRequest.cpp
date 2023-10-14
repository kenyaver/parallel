#include <iostream>
#include <thread>
#include <future>
#include <string>

using namespace std::literals;

void function1(std::stop_token stopToken, const std::string& str){
    std::this_thread::sleep_for(1s);
    if(stopToken.stop_requested()){
        std::cout << str << ": stoped request\n";
    }
}

void function2(
std::promise<void> prom,
std::stop_token stopToken, const std::string& str
){  //
    std::this_thread::sleep_for(1s);
    std::stop_callback callBack(stopToken, [&str]{
        std::cout << str << ": stoped request\n";
    });
    prom.set_value();
}

int main(){
    std::stop_source stopSourse;
    std::stop_token stopToken = std::stop_token(stopSourse.get_token());

    std::thread thr1(function1, stopToken, "std::thread");

    std::jthread jthr(function1, stopToken, "std::jthread");

    auto fut1 = std::async([stopToken]{
        std::this_thread::sleep_for(1s);
        if(stopToken.stop_requested()){
            std::cout << "std::async: stop requested\n";
        }
    });

    std::promise<void> prom;

    auto fut2 = prom.get_future();
    std::thread thr2(function2, prom, stopToken, "std::promise");
    stopSourse.request_stop();
    if(stopToken.stop_requested()){
        std::cout << "main: stop requested\n";
    }

    thr1.join();
    thr2.join();
}
