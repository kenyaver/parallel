#include <iostream>
#include <thread>

int main(){
    std::cout << std::boolalpha;
    std::jthread thr{[]{
        std::cout << "joinable thread\n";
    }};
    // thr.join();
}