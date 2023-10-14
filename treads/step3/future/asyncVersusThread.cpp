#include <future>
#include <thread>
#include <iostream>

int main(){
    int res;
    std::thread t1([&]{
        res = 2000 + 11; 
    });
    t1.join();

    std::cout << "res: " << res << '\n';

    auto fut = std::async([] {
        return 2000 + 11;
    });

    std::cout << "fut.get: " << fut.get() << '\n';
}