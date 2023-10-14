#include <iostream>
#include <thread>
#include <string>

void executeTwoThreads(){
    std::string localString("local string");

    std::thread t1([localString]{
        std::cout << "per copy: " << localString << std::endl;
    });

    std::thread t2([&localString]{
        std::cout << "per reference: " << localString << std::endl;
    });

    t1.detach();
    t2.detach();
}

using namespace std::chrono_literals;

int main(){
    executeTwoThreads();

    std::this_thread::sleep_for(1s);
}